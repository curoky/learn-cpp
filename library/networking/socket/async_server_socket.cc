/*
 * Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
 *
 * This file is part of learn-cpp.
 * See https://github.com/curoky/learn-cpp for further info.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <catch2/catch_test_macros.hpp>
#include <folly/SocketAddress.h>
#include <folly/io/async/AsyncServerSocket.h>
#include <folly/io/async/EventBase.h>
#include <stdint.h>
#include <unistd.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

TEST_CASE("basic usage", "[AsyncServerSocket]") {
  folly::EventBase base;
  auto socket = folly::AsyncServerSocket::newSocket(&base);
  socket->bind(0);
  socket->listen(0);
  socket->startAccepting();
}

TEST_CASE("duplicate bind", "[AsyncServerSocket]") {
  folly::EventBase base;
  auto server1 = folly::AsyncServerSocket::newSocket(&base);
  server1->bind(0);
  server1->listen(10);

  folly::SocketAddress address;
  server1->getAddress(std::addressof(address));

  auto server2 = folly::AsyncServerSocket::newSocket(&base);
  REQUIRE_THROWS_AS(server2->bind(address.getPort()), std::exception);
}

TEST_CASE("reuse port", "[AsyncServerSocket]") {
  folly::EventBase base;
  auto socket = folly::AsyncServerSocket::newSocket(&base);
  socket->bind(0);
  socket->listen(0);
  socket->startAccepting();
  folly::SocketAddress address;
  socket->getAddress(&address);

  try {
    socket->setReusePortEnabled(true);
  } catch (...) {
    FAIL("Reuse port probably not supported");
  }

  auto socket2 = folly::AsyncServerSocket::newSocket(&base);
  socket2->setReusePortEnabled(true);
  socket2->bind(address.getPort());
  socket2->listen(0);
  socket2->startAccepting();
}

TEST_CASE("v4 v6 same port", "[AsyncServerSocket]") {
  folly::EventBase base;
  auto serverSocket = folly::AsyncServerSocket::newSocket(&base);
  serverSocket->bind(0);
  auto addrs = serverSocket->getAddresses();
  REQUIRE(addrs.size() >= 0);

  // addrs := { [::]:19131, 0.0.0.0:19131 }
  uint16_t port = addrs[0].getPort();
  for (const auto& addr : addrs) {
    REQUIRE(port == addr.getPort());
  }
}

TEST_CASE("unix domain socket", "[AsyncServerSocket]") {
  std::string path;
  SECTION("basic") { path = "/tmp/folly-domian-socket.sock"; }
  SECTION("abstract") {
    path = "/tmp/folly-domian-socket.sock";
    path[0] = 0;
  }
  unlink(path.c_str());

  auto addr = folly::SocketAddress::makeFromPath(path);
  folly::EventBase base;
  auto serverSocket = folly::AsyncServerSocket::newSocket(&base);
  serverSocket->setReusePortEnabled(true);
  serverSocket->bind(addr);

  auto serverSocket2 = folly::AsyncServerSocket::newSocket(&base);
  serverSocket2->setReusePortEnabled(true);
  // serverSocket2->bind(addr);
}

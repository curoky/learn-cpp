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
#include <folly/IPAddress.h>
#include <folly/IPAddressV4.h>
#include <folly/IPAddressV6.h>
#include <folly/Range.h>

TEST_CASE("basic usage", "[Ipaddress]") {
  folly::IPAddress v4addr("192.0.2.129");
  folly::IPAddress v6map("::ffff:192.0.2.129");

  REQUIRE(v4addr.inSubnet("192.0.2.0/24") == v4addr.inSubnet(folly::IPAddress("192.0.2.0"), 24));
  REQUIRE(v4addr.inSubnet("192.0.2.128/30"));
  REQUIRE(!v4addr.inSubnet("192.0.2.128/32"));

  REQUIRE(v4addr.asV4().toLong() == 2164392128);
  REQUIRE(v4addr.asV4().toLongHBO() == 3221226113);

  REQUIRE(v4addr.isV4());
  REQUIRE(v6map.isV6());
  REQUIRE(v4addr == v6map);

  REQUIRE(v6map.isIPv4Mapped());
  REQUIRE(v4addr.asV4() == folly::IPAddress::createIPv4(v6map));
  REQUIRE(folly::IPAddress::createIPv6(v4addr) == v6map.asV6());
}

TEST_CASE("[Ipaddress]: v4/v6 judgement") {
  REQUIRE(folly::IPAddress("192.168.0.1").isV4() == true);
  REQUIRE(folly::IPAddress("192.168.0.1").isV6() == false);

  REQUIRE(folly::IPAddress("::ffff:192.0.2.129").isV4() == false);
  REQUIRE(folly::IPAddress("::ffff:192.0.2.129").isV6() == true);
}

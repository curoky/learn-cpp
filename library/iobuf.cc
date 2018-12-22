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
#include <folly/io/Cursor.h>
#include <folly/io/IOBuf.h>
#include <folly/io/IOBufQueue.h>

#include <iostream>
#include <memory>
#include <string>
#include <utility>

/*
 *  +-------+
 *  | IOBuf |
 *  +-------+
 *   /
 *  |
 *  v
 *  +------------+--------------------+-----------+
 *  | headroom   |        data        |  tailroom |
 *  +------------+--------------------+-----------+
 *  ^            ^                    ^           ^
 *  buffer()   data()               tail()      bufferEnd()
 *
 *  The length() method returns the length of the valid data;
 *  capacity() returns the entire capacity of the buffer (from buffer() to bufferEnd()).
 *  The headroom() and tailroom() methods return the amount of unused capacity
 *  available before and after the data.
 */

// TODO(curoky): add REQUIRE

TEST_CASE("simple test1", "[Iobuf]") {
  folly::IOBufQueue queue;
  queue.append("hello ", 6);
  queue.append("world", 5);
  std::string s;
  queue.appendToString(s);
  auto f = queue.front();
  std::cout << f->length() << std::endl;
  // char* str = (char*)f->data();
  // std::cout << str << std::endl;
  {
    auto t = queue.split(5);
    std::cout << t->length() << std::endl;
  }
  auto buf = queue.move();
  std::cout << buf->length() << std::endl;
}

TEST_CASE("[Iobuf]: simple test2") {
  folly::IOBufQueue queue(folly::IOBufQueue::cacheChainLength());
  auto buf1 = folly::IOBuf::copyBuffer(std::string("11111"));
  auto buf2 = folly::IOBuf::copyBuffer(std::string("22222"));
  queue.append(std::move(buf1));
  queue.append(std::move(buf2));
  std::cout << queue.chainLength() << std::endl;

  // auto f = queue.front();
  // std::cout << (char*)f->data() << std::endl;
  //
  // auto f2 = queue.move();
  // std::cout << (char*)f2->data() << std::endl;
  // auto f3 = f2->next();
  // std::cout << (char*)f3->data() << std::endl;

  // auto f4 = queue.split(8);
  // std::cout << (char*)f4->data() << std::endl;
}

TEST_CASE("[Iobuf]: simple test3") {
  folly::IOBufQueue queue(folly::IOBufQueue::cacheChainLength());
  auto buf1 = folly::IOBuf::copyBuffer(std::string("11"));
  auto buf2 = folly::IOBuf::copyBuffer(std::string("22"));
  queue.append(std::move(buf1));
  queue.append(std::move(buf2));
  std::cout << queue.chainLength() << std::endl;

  // auto rage = queue.move()->coalesce();
  // std::cout << rage.data() << std::endl;

  auto c = folly::io::Cursor(queue.front());
  std::cout << c.length() << std::endl;

  std::cout << c.read<char>() << std::endl;
  std::cout << c.read<char>() << std::endl;
  std::cout << c.read<char>() << std::endl;
  std::cout << c.read<char>() << std::endl;
}

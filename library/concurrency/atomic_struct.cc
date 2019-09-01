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
#include <folly/synchronization/AtomicStruct.h>
#include <netdb.h>

// 类似于 std::atomic，但是适用于任何小于 8 bytes 的数据结构。
// 原理：将数据转化为 int8/int16/int32/int64 进行处理

namespace {
struct TwoBy32 {
  uint32_t left;
  uint32_t right;
};
}  // namespace

TEST_CASE("automic struct basic usage", "[folly]") {
  folly::AtomicStruct<TwoBy32> a(TwoBy32{10, 20});
  // TODO(curoky): 这里的赋值是怎么实现的。
  TwoBy32 av = a;
  REQUIRE(av.left == 10);
  REQUIRE(av.right == 20);
  REQUIRE(a.compare_exchange_strong(av, TwoBy32{30, 40}));
  REQUIRE_FALSE(a.compare_exchange_weak(av, TwoBy32{31, 41}));
  REQUIRE(av.left == 30);
  REQUIRE(a.is_lock_free());
  auto b = a.exchange(TwoBy32{50, 60});
  REQUIRE(b.left == 30);
  REQUIRE(b.right == 40);
  REQUIRE(a.load().left == 50);
  a = TwoBy32{70, 80};
  REQUIRE(a.load().right == 80);
  a.store(TwoBy32{90, 100});
  av = a;
  REQUIRE(av.left == 90);
  folly::AtomicStruct<TwoBy32> c;
  c = b;
  REQUIRE(c.load().right == 40);
}

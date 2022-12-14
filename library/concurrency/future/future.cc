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
#include <folly/Unit.h>
#include <folly/futures/Future.h>
#include <folly/futures/Promise.h>

#include <type_traits>
#include <utility>

TEST_CASE("make empty ", "[Future]") {
  auto f = folly::Future<int>::makeEmpty();
  REQUIRE_THROWS_AS(f.isReady(), folly::FutureInvalid);
}

TEST_CASE("future to unit", "[Future]") {
  folly::Future<folly::Unit> fu = folly::makeFuture().unit();
  fu.value();
  //   EXPECT_TRUE(makeFuture<Unit>(eggs).unit().hasException());
}

TEST_CASE("then return", "[Future]") {
  folly::Future<int> ret = folly::makeFuture<int>(1).thenValue([](int&&) {
    return 2;
    //  return folly::Future<int>(2);
  });
  REQUIRE(std::move(ret).get() == 2);
}

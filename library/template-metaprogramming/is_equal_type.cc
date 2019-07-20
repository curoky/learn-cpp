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

template <typename T1, typename T2>
class theSameType {
 public:
  enum { ret = false };
};

template <typename T>
class theSameType<T, T> {
 public:
  enum { ret = true };
};

TEST_CASE("example 1", "[isEqualType]") {
  REQUIRE(theSameType<int, int>::ret == true);
  REQUIRE(theSameType<int, double>::ret == false);
}

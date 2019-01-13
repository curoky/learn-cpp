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

template <int Num>
struct Echo {
  int echo() { return Num; }
};
template <>
struct Echo<0> {
  int echo() { return 0; }
};
template <>
struct Echo<1> {
  int echo() { return 1; }
};

TEST_CASE("base test", "[NonTypeParam]") {
  REQUIRE(Echo<0>().echo() == 0);
  REQUIRE(Echo<1>().echo() == 1);
}
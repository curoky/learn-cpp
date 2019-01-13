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

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

TEST_CASE("OfTest", "[NoModify]") {
  std::vector<int> number = {0, 1, 2, 3, 4, 5};
  REQUIRE(std::any_of(number.begin(), number.end(), [](int x) { return x == 3; }));
  REQUIRE(std::none_of(number.begin(), number.end(), [](int x) { return x < 0; }));
  REQUIRE(std::all_of(number.begin(), number.end(), [](int x) { return x < 6; }));
}

TEST_CASE("CountTest", "[NoModify]") {
  std::vector<int> number = {0, 1, 2, 3, 4, 5, 5};
  REQUIRE(std::count(number.begin(), number.end(), 5) == 2);
  REQUIRE(std::count_if(number.begin(), number.end(), [](int x) { return x % 2 == 0; }) == 3);
}

TEST_CASE("MisMatchTest", "[NoModify]") {
  std::vector<int> number1 = {0, 1, 2, 3, 4, 5};
  std::vector<int> number2 = {0, 1, 2, 4, 5, 6};
  auto mis = std::mismatch(number1.begin(), number1.end(), number2.begin(), number2.end());
  REQUIRE(*mis.first == 3);
  REQUIRE(*mis.second == 4);
}

TEST_CASE("SearchTest", "[NoModify]") {
  std::string tar = "abcdefcde";
  std::string par = "cde";
  auto ret1 = std::search(tar.begin(), tar.end(), par.begin(), par.end());
  REQUIRE(std::distance(tar.begin(), ret1) == 2);
}

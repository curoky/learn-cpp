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

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <string>
#include <vector>

TEST_CASE("floating point comparisons", "[Catch2]") {
  REQUIRE(2 == Catch::Approx(2.000000000001));

  using namespace Catch::literals;  // NOLINT
  REQUIRE(2 == 2.000000000001_a);

  SECTION("epsilon") {
    // 允许相差 1%
    Catch::Approx target = Catch::Approx(100).epsilon(0.01);
    REQUIRE(89.9 != target);
    REQUIRE(99.0 == target);
    REQUIRE(101.0 == target);
    REQUIRE(101.1 != target);
  }

  SECTION("margin") {
    // 允许相差大小 5
    Catch::Approx target = Catch::Approx(100).margin(5);
    REQUIRE(94.0 != target);
    REQUIRE(95.0 == target);
    REQUIRE(105.0 == target);
    REQUIRE(106.0 != target);
  }

  SECTION("scale") {}
}

// https://github.com/catchorg/Catch2/blob/master/docs/matchers.md#top

TEST_CASE("string matcher", "[Catch2]") {
  // using Catch::Matchers::EndsWith;
  // or using Catch::EndsWith
  REQUIRE_THAT("hello world", Catch::Matchers::StartsWith("hello"));
  REQUIRE_THAT("hello world", Catch::Matchers::EndsWith("world"));
  REQUIRE_THAT("hello world", Catch::Matchers::ContainsSubstring("hello"));
  REQUIRE_THAT("hello world", Catch::Matchers::Equals("hello world"));
  REQUIRE_THAT("hello world", Catch::Matchers::Matches(R"~(hello \w*)~"));

  REQUIRE_THAT("hello world", Catch::Matchers::EndsWith("WORLD", Catch::CaseSensitive::No));

  REQUIRE_THAT("hello world",
               Catch::Matchers::StartsWith("hello") && Catch::Matchers::EndsWith("world"));
  REQUIRE_THAT("hello world",
               Catch::Matchers::StartsWith("hello") && !Catch::Matchers::ContainsSubstring("dog"));
  // Bugs, &&等运算符不会持有matcher对象的所有权，所以下面的代码会crash
  // auto match_expression = Catch::StartsWith("hello") && Catch::EndsWith("world");
  // REQUIRE_THAT("hello world", match_expression);
}

TEST_CASE("vector matchers", "[Catch2]") {}
TEST_CASE("deneric matchers", "[Catch2]") {}
TEST_CASE("Exception matchers", "[Catch2]") {}
TEST_CASE("custom matchers", "[Catch2]") {}

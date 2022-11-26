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

#include <expected>

TEST_CASE("basic", "[expected]") {
  std::expected<int, std::string> e;
  e.emplace(1);
  REQUIRE(e.has_value());

  e = std::unexpected("1");
  REQUIRE(e.has_value() == false);
}

namespace {
auto divide(int a, int b) -> std::expected<double, std::string> {
  if (b == 0) {
    return std::unexpected("divide by zero");
  } else {
    return (double)a / b;
  }
}
}  // namespace

TEST_CASE("func", "[expected]") {
  REQUIRE(divide(1, 0).error() == "divide by zero");
  REQUIRE(divide(1, 0).has_value() == false);
  REQUIRE_THROWS_AS(divide(1, 0).value(), std::bad_expected_access<std::string>);
  REQUIRE(divide(1, 0).value_or(1) == 1);

  REQUIRE(divide(1, 1).value() == 1);
  REQUIRE(divide(1, 1).has_value() == true);
  REQUIRE(divide(1, 1).error() == "");
}

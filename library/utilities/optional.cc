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

#include <optional>
#include <string>

#include "library/wheel/class_utils.h"

TEST_CASE("simple test", "[Optional]") {
  std::optional<std::string> opt;
  REQUIRE(opt == std::nullopt);
  REQUIRE(opt.has_value() == false);
  REQUIRE(opt.value_or("123") == "123");
  REQUIRE_THROWS_AS(opt.value(), std::bad_optional_access);

  opt = "123";
  REQUIRE(opt.has_value() == true);
  REQUIRE(opt.value() == "123");
  REQUIRE(opt->size() == 3);
  REQUIRE((*opt).size() == 3);
}

TEST_CASE("ConstructTest", "[Optional]") {
  using mox::ClassMetrics;

  std::optional<ClassMetrics> opt;
  opt = {};
}

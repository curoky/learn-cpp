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

#include <string>
#include <utility>
#include <vector>

#include "library/wheel/class_utils.h"  // for ClassMetrics, ClassMetrics::Counter

using mox::ClassMetrics;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpessimizing-move"

TEST_CASE("return", "[Move]") {
  ClassMetrics::Counter counter;

  auto normal_ret = [&counter]() {
    ClassMetrics cm(counter);
    return cm;
  };
  auto move_ret = [&counter]() {
    // moving a local object in a return statement prevents copy elision [-Wpessimizing-move]GCC
    ClassMetrics cm(counter);
    return std::move(cm);
  };

  SECTION("normal_ret") {
    ClassMetrics cm(normal_ret());
    REQUIRE(counter.copy_cons == 0);
    REQUIRE(counter.move_cons == 0);
  }

  SECTION("move_ret") {
    ClassMetrics cm(move_ret());
    REQUIRE(counter.copy_cons == 0);
    REQUIRE(counter.move_cons == 1);
  }
}
#pragma GCC diagnostic pop

TEST_CASE("vector emplace", "[Move]") {
  ClassMetrics::Counter counter;

  std::vector<ClassMetrics> cms;

  ClassMetrics cm(counter);
  counter.reset();

  SECTION("emplace local var without move") {
    cms.emplace_back(cm);
    REQUIRE(counter.copy_cons == 1);
    REQUIRE(counter.move_cons == 0);
  }

  SECTION("emplace local var with move") {
    cms.emplace_back(std::move(cm));
    REQUIRE(counter.copy_cons == 0);
    REQUIRE(counter.move_cons == 1);
  }
}

TEST_CASE("function args", "[Move]") {
  ClassMetrics::Counter counter;

  auto test_rvalue = [](ClassMetrics&&) {};

  ClassMetrics cm(counter);

  test_rvalue(std::move(cm));
  REQUIRE(counter.move_cons == 0);
}

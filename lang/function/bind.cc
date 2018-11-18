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

#include <functional>
#include <string>

#include "technique/class_utils.h"

TEST_CASE("RefTest", "[Bind]") {
  auto inc = [](std::string& str) { str += "1"; };
  std::string num = "1";
  // if not use ref, compile ok but num not add.
  std::function<void()> inc_num_noref = std::bind(inc, num);
  inc_num_noref();
  REQUIRE(num == "1");

  std::function<void()> inc_num_ref = std::bind(inc, std::ref(num));
  inc_num_ref();
  REQUIRE(num == "11");
}

TEST_CASE("BindCopy", "[Bind]") {
  std::string msg = "123";
  auto print = [](std::string m) -> std::string { return m; };
  auto func1 = std::bind(print, msg);
  auto func2 = std::bind(print, std::ref(msg));
  msg = "234";
  REQUIRE(func1() == "123");
  REQUIRE(func2() == "234");
}

TEST_CASE("CrefTest", "[Bind]") {
  using mox::ClassMetrics;
  ClassMetrics::Counter counter;

  auto check_ref = [](ClassMetrics&) {};
  auto check_cref = [](const ClassMetrics&) {};

  ClassMetrics cm(counter);
  ClassMetrics& cm_ref = cm;
  const ClassMetrics& cm_cref = cm;

  counter.reset();

  SECTION("bind not std::ref") {
    std::bind(check_ref, cm)();
    std::bind(check_ref, cm_ref)();
    std::bind(check_ref, cm_cref)();

    std::bind(check_cref, cm)();
    std::bind(check_cref, cm_ref)();
    std::bind(check_cref, cm_cref)();
    REQUIRE(counter.copy_cons == 6);
    REQUIRE(counter.move_cons == 0);
  }

  SECTION("bind with std::ref") {
    std::bind(check_ref, std::ref(cm))();
    std::bind(check_ref, std::ref(cm_ref))();
    REQUIRE(counter.copy_cons == 0);
    REQUIRE(counter.move_cons == 0);
  }

  SECTION("bind with std::cref") {
    std::bind(check_cref, std::cref(cm))();
    std::bind(check_cref, std::cref(cm_ref))();
    std::bind(check_cref, std::cref(cm_cref))();
    REQUIRE(counter.copy_cons == 0);
    REQUIRE(counter.move_cons == 0);
  }
}

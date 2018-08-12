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

#include "technique/class_utils.h"

#define USE_STD

#ifdef USE_STD
#include <any>

namespace detail {
using std::any;
using std::any_cast;
using std::bad_any_cast;
}  // namespace detail
#endif

#ifdef USE_BOOST
#include <boost/any.hpp>

namespace detail {
using boost::any;
using boost::any_cast;
using boost::bad_any_cast;
}  // namespace detail
#endif

#ifdef USE_ABSL
#include <absl/types/any.h>
#include <absl/types/bad_any_cast.h>

namespace detail {
using absl::any;
using absl::any_cast;
using absl::bad_any_cast;
using absl::make_any;
}  // namespace detail
#endif

using mox::ClassMetrics;

TEST_CASE("construct", "[Any]") {
  ClassMetrics::Counter counter;

  ClassMetrics cm(counter);

  counter.reset();

  SECTION("lvalue") {
    detail::any _ = cm;
    REQUIRE(counter.copy_cons == 1);
    REQUIRE(counter.move_cons == 0);
  }
  SECTION("rvalue") {
    detail::any _ = ClassMetrics(counter);
    REQUIRE(counter.copy_cons == 0);
    REQUIRE(counter.move_cons == 1);
  }
  SECTION("move lvalue") {
    detail::any _ = std::move(cm);
    REQUIRE(counter.copy_cons == 0);
    REQUIRE(counter.move_cons == 1);
  }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
TEST_CASE("cast get", "[Any]") {
  ClassMetrics::Counter counter;

  detail::any cm = ClassMetrics(counter);

  counter.reset();

  // Construct::reset();
  // detail::any cat = Construct();
  // Construct::reset();
  SECTION("no ref") {
    ClassMetrics _ = detail::any_cast<ClassMetrics>(cm);
    REQUIRE(counter.copy_cons == 1);
    REQUIRE(counter.move_cons == 0);
  }
  SECTION("lvalue ref") {
    ClassMetrics& _ = detail::any_cast<ClassMetrics&>(cm);
    REQUIRE(counter.copy_cons == 0);
    REQUIRE(counter.move_cons == 0);
  }
  SECTION("rvalue ref") {
    ClassMetrics _ = detail::any_cast<ClassMetrics&&>(std::move(cm));
    REQUIRE(counter.copy_cons == 0);
    REQUIRE(counter.move_cons == 1);
  }

  SECTION("point") {
    ClassMetrics* _ = detail::any_cast<ClassMetrics>(&cm);
    REQUIRE(counter.copy_cons == 0);
    REQUIRE(counter.move_cons == 0);
  }
}
#pragma GCC diagnostic pop

TEST_CASE("BadAnyCastTest", "[Any]") {
  detail::any int_value = 1;
  REQUIRE_THROWS_AS(detail::any_cast<float>(int_value), detail::bad_any_cast);
}

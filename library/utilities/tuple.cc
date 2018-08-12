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

#include <compare>
#include <functional>
#include <string>
#include <tuple>
#include <utility>

// #include <absl/utility/utility.h>
// using absl::apply;
// using absl::make_from_tuple;

namespace {
struct Time {
  int hour;
  int minute;
  int second;

  Time(int h, int m, int s) : hour(h), minute(m), second(s) {}
  void init(int h, int m, int s) { hour = h, minute = m, second = s; }
  std::tuple<int, int, int> toTuple() { return std::make_tuple(hour, minute, second); }

  friend bool operator<(const Time& lhs, const Time& rhs) {
    return std::tie(lhs.hour, lhs.minute, lhs.second) < std::tie(rhs.hour, rhs.minute, rhs.second);
  }
};
}  // namespace

TEST_CASE("make_from_tuple test", "[Tuple]") {
  auto tuple = std::make_tuple(11, 22, 33);
  Time t = std::make_from_tuple<Time>(std::move(tuple));
  REQUIRE(t.hour == 11);
  REQUIRE(t.minute == 22);
  REQUIRE(t.second == 33);
}

TEST_CASE("apply test", "[Tuple]") {
  using namespace std::placeholders;  // NOLINT

  Time t(0, 0, 0);
  auto cons = std::make_tuple(11, 22, 33);

  SECTION("create func with bind") {
    std::apply(std::bind(&Time::init, std::ref(t), _1, _2, _3), std::move(cons));
  }
  SECTION("create func with tuple_cat") {
    std::apply(&Time::init, std::tuple_cat(std::tie(t), std::move(cons)));
  }
  REQUIRE(t.hour == 11);
  REQUIRE(t.minute == 22);
  REQUIRE(t.second == 33);
}

TEST_CASE("tie ref tuple test", "[Tuple]") {
  int a = 1, b = 2, c = 3;
  auto t = std::tie(a, b, c);
  a = 11, b = 22, c = 33;
  REQUIRE(t == std::make_tuple(11, 22, 33));
}

TEST_CASE("tie compare test", "[Tuple]") {
  REQUIRE(Time(1, 0, 0) < Time(2, 0, 0));
  REQUIRE(Time(1, 1, 0) < Time(1, 2, 0));
  REQUIRE(Time(1, 1, 1) < Time(1, 1, 2));

  REQUIRE_FALSE(Time(2, 0, 0) < Time(1, 0, 0));
  REQUIRE_FALSE(Time(1, 2, 0) < Time(1, 1, 0));
  REQUIRE_FALSE(Time(1, 1, 2) < Time(1, 1, 1));
}

TEST_CASE("tie unpack test", "[Tuple]") {
  int h, m;
  std::tie(h, m, std::ignore) = Time(11, 22, 33).toTuple();
  REQUIRE(h == 11);
  REQUIRE(m == 22);
}

TEST_CASE("tuple_cat test", "[Tuple]") {
  int a = 1, b = 2, c = 3;
  auto tuple1 = std::make_tuple(a, b, c);
  auto tuple2 = std::tie(a, b, c);

  auto tuple_merge = std::tuple_cat(tuple1, tuple2);
  a = 11, b = 22, c = 33;
  REQUIRE(tuple_merge == std::make_tuple(1, 2, 3, 11, 22, 33));
}

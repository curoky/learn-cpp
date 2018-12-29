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

// This example is an adaptation of one found in Louis Dionne's dyno library.
#include <catch2/catch_test_macros.hpp>
#include <folly/Poly.h>

#include <string>
#include <vector>

namespace {

struct IDrawable {
  // Define the interface of something that can be drawn:
  template <class Base>
  struct Interface : Base {
    std::string draw() const { return folly::poly_call<0>(*this); }
  };
  // Define how concrete types can fulfill that interface (in C++17):
  template <class T>
  using Members = folly::PolyMembers<&T::draw>;
};

// Define an object that can hold anything that can be drawn:
using Drawable = folly::Poly<IDrawable>;

struct Square {
  std::string draw() const { return "Square"; }
};

struct Circle {
  std::string draw() const { return "Circle"; }
};

}  // namespace

TEST_CASE("basic usage", "[Poly]") {
  std::vector<Drawable> d = {Square(), Circle()};
  REQUIRE(d[0].draw() == "Square");
  REQUIRE(d[1].draw() == "Circle");
}

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
#include <refl.hpp>

#include <tuple>

struct Point {
  float x;
  float y;
};

/* Metadata */
REFL_AUTO(type(Point), field(x, /* attributes */), field(y));

TEST_CASE("basic usage", "[Refl]") {
  constexpr Point pt{};

  // Converting to an std::tuple: (Note the constexpr!)
  constexpr auto values = refl::util::map_to_tuple(refl::reflect(pt).members, [&](auto member) {
    // refl::descriptor::is_readable (found by Koenig lookup)
    if constexpr (is_readable(member)) {
      return member(pt);  // invoke the member
    }
  });

  std::tuple<int, int> expect{0, 0};
  REQUIRE(values == expect);
  // Result: values == std::tuple<int, int>{ 0, 0 };
}

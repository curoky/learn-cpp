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

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <catch2/catch_test_macros.hpp>
#include <stddef.h>

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

TEST_CASE("base test", "[Transform]") {
  std::vector<int> ids = {0, 1, 2, 3, 4, 5};
  std::vector<std::string> ids_strs;

  SECTION("std::transform") {
    std::transform(ids.begin(), ids.end(), std::back_inserter(ids_strs),
                   [](int id) { return std::to_string(id); });
  }

  SECTION("ranges::transform") {
    std::ranges::transform(ids, std::back_inserter(ids_strs),
                           [](int id) { return std::to_string(id); });
  }

  SECTION("boost::range::transform") {
    boost::range::transform(ids, std::back_inserter(ids_strs),
                            [](int id) { return std::to_string(id); });
  }

  SECTION("boost::adaptors::transformed") {
    boost::copy(ids | boost::adaptors::transformed([](int id) { return std::to_string(id); }),
                std::back_inserter(ids_strs));
  }

  SECTION("std::view") {
    std::ranges::copy(ids | std::views::transform([](int id) { return std::to_string(id); }),
                      std::back_inserter(ids_strs));
  }

  for (size_t i = 0; i < ids_strs.size(); ++i) {
    REQUIRE(ids_strs[i] == std::to_string(i));
  }
}

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

#include <boost/range/adaptor/copied.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/algorithm.hpp>
#include <catch2/catch_test_macros.hpp>

#include <iterator>
#include <list>
#include <map>
#include <vector>

TEST_CASE("copied", "[Adaptor]") {
  std::vector<int> input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> result;

  boost::copy(input | boost::adaptors::copied(1, 5), std::back_inserter(result));

  std::vector<int> expect = {1, 2, 3, 4};
  REQUIRE(result == expect);
}

TEST_CASE("copy", "[Range]") {
  std::map<int, int> foo = {{1, 2}, {2, 3}};
  std::vector<int> keys;
  std::list<int> valus;
  boost::copy(foo | boost::adaptors::map_keys, std::back_inserter(keys));
  boost::copy(foo | boost::adaptors::map_values, std::back_inserter(valus));
  REQUIRE(keys == std::vector<int>({1, 2}));
  REQUIRE(valus == std::list<int>({2, 3}));
}

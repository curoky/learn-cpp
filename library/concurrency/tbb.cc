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

#define TBB_PREVIEW_CONCURRENT_ORDERED_CONTAINERS 1
#include <catch2/catch_test_macros.hpp>
#include <tbb/concurrent_map.h>
#include <tbb/concurrent_set.h>
#include <tbb/concurrent_vector.h>

TEST_CASE("concurrent_vector", "[Container]") {
  tbb::concurrent_vector<int> nub;
  nub.emplace_back(1);
  REQUIRE(nub.size() == 1);
}

TEST_CASE("concurrent_map", "[Container]") {
  tbb::concurrent_map<int, int> nub;
  nub[1] = 1;
  REQUIRE(nub[1] == 1);
}

TEST_CASE("concurrent_set", "[Container]") {
  tbb::concurrent_set<int> nub;
  nub.insert(1);
  REQUIRE(nub.count(1) == 1);
}

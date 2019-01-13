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

/**
 * @brief Heap operations
 *        - is_heap
 *        - ranges::is_heap
 *        - is_heap_until
 *        - ranges::is_heap_until
 *        - make_heap
 *        - ranges::make_heap
 *        - push_heap
 *        - ranges::push_heap
 *        - pop_heap
 *        - ranges::pop_heap
 *        - sort_heap
 *        - ranges::sort_heap
 */
#ifndef __clang__

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <functional>
#include <iterator>
#include <ranges>
#include <vector>

TEST_CASE("basic usage", "[Heap]") {
  std::vector<int> heap = {1, 2, 3, 4, 5};
  REQUIRE_FALSE(std::ranges::is_heap(heap));

  std::ranges::make_heap(heap);
  REQUIRE(std::ranges::is_heap(heap));

  heap.push_back(6);
  REQUIRE_FALSE(std::ranges::is_heap(heap));
  REQUIRE(*std::ranges::is_heap_until(heap) == 6);
  REQUIRE(std::distance(heap.begin(), std::ranges::is_heap_until(heap)) == 5);

  std::ranges::push_heap(heap);
  REQUIRE(std::ranges::is_heap(heap));

  std::ranges::pop_heap(heap);
  REQUIRE(heap.back() == 6);
}
#endif

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

#include <assert.h>
#include <catch2/catch_test_macros.hpp>
#include <immer/vector.hpp>

TEST_CASE("basic usage", "[Immer]") {
  const auto v0 = immer::vector<int>{};
  const auto v1 = v0.push_back(13);
  assert(v0.size() == 0 && v1.size() == 1 && v1[0] == 13);

  const auto v2 = v1.set(0, 42);
  assert(v1[0] == 13 && v2[0] == 42);
}
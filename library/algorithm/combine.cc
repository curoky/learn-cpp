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

/** Refference
 * https://codereview.stackexchange.com/questions/30846/zip-like-functionality-with-c11s-range-based-for-loop
 * https://stackoverflow.com/questions/12552277/whats-the-best-way-to-iterate-over-two-or-more-containers-simultaneously
 * https://stackoverflow.com/questions/8511035/sequence-zip-function-for-c11
 */

#include <boost/range/combine.hpp>
#include <catch2/catch_test_macros.hpp>

#include <list>
#include <vector>

TEST_CASE("basic usage", "[Combine]") {
  std::vector<int> a = {1, 2, 3, 4, 5};
  std::list<int> b = {1, 2, 3, 4, 5};

  for (const auto& var : boost::combine(a, b)) {
    int f, s;
    boost::tie(f, s) = var;
    REQUIRE(f == s);
  }
}

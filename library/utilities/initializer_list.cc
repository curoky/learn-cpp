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

#include <initializer_list>
#include <memory>
#include <vector>

namespace {

template <class T>
struct S {
  std::vector<T> v;
  std::vector<std::vector<T>> vv;

  S(std::initializer_list<T> l) : v(l) {}
  S(std::initializer_list<std::vector<T>> l) : vv(l.begin(), l.end()) {}

  void append(std::initializer_list<T> l) { v.insert(v.end(), l.begin(), l.end()); }
};

}  // namespace

TEST_CASE("basic usage", "[InitializerList]") {
  S<int> s1 = {1, 2, 3};
  REQUIRE(s1.v.size() == 3);

  S<int> s2 = {{1}, {1, 2}, {1, 2, 3}};
  REQUIRE(s2.vv.size() == 3);
  REQUIRE(s2.vv[0].size() == 1);
  REQUIRE(s2.vv[1].size() == 2);
  REQUIRE(s2.vv[2].size() == 3);
}

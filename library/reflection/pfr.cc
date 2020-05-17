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
#include <boost/pfr.hpp>
#include <catch2/catch_test_macros.hpp>

#include <string>

namespace {
struct Type {
  int a;
  double b;
  std::string c;
};
}  // namespace

TEST_CASE("basic usage", "[pfr]") {
  Type t{1, 2.0, "3"};
  int a = boost::pfr::get<0>(t);
  double b = boost::pfr::get<1>(t);
  std::string c = boost::pfr::get<2>(t);

  REQUIRE(boost::pfr::tuple_size<Type>::value == 3);
  // REQUIRE(boost::pfr::io(t) == "");
}

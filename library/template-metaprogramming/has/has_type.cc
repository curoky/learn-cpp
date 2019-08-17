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
#include <fatal/type/has_type.h>

#include <type_traits>

class Foo1 {
 public:
  using type_int = int;
  int var_int;
  int var_func_void_int();
  void var_func_void_void();

 private:
  using private_type_int = int;
  int private_var_int;
};

FATAL_HAS_TYPE(has_type_int, type_int);

TEST_CASE("has tyep", "[Fatal]") {
  REQUIRE(has_type_int::apply<Foo1>::value == true);
  REQUIRE(has_type_int::apply<int>::value == false);
}

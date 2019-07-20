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
#include <nameof.hpp>

#include <string>
#include <string_view>
#include <utility>

TEST_CASE("check compiler support", "[Nameof]") {
  // check is nameof_type supported compiler
  REQUIRE(NAMEOF_TYPE_SUPPORTED);
  REQUIRE(nameof::is_nameof_type_supported);
  // check is nameof_enum supported compiler
  REQUIRE(NAMEOF_ENUM_SUPPORTED);
  REQUIRE(nameof::is_nameof_enum_supported);
}

TEST_CASE("NAMEOF usage", "[Nameof]") {
  bool bool_var;
  // Name of variable.
  REQUIRE(NAMEOF(bool_var) == "bool_var");

  // Name of member variable.
  std::pair<int, int> pii_var;
  REQUIRE(NAMEOF(pii_var.first) == "first");

  // Name of member function.
  std::string str_var;
  REQUIRE(NAMEOF(str_var.c_str()) == "c_str");

  // Name of macro.
  REQUIRE(NAMEOF(__LINE__) == "__LINE__");

  // error: lambda expression in an unevaluated operand
  // REQUIRE(NAMEOF(NAMEOF(str_var)) == "NAMEOF");
}

TEST_CASE("nameof_enum", "[Nameof]") {
  //
}
TEST_CASE("nameof_type", "[Nameof]") {
  using T = const int&;
  REQUIRE(NAMEOF_TYPE(T) == "int");
}

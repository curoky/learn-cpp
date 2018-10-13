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
#include <folly/Demangle.h>
#include <folly/FBString.h>

#include <cstdint>
#include <functional>
#include <string>
#include <typeinfo>

TEST_CASE("basic type", "[Sizeof]") {
  //
  REQUIRE(sizeof(uint32_t) == 4);
}
TEST_CASE("pointer", "[Sizeof]") {
  REQUIRE(sizeof(char*) == 8);
  REQUIRE(sizeof(int*) == 8);
  REQUIRE(sizeof(int64_t*) == 8);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

TEST_CASE("char", "[Sizeof]") {
  REQUIRE(sizeof("") == 1);
  REQUIRE(sizeof('1') == 1);
  REQUIRE(sizeof("1") == 2);
  REQUIRE(sizeof("\0\0") == 3);
  REQUIRE(folly::demangle(typeid("").name()) == "char [1]");
  REQUIRE(folly::demangle(typeid('1').name()) == "char");
  REQUIRE(folly::demangle(typeid("1").name()) == "char [2]");

  // ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]GCC
  char* message1 = "123";
  char message2[] = "123";
  char message3[5] = "1234";
  REQUIRE(sizeof(message1) == 8);
  REQUIRE(sizeof(message2) == 4);
  REQUIRE(sizeof(message3) == 5);
  REQUIRE(folly::demangle(typeid(message1).name()) == "char*");
  REQUIRE(folly::demangle(typeid(message2).name()) == "char [4]");
  REQUIRE(folly::demangle(typeid(message3).name()) == "char [5]");
}
#pragma GCC diagnostic pop

namespace {
struct Test {
  void foo() {}
  static void boo() {}
};
}  // namespace

TEST_CASE("function test", "[Sizeof]") {
  // TODO(curoky): https://stackoverflow.com/questions/13503511/sizeof-of-stdfunctionvoidint-type
  REQUIRE(sizeof(std::function<void()>) == 32);
  REQUIRE(sizeof(std::function<void(int)>) == 32);
  REQUIRE(sizeof(std::function<int(int, int)>) == 32);
  REQUIRE(sizeof(std::function<int(int, std::string, std::string, std::string)>) == 32);

  // TODO(curoky):
  // https://stackoverflow.com/questions/37481767/why-does-a-lambda-have-a-size-of-1-byte
  auto f_empty = []() {};
  auto f_with_args = [](int) -> int { return 1; };
  auto f_with_ref = [&](int) -> int { return 1; };
  REQUIRE(sizeof(f_empty) == 1);
  REQUIRE(sizeof(f_with_args) == 1);
  REQUIRE(sizeof(f_with_ref) == 1);
  REQUIRE(sizeof(&f_empty) == 8);
  REQUIRE(sizeof(&f_empty) == 8);

  // TODO(curoky): https://www.oschina.net/translate/wide-pointers
  REQUIRE(sizeof(&Test::foo) == 16);
  REQUIRE(folly::demangle(typeid(&Test::foo).name()) == "void ((anonymous namespace)::Test::*)()");
  REQUIRE(sizeof(&Test::boo) == 8);
  REQUIRE(folly::demangle(typeid(&Test::boo).name()) == "void (*)()");
}

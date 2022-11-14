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
#include <glaze/glaze.hpp>

#include <string>
#include <string_view>

namespace {
struct my_struct {
  int i = 287;
  double d = 3.14;
  std::string hello = "Hello World";
  std::array<uint64_t, 3> arr = {1, 2, 3};
};
}  // namespace
template <>
struct glz::meta<my_struct> {
  using T = my_struct;
  static constexpr auto value = object("i", &T::i, "d", &T::d, "hello", &T::hello, "arr", &T::arr);
};

TEST_CASE("basic usage", "[glaze]") {
  my_struct s;
  std::string data = glz::write_json(s);
  REQUIRE(data == R"~({"i":287,"d":3.14,"hello":"Hello World","arr":[1,2,3]})~");

  my_struct s1 = glz::read_json<my_struct>(data);
  REQUIRE(s.i == s1.i);
  REQUIRE(s.d == s1.d);
  REQUIRE(s.hello == s1.hello);
  REQUIRE(s.arr == s1.arr);

  // JSON Pointer Syntax
  REQUIRE(glz::get<double>(s, "/d") == 3.14);
  REQUIRE(glz::set(s, "/d", 42.0));
  REQUIRE(glz::get<double>(s, "/d") == 42.0);
  // JSON Pointer Syntax: tuple example
  auto tuple = std::make_tuple(3, 2.7, std::string("curry"));
  glz::set(tuple, "/0", 5);
  REQUIRE(std::get<0>(tuple) == 5.0);
}

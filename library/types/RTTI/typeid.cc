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

#include <cstdint>
#include <string>
#include <typeinfo>

using namespace std::string_literals;  // NOLINT

TEST_CASE("basic type", "[Typeid]") {
  REQUIRE(typeid(char).name() == "c"s);
  REQUIRE(typeid(signed char).name() == "a"s);
  REQUIRE(typeid(unsigned char).name() == "h"s);

  REQUIRE(typeid(bool).name() == "b"s);

  REQUIRE(typeid(int).name() == "i"s);
  REQUIRE(typeid(signed int).name() == "i"s);
  REQUIRE(typeid(unsigned int).name() == "j"s);

  REQUIRE(typeid(short).name() == "s"s);      // NOLINT
  REQUIRE(typeid(short int).name() == "s"s);  // NOLINT
  REQUIRE(typeid(long).name() == "l"s);       // NOLINT
  REQUIRE(typeid(long long).name() == "x"s);  // NOLINT

  REQUIRE(typeid(long int).name() == "l"s);       // NOLINT
  REQUIRE(typeid(long long int).name() == "x"s);  // NOLINT

  REQUIRE(typeid(float).name() == "f"s);
  REQUIRE(typeid(double).name() == "d"s);
  REQUIRE(typeid(long double).name() == "e"s);

  REQUIRE(typeid(int8_t).name() == "a"s);
  REQUIRE(typeid(int16_t).name() == "s"s);
  REQUIRE(typeid(int32_t).name() == "i"s);
  REQUIRE(typeid(int64_t).name() == "l"s);

  REQUIRE(typeid(const int).name() == "i"s);
  REQUIRE(typeid(int *).name() == "Pi"s);
  REQUIRE(typeid(int const *).name() == "PKi"s);
  REQUIRE(typeid(int *const).name() == "Pi"s);
  REQUIRE(typeid(int const *const).name() == "PKi"s);
  REQUIRE(typeid(int &).name() == "i"s);
  REQUIRE(typeid(const int &).name() == "i"s);
}

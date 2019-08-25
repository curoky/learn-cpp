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

#include <bitset>
#include <string>

TEST_CASE("test Shift", "[Shift]") {
  int value = -1;
  REQUIRE(std::bitset<32>(value).to_string() == "11111111111111111111111111111111");
  REQUIRE(std::bitset<32>(value << 1).to_string() == "11111111111111111111111111111110");
  REQUIRE(value >> 1 == value);
  REQUIRE(std::bitset<32>(value >> 1).to_string() == "11111111111111111111111111111111");
}

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

#include <better-enums/enum.h>
#include <catch2/catch_test_macros.hpp>

#include <string>

namespace {
BETTER_ENUM(Color, int, Red = 1, Green = 2, Blue = 3, Cyan = 4, Magenta = 5, Yellow = 6, Black = 7,
            White = 8)
}

TEST_CASE("[better-enum]: basic usage") {
  Color c = Color::Red;
  REQUIRE(c._to_string() == std::string("Red"));
  REQUIRE(Color::_from_string("Red") == +Color::Red);
  REQUIRE(c._size() == 8);
}

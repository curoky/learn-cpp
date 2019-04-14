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

#include <assert.h>
#include <catch2/catch_test_macros.hpp>
#include <peglib.h>

#include <any>
#include <string_view>
#include <vector>

TEST_CASE("[Cpp-peglib]: basic usage") {
  // (2) Make a parser
  peg::parser parser(R"(
        # Grammar for Calculator...
        Additive    <- Multitive '+' Additive / Multitive
        Multitive   <- Primary '*' Multitive / Primary
        Primary     <- '(' Additive ')' / Number
        Number      <- < [0-9]+ >
        %whitespace <- [ \t]*
    )");

  assert(static_cast<bool>(parser) == true);

  // (3) Setup actions
  parser["Additive"] = [](const peg::SemanticValues& sv) {
    switch (sv.choice()) {
      case 0:  // "Multitive '+' Additive"
        return std::any_cast<int>(sv[0]) + std::any_cast<int>(sv[1]);
      default:  // "Multitive"
        return std::any_cast<int>(sv[0]);
    }
  };

  parser["Multitive"] = [](const peg::SemanticValues& sv) {
    switch (sv.choice()) {
      case 0:  // "Primary '*' Multitive"
        return std::any_cast<int>(sv[0]) * std::any_cast<int>(sv[1]);
      default:  // "Primary"
        return std::any_cast<int>(sv[0]);
    }
  };

  parser["Number"] = [](const peg::SemanticValues& sv) { return sv.token_to_number<int>(); };

  // (4) Parse
  parser.enable_packrat_parsing();  // Enable packrat parsing.

  int val;
  parser.parse(" (1 + 2) * 3 ", val);

  assert(val == 9);
}

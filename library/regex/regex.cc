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

#include <regex>
#include <string>
#include <vector>

TEST_CASE("MatchTest", "[Regex]") {
  std::string target = "abcdabcd";
  const std::regex pattern("abc[a-z]",
                           std::regex_constants::ECMAScript | std::regex_constants::icase);
  std::smatch match_result;

  // 尽可能的完整匹配
  REQUIRE(std::regex_match(target, match_result, pattern) == false);
  REQUIRE(match_result.size() == 0);

  // 第一个匹配
  REQUIRE(std::regex_search(target, match_result, pattern) == true);
  REQUIRE(match_result.size() == 1);
  REQUIRE(match_result[0].str() == "abcd");

  // 全部的匹配
  // default constructor = end-of-sequence:
  std::sregex_token_iterator rend;
  for (auto iter = std::sregex_token_iterator(target.begin(), target.end(), pattern); iter != rend;
       ++iter) {
    REQUIRE(iter->str() == "abcd");
  }
}

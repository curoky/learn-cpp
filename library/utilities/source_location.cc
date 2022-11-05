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
#include <catch2/matchers/catch_matchers_string.hpp>

#include <source_location>
#include <string>
#include <string_view>
#include <vector>

std::vector<std::string> log(std::string_view message, const std::source_location& location =
                                                           std::source_location::current()) {
  std::vector<std::string> res;
  res.push_back(location.file_name());
  res.push_back(std::to_string(location.line()));
  res.push_back(std::to_string(location.column()));
  res.push_back(location.function_name());
  return res;
}

TEST_CASE("basic usage", "[SourceLocation]") {
  auto ret = log("hahaha");
  REQUIRE(ret.size() == 4);
  REQUIRE_THAT(ret[0], Catch::Matchers::EndsWith("source_location.cc"));
  REQUIRE(ret[1] == "47");
#if __GNUG__ == 11
  REQUIRE(ret[2] == "17");
  REQUIRE(ret[3] == "void CATCH2_INTERNAL_TEST_0()");
  // REQUIRE(ret[3] == "void ____C_A_T_C_H____T_E_S_T____0()");
#else
  REQUIRE(ret[2] == "0");
  REQUIRE(ret[3] == "CATCH2_INTERNAL_TEST_0");
#endif
}

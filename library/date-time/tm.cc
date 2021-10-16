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

#include <chrono>
#include <iomanip>

TEST_CASE("get-time", "[time]") {
  std::tm t = {};
  std::istringstream ss("2022-06-06");
  ss >> std::get_time(&t, "%Y-%m-%d");
  REQUIRE_FALSE(ss.fail());
  CHECK(t.tm_year == 122);  // -1900
  CHECK(t.tm_mon == 5);     // 0-11
  CHECK(t.tm_mday == 6);
}

TEST_CASE("<=> time_t", "[time]") {
  std::tm t_tm;
  std::time_t t_time = std::mktime(&t_tm);

  t_tm = *std::localtime(&t_time);
}

TEST_CASE("calculate", "[time]") {
  SECTION("v1") {
    std::tm last_tm = {};
    std::istringstream ss("2022-06-06");
    ss >> std::get_time(&last_tm, "%Y-%m-%d");
    REQUIRE_FALSE(ss.fail());
    std::chrono::system_clock::time_point last_time =
        std::chrono::system_clock::from_time_t(std::mktime(&last_tm));
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::days d = std::chrono::duration_cast<std::chrono::days>(now - last_time);
    // REQUIRE(d.count() == 1);
  }
}

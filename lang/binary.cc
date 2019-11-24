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
#include <stdint.h>

#include <bitset>
#include <sstream>
#include <string>

#define GET_STR(value, content)   \
  do {                            \
    std::stringstream ss;         \
    ss << value;                  \
    REQUIRE(ss.str() == content); \
  } while (0);

TEST_CASE("example", "[binary]") {
  GET_STR(std::bitset<4>(5), "0101");

  {
    char ch = '1';
    REQUIRE(*reinterpret_cast<int8_t*>(&ch) == (int8_t)ch);
    GET_STR(std::bitset<4>(ch), "0001");
  }

  {
    char ch[2] = {1, 2};
    GET_STR(std::bitset<16>(*reinterpret_cast<int16_t*>(&ch)), "0000001000000001");
  }
}

TEST_CASE("endian", "[binary]") {
  {
    int32_t a = 1;
    char* buf = reinterpret_cast<char*>(&a);
    // CHECK(fmt::format("{:p}", buf) == "123");
    // CHECK(fmt::format("{:p}", &buf[0]) == "123");
    // CHECK(fmt::format("{:p}", &buf[1]) == "123");
    // CHECK(fmt::format("{:p}", &buf[2]) == "123");
    // CHECK(fmt::format("{:p}", &buf[3]) == "123");
    REQUIRE(buf[0] == 1);
    REQUIRE(buf[1] == 0);
    REQUIRE(buf[2] == 0);
    REQUIRE(buf[3] == 0);
  }

  {
    char buf[4] = {'1', '2', '3', '4'};
    int32_t a = *reinterpret_cast<int32_t*>(&buf);
    REQUIRE(a == ('1' | '2' << 8 | '3' << 16 | '4' << 24));
  }
}

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

// FIXME: don't work with clang++-9
#if !defined(__clang__)

#include "typename.h"

#include <catch2/catch_test_macros.hpp>

#include <any>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <variant>
#include <vector>

#define CHECK_TYPE(...) REQUIRE((type_name<__VA_ARGS__>()) == #__VA_ARGS__);
// #define CHECK_TYPE(type) EXPECT_EQ(type_name<type>(), #type);

TEST_CASE("[Typename]: base test") {
  using mox::type::type_name;
  // CHECK_TYPE(short);
  CHECK_TYPE(int);
  CHECK_TYPE(short int);
  CHECK_TYPE(long int);
  CHECK_TYPE(long long int);
  CHECK_TYPE(std::string);
  CHECK_TYPE(std::set<std::string>);

  CHECK_TYPE(std::set<std::vector<std::string>>);
  CHECK_TYPE(std::any);
  CHECK_TYPE(std::map<int, int>);
  CHECK_TYPE(std::unordered_map<int, int>);
  CHECK_TYPE(std::map<std::string, std::set<std::string>>);
  // CHECK_TYPE(std::variant<std::string>);
}

#endif

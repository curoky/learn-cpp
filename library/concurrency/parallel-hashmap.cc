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
#include <parallel_hashmap/phmap.h>

#include <iostream>
#include <string>
#include <utility>

TEST_CASE("[Parallel-hashmap]: basic usage") {
  // Create an unordered_map of three strings (that map to strings)
  phmap::flat_hash_map<std::string, std::string> email = {
      {"tom", "tom@gmail.com"}, {"jeff", "jk@gmail.com"}, {"jim", "jimg@microsoft.com"}};

  // Iterate and print keys and values
  for (const auto& n : email) std::cout << n.first << "'s email is: " << n.second << "\n";

  // Add a new entry
  email["bill"] = "bg@whatever.com";

  // and print it
  std::cout << "bill's email is: " << email["bill"] << "\n";
}

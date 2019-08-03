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

#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main(int argc, char const *argv[]) {
  std::list<int> int_list = {1, 2, 3, 4, 5};
  std::vector<int> int_vector = {1, 2, 3, 4, 5};
  std::set<int> int_set = {1, 2, 3, 4, 5};
  std::unordered_set<int> int_unordered_set = {1, 2, 3, 4, 5};
  std::queue<int> int_queue({1, 2, 3, 4, 5});

  std::list<std::string> string_list = {"1", "2", "3", "4", "5"};
  std::vector<std::string> string_vector = {"1", "2", "3", "4", "5"};
  std::set<std::string> string_set = {"1", "2", "3", "4", "5"};
  std::unordered_set<std::string> string_unordered_set = {"1", "2", "3", "4", "5"};
  std::queue<std::string> string_queue({"1", "2", "3", "4", "5"});

  std::map<std::string, int> string_int_map = {{"1", 1}, {"2", 2}, {"2", 2}};
  std::unordered_map<std::string, int> string_int_unordered_map = {{"1", 1}, {"2", 2}, {"2", 2}};

  (void)0;
  (void)0;
  (void)0;
  (void)0;
  (void)0;
  (void)0;
  return 0;
}

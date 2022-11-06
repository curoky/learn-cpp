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
#include <jemalloc/jemalloc.h>

#include <any>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <template <typename> typename T>
auto createContainer() {
  auto ret = T<std::string>();
  for (size_t i = 0; i < 10000; i++) {
    ret.push_back(std::to_string(i));
  }
  return ret;
}

auto insertToTrash(std::list<std::any> &g) {
  g.push_back(createContainer<std::vector>());
  g.push_back(createContainer<std::deque>());
  g.push_back(createContainer<std::list>());
}

void dumpProfile(const char *fileName) {
  mallctl("prof.dump", NULL, NULL, &fileName, sizeof(const char *));
}

int main(int argc, char const *argv[]) {
  // malloc directly
  for (size_t i = 0; i < 1000; i++) {
    malloc(i * 100);
  }
  dumpProfile("malloc.directly");

  std::list<std::any> g;
  for (size_t i = 0; i < 30; i++) {
    insertToTrash(g);
  }
  dumpProfile("malloc.container");

  return 0;
}

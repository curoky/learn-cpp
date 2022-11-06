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
#include <stdlib.h>

// https://github.com/jemalloc/jemalloc/wiki/Getting-Started
// https://github.com/jemalloc/jemalloc/wiki/Use-Case%3A-Basic-Allocator-Statistics

void do_something(size_t i) {
  // Leak some memory.
  malloc(i * 100);
}

int main(int argc, char **argv) {
  for (size_t i = 0; i < 1000; i++) {
    do_something(i);
  }

  // Dump allocator statistics to stderr.
  malloc_stats_print(NULL, NULL, NULL);
  return 0;
}

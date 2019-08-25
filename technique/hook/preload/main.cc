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

#include <stdlib.h>
#include <time.h>

#include <iostream>

int main(int argc, char const *argv[]) {
  time_t t = time(NULL);
  int r = rand();  // NOLINT
  std::cout << "time: " << t << std::endl;
  std::cout << "rand: " << r << std::endl;  // NOLINT

  char *str = static_cast<char *>(malloc(15));
  std::cout << "malloc: " << (void *)str << std::endl;  // NOLINT

  std::cout << "free: " << std::endl;  // NOLINT
  free(str);
  return 0;
}
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

#include <iostream>
#include <thread>

const int MB = 1024 * 1024;

void test() {
  [[maybe_unused]] char buf[1 * MB];
  static int count = 0;
  std::cout << "count: " << count++ << std::endl;
  test();
}

int main(int argc, char* argv[]) {
  // process stack not effect thread stack
  [[maybe_unused]] char buf[1 * MB];

  // tls stack effect thread stack
  [[maybe_unused]] thread_local char tls_buf[2 * MB];

  std::thread th(test);
  th.join();
  return 0;
}

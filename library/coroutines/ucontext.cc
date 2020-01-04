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
#include <signal.h>
#include <ucontext.h>

#include <vector>

TEST_CASE("loop", "[ucontext]") {
  size_t loop_count = 0;
  ucontext_t context;
  getcontext(&context);
  // THINK: what will happend when getcontext before loop_count define.
  loop_count += 1;
  if (loop_count < 3) {
    setcontext(&context);
  }
  REQUIRE(loop_count == 3);
}

namespace {
std::vector<int> behiver_list;
#define MARK_STEP(x) behiver_list.push_back(x);

void func() { MARK_STEP(3); }

}  // namespace

TEST_CASE("coro", "[ucontext]") {
  char stack[1024 * 128];
  ucontext_t child, main;
  MARK_STEP(0);
  getcontext(&child);
  child.uc_stack.ss_sp = stack;
  child.uc_stack.ss_size = sizeof(stack);
  child.uc_stack.ss_flags = 0;
  child.uc_link = &main;  // THINK: what happend when set to NULL?
  MARK_STEP(1);
  makecontext(&child, func, 0);
  MARK_STEP(2);
  swapcontext(&main, &child);
  MARK_STEP(4);

  REQUIRE(behiver_list == std::vector<int>({0, 1, 2, 3, 4}));
}

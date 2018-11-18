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
#include <cxxabi.h>

#include <functional>
#include <future>
#include <memory>
#include <thread>
#include <utility>

namespace {
int add(int a, int b) { return a + b; }
}  // namespace

TEST_CASE("LambdaTest", "[PackagedTask]") {
  // 使用 lambda 函数构建 packaged_task，在当前线程执行
  std::packaged_task<int(int, int)> task([](int a, int b) { return a + b; });
  std::future<int> result = task.get_future();
  task(1, 2);
  REQUIRE(result.get() == 3);
}

TEST_CASE("BindTest", "[PackagedTask]") {
  // 使用 bind 构建 packaged_task，在当前线程执行
  std::packaged_task<int()> task(std::bind(add, 1, 2));
  std::future<int> result = task.get_future();
  task();
  REQUIRE(result.get() == 3);
}

TEST_CASE("ThreadTest", "[PackagedTask]") {
  // 在其它 thread 执行 packaged_task
  std::packaged_task<int(int, int)> task(add);
  std::future<int> result = task.get_future();
  std::thread task_td(std::move(task), 1, 2);
  task_td.join();
  REQUIRE(result.get() == 3);
}

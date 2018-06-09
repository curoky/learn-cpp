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

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <stdint.h>

#include <memory>

std::uint64_t Fibonacci(std::uint64_t number) {
  return number < 2 ? 1 : Fibonacci(number - 1) + Fibonacci(number - 2);
}

TEST_CASE("Fibonacci") {
  REQUIRE(Fibonacci(0) == 1);
  // some more asserts..
  REQUIRE(Fibonacci(5) == 8);
  // some more asserts..

  // now let's benchmark:
  BENCHMARK("Fibonacci 20") { return Fibonacci(20); };

  BENCHMARK("Fibonacci 25") { return Fibonacci(25); };

  BENCHMARK("Fibonacci 30") { return Fibonacci(30); };

  BENCHMARK("Fibonacci 35") { return Fibonacci(35); };
}

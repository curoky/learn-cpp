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

#include <benchmark/benchmark.h>
#include <folly/FBVector.h>
#include <folly/small_vector.h>

#include <vector>

#include "absl/container/inlined_vector.h"

template <class Vector>
void BM_vector_construct(benchmark::State& state) {
  for (auto _ : state) {
    {
      Vector vec(state.range(0));
      benchmark::DoNotOptimize(vec);
      state.PauseTiming();
    }
    state.ResumeTiming();
  }
}

template <class Vector>
void BM_vector_reserve(benchmark::State& state) {
  for (auto _ : state) {
    {
      Vector vec;
      vec.reserve(state.range(0));
      benchmark::DoNotOptimize(vec);
      state.PauseTiming();
    }
    state.ResumeTiming();
  }
}

template <class Vector>
void BM_vector_copy(benchmark::State& state) {
  Vector vec(state.range(0));
  for (auto _ : state) {
    {
      Vector v = vec;
      benchmark::DoNotOptimize(v);
      state.PauseTiming();
    }
    state.ResumeTiming();
  }
}

BENCHMARK_TEMPLATE(BM_vector_construct, std::vector<int>)->RangeMultiplier(64)->Range(1, 1 << 24);
BENCHMARK_TEMPLATE(BM_vector_construct, folly::fbvector<int>)
    ->RangeMultiplier(64)
    ->Range(1, 1 << 24);
BENCHMARK_TEMPLATE(BM_vector_construct, absl::InlinedVector<int, 1 << 12>)
    ->RangeMultiplier(64)
    ->Range(1, 1 << 24);
BENCHMARK_TEMPLATE(BM_vector_construct, folly::small_vector<int, 1 << 12>)
    ->RangeMultiplier(64)
    ->Range(1, 1 << 24);

BENCHMARK_TEMPLATE(BM_vector_reserve, std::vector<int>)->RangeMultiplier(64)->Range(1, 1 << 24);
BENCHMARK_TEMPLATE(BM_vector_reserve, folly::fbvector<int>)->RangeMultiplier(64)->Range(1, 1 << 24);

BENCHMARK_TEMPLATE(BM_vector_copy, std::vector<int>)->RangeMultiplier(64)->Range(1, 1 << 24);
BENCHMARK_TEMPLATE(BM_vector_copy, folly::fbvector<int>)->RangeMultiplier(64)->Range(1, 1 << 24);
BENCHMARK_TEMPLATE(BM_vector_copy, absl::InlinedVector<int, 1 << 12>)
    ->RangeMultiplier(64)
    ->Range(1, 1 << 24);
BENCHMARK_TEMPLATE(BM_vector_copy, folly::small_vector<int, 1 << 12>)
    ->RangeMultiplier(64)
    ->Range(1, 1 << 24);

BENCHMARK_MAIN();

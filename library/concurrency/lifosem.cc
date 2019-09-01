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
#include <folly/synchronization/LifoSem.h>

#include <atomic>
#include <ostream>
#include <thread>

#include "glog/logging.h"  // for COMPACT_GOOGLE_LOG_INFO, LOG, LogMessage

// LifoSemBase 是几种不同类型的LIFO信号量的引擎。
// LifoSemBase 处理正信号量值和等待节点的存储，但是实际的等待和通知机制取决于客户端。
// 切换类型负责安排一个唤醒通知。

TEST_CASE("lifosem basic usage", "[folly]") {
  // 最简单的使用测试
  folly::LifoSem sem;
  REQUIRE_FALSE(sem.tryWait());

  sem.post();
  REQUIRE(sem.tryWait());

  sem.post();
  sem.wait();
}

TEST_CASE("lifosem multi thread", "[folly]") {
  // 多线程测试
  // 模拟场景：n个线程陷入等待，然后触发一次 post，n 个线程依次完成退出

  folly::LifoSem sem;

  const int opsPerThread = 10000;
  std::thread threads[10];
  std::atomic<int> blocks(0);

  for (auto& thr : threads) {
    thr = std::thread([&] {
      int b = 0;
      for (int i = 0; i < opsPerThread; ++i) {
        if (!sem.tryWait()) {
          sem.wait();
          ++b;
        }
        sem.post();
      }
      blocks += b;
    });
  }

  // start the flood
  sem.post();

  for (auto& thr : threads) {
    thr.join();
  }

  LOG(INFO) << opsPerThread * sizeof(threads) / sizeof(threads[0]) << " post/wait pairs, " << blocks
            << " blocked";
}

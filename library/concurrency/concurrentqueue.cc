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

#include <blockingconcurrentqueue.h>
#include <catch2/catch_test_macros.hpp>
#include <concurrentqueue.h>

#include <chrono>
#include <thread>

TEST_CASE("BaseTest", "[Concurrentqueue]") {
  moodycamel::ConcurrentQueue<int> q;
  q.enqueue(25);

  int item;
  bool found = q.try_dequeue(item);
  REQUIRE(found);
  REQUIRE(item == 25);
}

TEST_CASE("BlockTest", "[Concurrentqueue]") {
  moodycamel::BlockingConcurrentQueue<int> q;
  std::thread producer([&]() {
    for (int i = 0; i != 100; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(i % 10));
      q.enqueue(i);
    }
  });
  std::thread consumer([&]() {
    for (int i = 0; i != 100; ++i) {
      int item;
      q.wait_dequeue(item);
      REQUIRE(item == i);

      if (q.wait_dequeue_timed(item, std::chrono::milliseconds(5))) {
        ++i;
        REQUIRE(item == i);
      }
    }
  });
  producer.join();
  consumer.join();
  REQUIRE(q.size_approx() == 0);
}

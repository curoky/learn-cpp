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

#include <pthread.h>
#include <signal.h>
#include <stddef.h>

#include <chrono>
#include <iostream>
#include <thread>

int stop_count = 5;

void __signal_handler__(int sig_num) {
  char threadName[64];
  pthread_getname_np(pthread_self(), threadName, sizeof(threadName));
  pthread_t tid = pthread_self();
  std::cerr << "[signal_handler] signal process, tid:" << tid << " signal:" << sig_num << std::endl;
  stop_count -= 1;
}

int main(int argc, char const *argv[]) {
  pthread_join((pthread_t)139791566890752, NULL);
  // pthread_kill((pthread_t)139791566890752,SIGINT);
  signal(SIGINT, __signal_handler__);
  while (stop_count > 0) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}

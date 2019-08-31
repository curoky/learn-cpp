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
#ifndef __clang__
// #include <folly/experimental/symbolizer/Symbolizer.h>
// #define BOOST_STACKTRACE_USE_WINDBG_CACHED
#include <folly/Format.h>
#define BOOST_STACKTRACE_USE_BACKTRACE
#define BOOST_STACKTRACE_USE_ADDR2LINE

#include <backtrace.h>
#include <boost/stacktrace.hpp>

#include <iostream>

void func0(int a) {
  boost::stacktrace::stacktrace st;
  for (boost::stacktrace::frame frame : st) {
    auto line = folly::sformat("[{}]-{}:{}:{}", frame.address(), frame.source_file(),
                               frame.source_line(), frame.name());
    std::cout << line << std::endl;
  }

  std::cout << "a: " << a << std::endl;
}

void func1(int b) { func0(b); }

inline void func2(int c) { func1(c); }

int main(int argc, char const *argv[]) {
  func2(1);
  return 0;
}

#endif

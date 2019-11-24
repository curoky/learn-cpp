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
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include <string>

#define WANT_ERROR(x) CHECK(std::string(strerror(errno)) == x);

TEST_CASE("basic usage", "[eventfd]") {
  int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  REQUIRE(evtfd > 0);

  int code32 = 100;
  REQUIRE(sizeof(code32) == 4);
  REQUIRE(write(evtfd, &code32, 4) == -1);
  WANT_ERROR("Invalid argument");

  int64_t code64 = 100;
  REQUIRE(sizeof(code64) == 8);
  REQUIRE(write(evtfd, &code64, 8) == 8);

  char buf8[8] = "1\0\0\0\0\0\0";
  // REQUIRE(reinterpret_cast<int64_t>(buf8) == 2);
  REQUIRE(write(evtfd, buf8, 8) == 8);

  char buf7[7];
  REQUIRE(sizeof(buf7) == 7);
  REQUIRE(read(evtfd, &buf7, 7) == -1);
  WANT_ERROR("Invalid argument");

  int64_t code64_2 = 0;
  REQUIRE(read(evtfd, &code64_2, 8) == 8);
  REQUIRE(code64_2 == 149);  // 149 = 100 + 49
}

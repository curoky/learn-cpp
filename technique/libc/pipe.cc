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
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <string>

#define WANT_ERROR(x) CHECK(std::string(strerror(errno)) == x);

TEST_CASE("basic usage", "[pipe]") {
  int pipefd[2];
  // pipefd[0] for reading
  // pipefd[1] for writing

  int err = pipe2(pipefd, O_NONBLOCK);
  REQUIRE(err == 0);

  char buf;
  REQUIRE(read(pipefd[0], &buf, 1) == -1);
  WANT_ERROR("Resource temporarily unavailable");

  REQUIRE(write(pipefd[1], &buf, 1) == 1);
  REQUIRE(read(pipefd[0], &buf, 1) == 1);
  REQUIRE(read(pipefd[0], &buf, 1) == -1);
  WANT_ERROR("Resource temporarily unavailable");

  REQUIRE(write(pipefd[0], &buf, 1) == -1);
  WANT_ERROR("Bad file descriptor");

  REQUIRE(read(pipefd[1], &buf, 1) == -1);
  WANT_ERROR("Bad file descriptor");
}

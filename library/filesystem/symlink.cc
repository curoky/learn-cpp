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

#include <chrono>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

TEST_CASE("CreateTest", "[Symlink]") {
  fs::create_directories("/tmp/sandbox/subdir");
  fs::create_symlink("/tmp/target", "/tmp/sandbox/sym1");
  fs::create_directory_symlink("/tmp/subdir", "/tmp/sandbox/sym2");

  for (auto& p : fs::directory_iterator("/tmp/sandbox")) {
    if (fs::is_symlink(p.symlink_status())) {
      std::cout << p.path() << "->" << fs::read_symlink(p.path()) << '\n';
    }
  }
  REQUIRE(fs::read_symlink("/tmp/sandbox/sym1") == "/tmp/target");
  REQUIRE(fs::read_symlink("/tmp/sandbox/sym2") == "/tmp/subdir");

  fs::remove_all("/tmp/sandbox");
}

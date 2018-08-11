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
#include <cstdlib>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

TEST_CASE("base test", "[Path]") {
  fs::path now_path = fs::current_path();
  fs::path sandbox = "sandbox/a/b/c";

  REQUIRE(fs::absolute(sandbox) == now_path / sandbox);

  fs::path abs_sandbox = fs::absolute(sandbox);
  REQUIRE(abs_sandbox.root_path() == "/");
  REQUIRE(abs_sandbox.root_directory() == "/");
  REQUIRE(abs_sandbox.root_name() == "");
  REQUIRE(abs_sandbox.parent_path() == now_path / "sandbox" / "a" / "b");
  REQUIRE(sandbox.relative_path() == sandbox);
}

TEST_CASE("temp_dir", "[Path]") {
  char* tmp_dir = std::getenv("TMPDIR");
  if (tmp_dir != nullptr) {
    REQUIRE(fs::temp_directory_path() == tmp_dir);
  }
}

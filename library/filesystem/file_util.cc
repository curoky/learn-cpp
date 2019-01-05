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
#include <catch2/matchers/catch_matchers_string.hpp>
#include <folly/FBString.h>
#include <folly/FileUtil.h>

#include <memory>

TEST_CASE("read file", "[FileUtil]") {
  folly::fbstring content;
  bool status = folly::readFile("/proc/sys/kernel/ostype", content);
  REQUIRE(status == true);
  REQUIRE_THAT(content.toStdString(), Catch::StartsWith("Linux"));

  // file not found
  status = folly::readFile("/proc/sys/kernel/ostype.2333", content);
  REQUIRE(status == false);
}

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
#include <crc32c/crc32c.h>
#include <stdint.h>

#include <string>
#include <string_view>

TEST_CASE("simple test", "[Crc32c]") {
  // Process a raw buffer.
  const std::uint8_t buffer[] = {48, 48, 48, 48};
  REQUIRE(crc32c::Crc32c(buffer, 4) == 2540516317);

  // Process a std::string.
  std::string string = "0000";
  REQUIRE(crc32c::Crc32c(string) == 2540516317);

  // If you have C++17 support, process a std::string_view.
  std::string_view string_view(string);
  REQUIRE(crc32c::Crc32c(string_view) == 2540516317);
}

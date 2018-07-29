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
#include <snappy.h>

#include <string>

// https://github.com/google/snappy/blob/master/README.md

TEST_CASE("compression and decompress", "[Snappy]") {
  std::string data = "hello world";
  std::string compressed;
  std::string decompressed;

  snappy::Compress(data.data(), data.size(), &compressed);
  snappy::Uncompress(compressed.data(), compressed.size(), &decompressed);

  REQUIRE(decompressed == data);
}

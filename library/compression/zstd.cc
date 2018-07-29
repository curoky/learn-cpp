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
#include <stdlib.h>
#include <zstd.h>

#include <string>

// using namespace std::string_literals;
// http://facebook.github.io/zstd/zstd_manual.html#Chapter3
// https://github.com/facebook/zstd/blob/dev/examples/simple_compression.c
// https://github.com/facebook/zstd/blob/dev/examples/simple_decompression.c

TEST_CASE("compression and decompress", "[Zstd]") {
  std::string data = "hello world";

  // compress
  const void* compress_src = data.data();
  size_t compress_src_size = data.size();
  size_t compress_dst_cap = ZSTD_compressBound(compress_src_size);
  void* compress_dst = malloc(compress_dst_cap);
  size_t compress_dst_size = ZSTD_compress(compress_dst, compress_dst_cap, compress_src,
                                           compress_src_size, /*compressionLevel=*/1);

  // decompress
  const void* decompress_src = compress_dst;
  size_t decompress_src_size = compress_dst_size;
  size_t decompress_dst_size = ZSTD_getFrameContentSize(decompress_src, decompress_src_size);
  void* decompress_dst = malloc(decompress_dst_size);
  size_t dSize =
      ZSTD_decompress(decompress_dst, decompress_dst_size, decompress_src, decompress_src_size);

  REQUIRE(dSize == decompress_dst_size);
  // FIXME: use strcmp to compare
  // REQUIRE((char*)decompress_dst == data);

  free(compress_dst);
  free(decompress_dst);
}

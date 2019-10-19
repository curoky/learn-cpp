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

#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>
#include <bitsery/traits/vector.h>
#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <utility>
#include <vector>

enum class MyEnum : uint16_t { V1, V2, V3 };
struct MyStruct {
  uint32_t i;
  MyEnum e;
  std::vector<float> fs;
};

template <typename S>
void serialize(S& s, MyStruct& o) {
  s.value4b(o.i);
  s.value2b(o.e);
  s.container4b(o.fs, 10);
}

using Buffer = std::vector<uint8_t>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;
using InputAdapter = bitsery::InputBufferAdapter<Buffer>;

TEST_CASE("basic usage", "[Bitsery]") {
  MyStruct data{8941, MyEnum::V2, {15.0f, -8.5f, 0.045f}};
  MyStruct res{};

  Buffer buffer;

  auto writtenSize = bitsery::quickSerialization<OutputAdapter>(buffer, data);
  auto state = bitsery::quickDeserialization<InputAdapter>({buffer.begin(), writtenSize}, res);

  REQUIRE(state.first == bitsery::ReaderError::NoError);
  REQUIRE(state.second);
  REQUIRE(data.fs == res.fs);
  REQUIRE(data.i == res.i);
  REQUIRE(data.e == res.e);
}

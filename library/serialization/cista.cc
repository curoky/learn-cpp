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

#include <assert.h>
#include <catch2/catch_test_macros.hpp>
#include <cista.h>

#include <vector>

namespace data = cista::raw;
struct my_struct {  // Define your struct.
  int a_{0};
  struct inner {
    data::string b_;
  } j;
};

TEST_CASE("basic usage", "[cista]") {
  std::vector<unsigned char> buf;
  {  // Serialize.
    my_struct obj{1, {data::string{"test"}}};
    buf = cista::serialize(obj);
  }
  // Deserialize.
  auto deserialized = cista::deserialize<my_struct>(buf);
  assert(deserialized->j.b_ == data::string{"test"});
}

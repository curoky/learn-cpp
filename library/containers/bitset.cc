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

#include <bitset>

TEST_CASE("basic usage", "[Bitset]") {
  std::bitset<8> b;
  // b.test(11);

  // REQUIRE(b == "11111111");
  // std::cout << b << '\n';
  // std::cout << b.set() << '\n';
  // std::cout << b.reset() << '\n';

  // for (size_t i = 1; i < b.size(); i += 2) {
  //   b.set(i);
  // }
  // std::cout << b << '\n';
}

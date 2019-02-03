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

TEST_CASE("base test", "[Destructor]") {
  static int counter = 0;
  static int counter_a = 0;
  static int counter_b = 0;

  class A {
   public:
    ~A() { counter_a = ++counter; }
  };

  class B {
   public:
    ~B() { counter_b = ++counter; }
    A a;
  };

  { B b; }
  REQUIRE(counter_a == 2);
  REQUIRE(counter_b == 1);
}

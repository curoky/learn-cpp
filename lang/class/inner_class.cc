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

#include <memory>

class OuterClass {
 public:
  // 内部类默认就是友元类
  class InnerClass {
   public:
    OuterClass get_outer() { return OuterClass(); }
    std::shared_ptr<OuterClass> get_outer_ptr() {
      return std::shared_ptr<OuterClass>(new OuterClass());
    }
  };

 private:
  OuterClass() {}
};

TEST_CASE("base test", "[InnerClass]") {
  OuterClass::InnerClass inner;
  inner.get_outer();
  REQUIRE(inner.get_outer_ptr() != nullptr);
}

template <typename T>
void get_inner_class() {
  auto f = []() {
    // 此处需要 typename 才能编译过
    typename T::InnerClass inner;
    return inner;
  };
  f();
}

TEST_CASE("GetInnerClass", "[InnerClass]") { get_inner_class<OuterClass>(); }

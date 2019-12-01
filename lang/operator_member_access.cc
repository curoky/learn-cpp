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

// https://en.cppreference.com/w/cpp/language/operator_member_access

#include <catch2/catch_test_macros.hpp>

namespace {
void f(int) {}
void f(double) {}
struct A {
  int i;
};
struct B {
  void f() {}
};

}  // namespace

// https://stackoverflow.com/questions/670734/pointer-to-class-data-member
TEST_CASE("[operator_member_access]") {
  int n = 1;
  int* pn = &n;              // pointer
  int* pn2 = &*pn;           // pn2 == pn
  int A::*mp = &A::i;        // pointer to data member
  void (B::*mpf)() = &B::f;  // pointer to member function

  void (*pf)(int) = &f;  // overload resolution due to initialization context
                         //  auto pf2 = &f; // error: ambiguous overloaded function type
  auto pf2 = static_cast<void (*)(int)>(&f);  // overload resolution due to cast
}

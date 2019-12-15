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
#include <rttr/registration.h>
#include <rttr/type.h>

#include <vector>

struct A {
  int a;
  int b;
};

struct B {
  std::vector<A> as;
};

struct C {
  A a;
  B b;
};

RTTR_REGISTRATION {
  rttr::registration::class_<A>("A")
      .property("a", &A::a)(rttr::metadata("thrift", "1,required"))
      .property("b", &A::b)(rttr::metadata("thrift", "2,required"));
  rttr::registration::class_<B>("B").property("as", &B::as);
  rttr::registration::class_<C>("C").property("b", &C::b).property("a", &C::a);
}

TEST_CASE("basic usage", "[rttr]") {
  rttr::type t = rttr::type::get<A>();
  for (auto& prop : t.get_properties()) {
    // REQUIRE(prop.get_name() == "a" || prop.get_name() == "b");
  }
}

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

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "technique/class_utils.h"

TEST_CASE("make_shared with move constructor", "[SharedPtr]") {
  std::string msg = "123";
  auto new_msg = std::make_shared<std::string>(std::move(msg));

  REQUIRE(msg.size() == 0);
  REQUIRE(*new_msg == "123");
}

namespace {
struct A;

struct B {
  ~B() { *destroy = true; }
  std::shared_ptr<A> a;
  bool* destroy;
};
struct A {
  ~A() { *destroy = true; }
  std::shared_ptr<B> b;
  bool* destroy;
};
}  // namespace

TEST_CASE("[SharedPtr]: circular references/dependency") {
  // make circular references
  auto a = std::make_shared<A>();
  a->b = std::make_shared<B>();
  a->b->a = a;

  // add observer when destory
  bool a_destroy = false;
  bool b_destroy = false;
  a->destroy = &a_destroy;
  a->b->destroy = &b_destroy;

  // check refference count
  REQUIRE(a.use_count() == 2);
  REQUIRE(a->b.use_count() == 1);

  // force destory b
  a->b.reset();
  REQUIRE(a->b == nullptr);
  REQUIRE(a.use_count() == 1);
  REQUIRE(b_destroy);

  // force destory b
  a.reset();
  REQUIRE(a == nullptr);
  REQUIRE(a_destroy);
}

TEST_CASE("no initialization", "[SharedPtr]") {
  std::shared_ptr<int> ptr;
  REQUIRE(ptr == nullptr);
}

TEST_CASE("return", "[SharedPtr]") {
  auto make_shared_ptr = [] {
    auto ptr = std::make_shared<int>(1);
    return ptr;
  };
  REQUIRE(*make_shared_ptr() == 1);
}

TEST_CASE("noop deleter", "[SharedPtr]") {
  using mox::ClassMetrics;

  mox::ClassMetrics::Counter counter;
  // int count = 0;
  // mox::ClassMetrics cm;

  // Nofree* nf = new Nofree(count);
  // REQUIRE(count == 1);

  SECTION("with default deleter") {
    std::shared_ptr<ClassMetrics> p1(new ClassMetrics(counter));
    p1.reset();
    REQUIRE(counter.destruct == 1);
  }

  SECTION("with noop deleter") {
    std::shared_ptr<ClassMetrics> p2(new ClassMetrics(counter), [](ClassMetrics*) {});

    auto raw_ptr = p2.get();
    p2.reset();
    REQUIRE(counter.destruct == 0);
    delete raw_ptr;
  }
}

TEST_CASE("conv", "[shared_ptr]") {
  {
    std::shared_ptr<int> ptr(new int(1));
    std::shared_ptr<const int> cptr = ptr;
  }
  {
    std::shared_ptr<std::map<int, int>> ptr;
    // std::shared_ptr<std::map<int, const int>> cptr = ptr;
  }
  {
    std::map<int, std::shared_ptr<int>> ptr;
    // std::map<int, std::shared_ptr<const int>> cptr = ptr;
  }
}

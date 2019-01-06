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
#include <stdint.h>

#include <cstring>
#include <type_traits>

namespace {
struct ClassEmpty {};

struct ClassMember {
  int member;
};

typedef enum {
  _AA = 0x00,
  _BB = 0x01,
} CStyleEnum;

typedef union {
  bool boolean;
  uint64_t u64;
  int64_t i64;
  double f64;
} CStyleUnion;

typedef struct {
  CStyleEnum ienum;
  CStyleUnion iunion;
} ClassMember2;

struct ClassConstructor {
  ClassConstructor() {}
};
struct ClassPrivate {
  int m1;

 private:
  int m2;
};

}  // namespace

TEST_CASE("[Trivial-type]: basic usage") {
  // If T is TrivialType (that is, a scalar type, a trivially copyable class with a trivial
  // default constructor, or array of such type/class, possibly cv-qualified)
  REQUIRE(std::is_trivial_v<int*> == true);
  REQUIRE(std::is_trivial_v<ClassEmpty> == true);
  REQUIRE(std::is_trivial_v<ClassMember> == true);
  REQUIRE(std::is_trivial_v<ClassMember2> == true);
  REQUIRE(std::is_trivial_v<ClassMember2&> == false);
  REQUIRE(std::is_trivial_v<const ClassMember2&> == false);
  REQUIRE(std::is_trivial_v<ClassPrivate> == true);
  REQUIRE(std::is_trivial_v<ClassConstructor> == false);

  ClassMember2 o, v;
  std::memcpy(&o, &v, sizeof(v));
}

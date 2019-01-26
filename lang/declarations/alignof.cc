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

#define Sizeof_Alignof_Equal(type, size) \
  {                                      \
    REQUIRE(sizeof(type) == size);       \
    REQUIRE(alignof(type) == size);      \
  }

#define Sizeof_Alignof_Diff(type, sizeof_size, alignof_size) \
  {                                                          \
    REQUIRE(sizeof(type) == sizeof_size);                    \
    REQUIRE(alignof(type) == alignof_size);                  \
  }

TEST_CASE("different with sizeof", "[Alignof]") {
  // basic type
  Sizeof_Alignof_Equal(char, 1);
  Sizeof_Alignof_Equal(bool, 1);
  Sizeof_Alignof_Equal(short, 2);  // NOLINT
  Sizeof_Alignof_Equal(int, 4);
  Sizeof_Alignof_Equal(int32_t, 4);
  Sizeof_Alignof_Equal(float, 4);
  Sizeof_Alignof_Equal(double, 8);
  Sizeof_Alignof_Equal(int64_t, 8);

  // complex type
  using EnumType = enum { A, B, C };
  using UnionType = union {
    int32_t a;
    double b;
  };
  using StructEmpty = struct {};
  using StructEmpty64 = struct alignas(64) {};
  using StructMember = struct { int m; };  // NOLINT
  using StructMember2 = struct {
    int32_t m;
    int64_t n;
  };

  Sizeof_Alignof_Equal(EnumType, 4);
  Sizeof_Alignof_Equal(UnionType, 8);
  Sizeof_Alignof_Equal(StructEmpty, 1);
  Sizeof_Alignof_Equal(StructEmpty64, 64);
  Sizeof_Alignof_Equal(StructMember, 4);
  Sizeof_Alignof_Diff(StructMember2, 16, 8);
}

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

// https://juejin.im/post/5b39a111f265da59a4020309

#include <catch2/catch_test_macros.hpp>
#include <flatbuffers/flatbuffers.h>
#include <stdint.h>

#include <typeinfo>

#include "library/flatbuffers/tutorial/idl/mock_generated.h"

#define REQUIRE_TYPE(var, type) REQUIRE(typeid(var) == typeid(type));

TEST_CASE("fb type", "[Type]") {
  return;
  flatbuffers::FlatBufferBuilder builder;
  idl::fb::CreateMockRequestDirect(builder);
  const idl::fb::MockRequest* req = idl::fb::GetMockRequest(builder.GetBufferPointer());

  REQUIRE_TYPE(req->var_bool(), bool);
  REQUIRE_TYPE(req->var_byte(), int8_t);
  REQUIRE_TYPE(req->var_ubyte(), uint8_t);
  REQUIRE_TYPE(req->var_short(), int16_t);
  REQUIRE_TYPE(req->var_ushort(), uint16_t);
  REQUIRE_TYPE(req->var_int(), int32_t);
  REQUIRE_TYPE(req->var_uint(), uint32_t);
  REQUIRE_TYPE(req->var_long(), int64_t);
  REQUIRE_TYPE(req->var_ulong(), uint64_t);
  REQUIRE_TYPE(req->var_float(), float);
  REQUIRE_TYPE(req->var_double(), double);
  REQUIRE_TYPE(req->var_string(), const flatbuffers::String*);

  REQUIRE_TYPE(req->var_int_list(), const flatbuffers::Vector<int32_t>*);
  REQUIRE_TYPE(req->var_byte_list(), const flatbuffers::Vector<int8_t>*);
  REQUIRE_TYPE(req->var_string_list(),
               const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>*);
  REQUIRE_TYPE(req->var_enum(), idl::fb::EnumType);
}

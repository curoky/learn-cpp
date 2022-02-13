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

#include "traits.h"  // for is_protobuf_message, is_protobuf_message_v

#include <catch2/catch_test_macros.hpp>

#include <type_traits>

#include "library/protobuf/tutorial/idl/complex.pb.h"  // for complexRequest, complexRequest_EnumType, MockRequest_EnumType_ONE

TEST_CASE("test protobuf", "[traits]") {
  REQUIRE(mox::v1::is_protobuf_message<idl::pb::MockRequest>::value);
  REQUIRE(mox::v2::is_protobuf_message<idl::pb::MockRequest>::value);
  REQUIRE(mox::is_protobuf_message_v<idl::pb::MockRequest>);
}

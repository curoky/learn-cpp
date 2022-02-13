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

#include "to_json.h"  // for to_json

#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

#include <initializer_list>
#include <string>
#include <type_traits>
#include <vector>

#include "library/protobuf/tutorial/idl/complex.pb.h"  // for complexRequest, MockRequest_EnumType, MockRequest_EnumType_ONE

using json = nlohmann::json;

TEST_CASE("[pb to json]") {
  idl::pb::MockRequest a;
  REQUIRE(mox::is_protobuf_message<idl::pb::MockRequest>::value == true);

  a.set_var_bool(true);
  json a_json = a;
  REQUIRE(a_json.dump() == "{\"varBool\":true}");
  json pa_json = &a;
  REQUIRE(pa_json.dump() == "{\"varBool\":true}");
}

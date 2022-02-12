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
#include <google/protobuf/util/json_util.h>

#include <string>

#include "library/protobuf/tutorial/idl/complex.pb.h"  // for complexRequest, MockRequest_EnumType, MockRequest_EnumType_ONE

TEST_CASE("pb serialize", "[Serialize]") {
  idl::pb::MockRequest req;
  req.set_var_bool(true);
  req.set_var_int32(1);
  req.set_var_float(1);
  req.set_var_str("var_str");
  req.set_var_bytes("var_bytes");

  req.set_var_enum(idl::pb::MockRequest_EnumType::MockRequest_EnumType_ONE);
  req.add_var_int32_lists(1);
  req.add_var_string_lists();

  std::string serialize_data;
  SECTION("debug string") {
    // "var_bool: true
    // var_int32: 1
    // var_float: 1
    // var_int32_list: 1
    // var_string_list: """
    serialize_data = req.DebugString();
  }

  SECTION("short debug string") {
    // "var_bool: true var_int32: 1 var_float: 1 var_int32_list: 1 var_string_list: """
    serialize_data = req.ShortDebugString();
  }

  SECTION("utf8 debug string") {
    // "var_bool: true
    // var_int32: 1
    // var_float: 1
    // var_int32_list: 1
    // var_string_list: """
    serialize_data = req.Utf8DebugString();
  }

  SECTION("serialize string") {
    REQUIRE(req.SerializeToString(&serialize_data) == true);
    idl::pb::MockRequest req_copy;
    REQUIRE(req_copy.ParseFromString(serialize_data) == true);
  }

  SECTION("json string") {
    std::string output;
    auto status = google::protobuf::util::MessageToJsonString(req, &output);
    REQUIRE(status.ok());
  }
  std::cout << serialize_data << std::endl;
  CAPTURE(serialize_data);
}

TEST_CASE("pb serialize json", "[Serialize]") {
  //
}

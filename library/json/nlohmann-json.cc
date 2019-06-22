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
#include <nlohmann/json.hpp>

#include <initializer_list>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "json_data.h"

// for convenience
using json = nlohmann::json;

TEST_CASE("[Nlohmann-json]: parse json") {
  auto params = json::parse(json_data);
  REQUIRE(params.is_object());

  auto& key_int = params["key_int"];
  REQUIRE(key_int.is_number_integer());
  REQUIRE(key_int.is_number_unsigned());
  REQUIRE_FALSE(key_int.is_number_float());
  REQUIRE(key_int == 1);

  auto& key_str = params["key_str"];
  REQUIRE(key_str.is_string());
  REQUIRE_FALSE(key_str.is_number_integer());
  REQUIRE(key_str == "value2");

  auto& key_bool = params["key_bool"];
  REQUIRE(key_bool.is_boolean());
  REQUIRE_FALSE(key_bool.is_number());
  REQUIRE_FALSE(key_bool.is_number_float());
  REQUIRE(key_bool == false);

  auto& key_null = params["key_null"];
  REQUIRE(key_null.is_null());

  auto& key_double = params["key_double"];
  REQUIRE(key_double.is_number_float());
  REQUIRE_FALSE(key_double.is_number_integer());
  REQUIRE(key_double == 1.1e100);

  auto& key_double2 = params["key_double2"];
  REQUIRE(key_double2 == -0.123);

  auto& key_list_eq = params["key_list_eq"];
  REQUIRE(key_list_eq.is_array());
  REQUIRE(key_list_eq == std::vector<int>{1, 2, 3});
  REQUIRE(key_list_eq.at(2) == 3);

  auto& key_list_mix = params["key_list_mix"];
  REQUIRE(key_list_mix.is_array());
  REQUIRE(key_list_mix.at(0) == "1");
  REQUIRE(key_list_mix.at(1) == 2);
  {
    auto& key_map_eq = params["key_map_eq"];
    REQUIRE(key_map_eq.is_object());
    REQUIRE(key_map_eq.count("kk1") == 1);
    REQUIRE(key_map_eq["kk2"] == "2");

    std::unordered_map<std::string, std::string> string_map =
        key_map_eq.get<std::unordered_map<std::string, std::string>>();
    REQUIRE(string_map.size() == 2);
  }
  {
    auto& key_map_mix = params["key_map_mix"];
    REQUIRE(key_map_mix.is_object());
    REQUIRE(key_map_mix.at("kk1") == 1);
    REQUIRE(key_map_mix.at("kk3").at(2) == 3);

    bool have_except = false;
    try {
      std::unordered_map<std::string, std::string> string_map =
          key_map_mix.get<std::unordered_map<std::string, std::string>>();
      REQUIRE(string_map.size() == 3);
    } catch (json::type_error& e) {
      have_except = true;
      REQUIRE(e.what() ==
              std::string("[json.exception.type_error.302] type must be string, but is number"));
    }
    REQUIRE(have_except == true);
  }
}

// custom struct
namespace nj {
struct Foo {
  std::vector<int> v1;
  std::map<std::string, std::vector<int>> v2;
};
void to_json(nlohmann::json& j, const Foo& foo) {
  j["v1"] = foo.v1;
  j["v2"] = foo.v2;
}
}  // namespace nj

TEST_CASE("basic usage", "[json]") {
  json j;
  nj::Foo foo;
  foo.v1 = {1, 2, 3};
  foo.v2 = {{"123", {1, 2, 3}}};
  j["data"] = foo;
  /*
  {
    "data": {
      "v1": [1, 2, 3],
      "v2": { "123": [1, 2, 3] }
    }
  }
   */
  // REQUIRE(j.dump(2) == "23");
}

// https://github.com/nlohmann/json/issues/1113
TEST_CASE("test any", "[json]") {
  // std::any a = "123";
  // REQUIRE(json(a).dump() == "123");
}

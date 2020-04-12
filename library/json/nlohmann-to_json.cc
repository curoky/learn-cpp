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

// https://github.com/nlohmann/json/issues/975

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

#include <memory>
#include <string>

namespace nlohmann {
template <typename T>
struct adl_serializer<std::unique_ptr<T>> {
  static void to_json(json& j, const std::unique_ptr<T>& opt) {
    if (opt.get()) {
      j = *opt;
    } else {
      j = nullptr;
    }
  }
};

template <typename T>
struct adl_serializer<std::shared_ptr<T>> {
  static void to_json(json& j, const std::shared_ptr<T>& opt) {
    if (opt.get()) {
      j = *opt;
    } else {
      j = nullptr;
    }
  }
};
}  // namespace nlohmann

TEMPLATE_TEST_CASE("[ptr to json]", "[ptr][template]", std::shared_ptr<int>, std::unique_ptr<int>) {
  using json = nlohmann::json;
  TestType a(new int(1));
  json a_json = a;
  REQUIRE(a_json.dump() == "1");
}

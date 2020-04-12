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

#pragma once
#include <assert.h>
#include <google/protobuf/util/json_util.h>
#include <nlohmann/json.hpp>

#include <string>
#include <type_traits>
#include <utility>

#include "traits.h"

namespace mox {
nlohmann::json protoToJson(const google::protobuf::Message& message);
}

namespace nlohmann {
/*
template <typename BasicJsonType, typename T,
          std::enable_if_t<mox::is_protobuf_message<T>::value, int> = 0>
void to_json_base(BasicJsonType& j, const T& b) {
  std::string output;
  google::protobuf::util::Status status = google::protobuf::util::MessageToJsonString(b, &output);
  assert(status.ok() == true);
  j = std::move(BasicJsonType::parse(output));
}
*/

template <typename BasicJsonType, typename T,
          std::enable_if_t<mox::is_protobuf_message<T>::value, int> = 0>
void to_json(BasicJsonType& j, const T& b) {
  // to_json_base(j, b);
  j = mox::protoToJson(b);
}

template <typename BasicJsonType, typename T,
          std::enable_if_t<mox::is_protobuf_message<T>::value, int> = 0>
void to_json(BasicJsonType& j, const T* b) {
  // to_json_base(j, *b);
  j = mox::protoToJson(*b);
}
}  // namespace nlohmann

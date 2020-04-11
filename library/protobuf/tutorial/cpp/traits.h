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
#include <google/protobuf/message.h>

#include <string>
#include <type_traits>
#include <utility>

namespace mox {
namespace details {
template <typename... Ts>
struct Ignore {};
}  // namespace details

namespace v1 {
template <typename ProtoType>
struct is_protobuf_message : public std::is_base_of<google::protobuf::Message, ProtoType> {};

template <typename ProtoType>
inline constexpr bool is_protobuf_message_v = is_protobuf_message<ProtoType>::value;
}  // namespace v1

inline namespace v2 {
template <class Obj, class = void>
struct is_protobuf_message : std::false_type {};

template <class Obj>
struct is_protobuf_message<
    Obj, typename std::conditional<false,
                                   details::Ignore<decltype(std::declval<Obj>().SerializeToString(
                                       (std::string*)nullptr))>,
                                   void>::type> : std::true_type {};
}  // namespace v2

template <class Obj>
inline constexpr bool is_protobuf_message_v = v2::is_protobuf_message<Obj>::value;
}  // namespace mox

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
#include <boost/algorithm/string/replace.hpp>

#include <string>
#include <string_view>

namespace detail {

static constexpr size_t PREFIX_LENGTH =
    sizeof("constexpr const char* detail::type_name_impl() [with T = ") - 1;
static constexpr size_t SUFFIX_LENGTH = sizeof("]") - 1;

template <typename T>
constexpr const char* type_name_impl() {
  return __PRETTY_FUNCTION__;
}

constexpr std::string_view string_type_name() {
  std::string_view string_type(type_name_impl<std::string>());
  string_type.remove_prefix(PREFIX_LENGTH);
  string_type.remove_suffix(SUFFIX_LENGTH);
  return string_type;
}

template <typename T>
std::string get_type_name() {
  std::string type = type_name_impl<T>();
  type = type.substr(PREFIX_LENGTH, type.size() - PREFIX_LENGTH - SUFFIX_LENGTH);
  boost::replace_all(type, string_type_name(), "std::string");
  boost::replace_all(type, " >", ">");
  return type;
}

}  // namespace detail

namespace mox {
namespace type {

template <typename T>
std::string type_name() {
  if (std::is_volatile<T>::value) {
    if (std::is_pointer<T>::value) {
      return type_name<typename std::remove_volatile<T>::type>() + " volatile";
    } else {
      return "volatile " + type_name<typename std::remove_volatile<T>::type>();
    }
  }
  if (std::is_const<T>::value) {
    if (std::is_pointer<T>::value) {
      return type_name<typename std::remove_const<T>::type>() + " const";
    } else {
      return "const " + type_name<typename std::remove_const<T>::type>();
    }
  }
  if (std::is_pointer<T>::value) {
    return type_name<typename std::remove_pointer<T>::type>() + "*";
  }
  if (std::is_lvalue_reference<T>::value) {
    return type_name<typename std::remove_reference<T>::type>() + "&";
  }
  if (std::is_rvalue_reference<T>::value) {
    return type_name<typename std::remove_reference<T>::type>() + "&&";
  }

  return detail::get_type_name<T>();
}

}  // namespace type
}  // namespace mox

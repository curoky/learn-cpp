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

#include <memory>
#include <type_traits>

namespace mox {
template <typename T>
struct is_shared_ptr : std::false_type {};

template <typename T>
struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

template <typename T>
typename std::enable_if<is_shared_ptr<T>::value, bool>::type is_ptr(T t) {
  return true;
}

template <typename T>
typename std::enable_if<!is_shared_ptr<T>::value, bool>::type is_ptr(T t) {
  return false;
}
}  // namespace mox

TEST_CASE("ptr", "[traits]") {
  REQUIRE(mox::is_shared_ptr<int>::value == false);
  REQUIRE(mox::is_shared_ptr<std::shared_ptr<int>>::value == true);

  REQUIRE(mox::is_ptr(1) == false);
  REQUIRE(mox::is_ptr(std::make_shared<int>(1)) == true);
}

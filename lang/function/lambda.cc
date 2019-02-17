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
#include <string>
#include <type_traits>
#include <utility>

TEST_CASE("MutableTest", "[Lambda]") {
  {
    auto str = std::make_shared<std::string>("123");
    // 捕获的拷贝对象，默认加了const，需要加mutable
    auto change = [str]() mutable { str.reset(); };
    change();
    REQUIRE(str.use_count() == 1);
  }
  {
    auto str = std::make_shared<std::string>("123");
    auto change = [&str]() { str.reset(); };
    change();
    REQUIRE(str.use_count() == 0);
  }
}
TEST_CASE("ConstRefTest", "[Lambda]") {
  // https://stackoverflow.com/questions/3772867/lambda-capture-as-const-reference/32440415#32440415

  std::string str = "123";
  auto get_const_ref = [&str = static_cast<const std::string&>(str)] {
    // FIXME: why is not const
    (void)str;
    REQUIRE(std::is_const<decltype(str)>::value == false);
  };
  get_const_ref();
  auto get_const_ref2 = [&str = std::as_const(str)] {
    REQUIRE(std::is_const<decltype(str)>::value == false);
  };
  get_const_ref2();
}

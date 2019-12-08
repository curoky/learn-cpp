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
#include <stdc-predef.h>

#include <string>
#include <string_view>

using namespace std::literals;  // NOLINT

TEST_CASE("simple test", "[PredefinedMacros]") {
  // REQUIRE(__cplusplus == 201709L);
  REQUIRE(__STDC_HOSTED__ == 1);
  // standard/language/preprocessor/predefined_macros.cc
  REQUIRE_THAT(__FILE__, Catch::Matchers::EndsWith("predefined_macros.cc"));

  // REQUIRE(__LINE__ == 20);
  // REQUIRE(__DATE__ == "Dec  2 2019");
  // REQUIRE(__TIME__ == "21:57:42");
  REQUIRE(__STDCPP_DEFAULT_NEW_ALIGNMENT__ == 16);
  REQUIRE(__STDC__ == 1);
  // __STDC_VERSION__ was not declared in this scope
  // REQUIRE(__STDC_VERSION__ == "");
  REQUIRE(__STDC_ISO_10646__ == 201706L);
  // follow lines were not declared in this scope
  // REQUIRE(__STDC_MB_MIGHT_NEQ_WC__ == "");
  // REQUIRE(__STDCPP_STRICT_POINTER_SAFETY__ == "");
  // REQUIRE(__STDCPP_THREADS__ == "");
  REQUIRE(__FUNCTION__ == "CATCH2_INTERNAL_TEST_0"s);
  REQUIRE(__PRETTY_FUNCTION__ == "void CATCH2_INTERNAL_TEST_0()"s);
  REQUIRE(__func__ == "CATCH2_INTERNAL_TEST_0"s);
}

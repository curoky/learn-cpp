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

#include <chrono>
#include <complex>
#include <string>

// using namespace std::literals;

TEST_CASE("ChronoTest", "[UserDefinedLiterals]") {
  using namespace std::chrono_literals;  // NOLINT
  REQUIRE(std::chrono::duration_cast<std::chrono::milliseconds>(1s).count() == 1000);
  REQUIRE(std::chrono::duration_cast<std::chrono::seconds>(1min1).count() == 60);
  REQUIRE(std::chrono::duration_cast<std::chrono::minutes>(1h).count() == 60);
  // REQUIRE(std::chrono::duration_cast<std::chrono::hours>(1d).count() == 24);  // start c++20
  // REQUIRE(std::chrono::duration_cast<std::chrono::days>(1y).count() == 365);  // start c++20
}

TEST_CASE("ComplexTest", "[UserDefinedLiterals]") {
  using namespace std::complex_literals;  // NOLINT
  REQUIRE(std::complex<double>(0, 100) == 100i);
  REQUIRE(std::complex<float>(0, 100) == 100if);
  REQUIRE(std::complex<long double>(0, 100) == 100il);
}

TEST_CASE("StringLiteralsTest", "[UserDefinedLiterals]") {
  using namespace std::string_literals;  // NOLINT
  std::string s1 = "abc\0\0def";
  std::string s2 = "abc\0\0def"s;
  CAPTURE(s1);
  CAPTURE(s2);
  REQUIRE(s1.size() == 3);
  REQUIRE(s2.size() == 8);
}

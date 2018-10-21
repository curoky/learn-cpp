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

#include <boost/lexical_cast.hpp>
#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>

TEST_CASE("[Lexical-cast]: BaseTest") {
  // string <=> int
  REQUIRE(boost::lexical_cast<int>("-123") == -123);
  REQUIRE(boost::lexical_cast<std::string>(-123) == "-123");

  // string <=> double
  REQUIRE(boost::lexical_cast<double>("-123.12") == -123.12);
  REQUIRE(boost::lexical_cast<std::string>(-123.12) == "-123.12");
}

TEST_CASE("[Lexical-cast]: bad cast") {
  REQUIRE_THROWS_AS(boost::lexical_cast<int>("123;"), boost::bad_lexical_cast);
  REQUIRE_THROWS_AS(boost::lexical_cast<int>("123.13.123"), boost::bad_lexical_cast);
  REQUIRE_THROWS_AS(boost::lexical_cast<int>("123i"), boost::bad_lexical_cast);
  REQUIRE_THROWS_AS(boost::lexical_cast<int>("abc"), boost::bad_lexical_cast);
}

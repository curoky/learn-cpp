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
#include <folly/String.h>

TEST_CASE("split", "[folly-string]") {
  SECTION("to vector") {
    std::vector<folly::StringPiece> v;
    folly::split("-", "1-2-3", v);
  }

  SECTION("to list") {
    folly::StringPiece a, b, c;
    SECTION("normal") {
      folly::split("-", "1-2-3", a, b, c);
      CHECK(a == "1");
      CHECK(b == "2");
      CHECK(c == "3");
    }
    SECTION("bad v1") {
      folly::split("-", "2-2", a, b, c);
      CHECK(a == "");
      CHECK(b == "");
      CHECK(c == "");
    }
    SECTION("bad v2") {
      folly::split("-", "", a, b, c);
      CHECK(a == "");
      CHECK(b == "");
      CHECK(c == "");
    }
    SECTION("bad v3") {
      folly::split("-", "2", a, b, c);
      CHECK(a == "");
      CHECK(b == "");
      CHECK(c == "");
    }
    SECTION("bad v4") {
      folly::split("-", "2--2", a, b, c);
      CHECK(a == "2");
      CHECK(b == "");
      CHECK(c == "2");
    }
    SECTION("bad v5") {
      folly::split("-", "--2", a, b, c);
      CHECK(a == "");
      CHECK(b == "");
      CHECK(c == "2");
    }
    SECTION("bad v6") {
      folly::split("-", "2--", a, b, c);
      CHECK(a == "2");
      CHECK(b == "");
      CHECK(c == "");
    }
    SECTION("bad v7") {
      folly::split("-", "2--2-3", a, b, c);
      CHECK(a == "");
      CHECK(b == "");
      CHECK(c == "");
    }
  }
}

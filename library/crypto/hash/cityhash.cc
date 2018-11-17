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
#include <city.h>

#include <cstring>
#include <utility>

TEST_CASE("BaseTest", "[Cityhash]") {
  char message[] = "this is a message";

  uint64 result = CityHash64(message, strlen(message));
  REQUIRE(result == 2326233506162522101UL);

  uint64 result_seed_0 = CityHash64WithSeed(message, strlen(message), 0);
  REQUIRE(result_seed_0 == 13618943559033900693UL);

  uint64 result_seed_x = CityHash64WithSeed(message, strlen(message), 11);
  REQUIRE(result_seed_x == 15318277747039075468UL);
  uint64 result_seed_00 = CityHash64WithSeeds(message, strlen(message), 0, 0);
  REQUIRE(result_seed_00 == 10245443173365667867UL);
  uint64 result_seed_xx = CityHash64WithSeeds(message, strlen(message), 11, 11);
  REQUIRE(result_seed_xx == 84619909344789617UL);
  uint128 result_128 = CityHash128(message, strlen(message));
  REQUIRE(result_128 == uint128(14542769689296376665UL, 15428484447020256649UL));
  uint128 result_128_seed_0 = CityHash128WithSeed(message, strlen(message), uint128{0, 0});
  REQUIRE(result_128_seed_0 == uint128(4938914511040200291UL, 9334466718237466855UL));
  uint128 result_128_seed_x = CityHash128WithSeed(message, strlen(message), uint128{11, 11});
  REQUIRE(result_128_seed_x == uint128(6537074921161846671UL, 5540889777009156352UL));
  uint32 result_32 = CityHash32(message, strlen(message));
  REQUIRE(result_32 == 2490823589);
  uint64 result_128_to_64 = Hash128to64(result_128);
  REQUIRE(result_128_to_64 == 3791066174313333588);
}

TEST_CASE("empty string", "[Cityhash]") {
  char message[] = "";
  uint64 result = CityHash64(message, strlen(message));
  REQUIRE(result == 11160318154034397263);
}

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
#include <boost/hana.hpp>
#include <catch2/catch_test_macros.hpp>

#include <string>

namespace hana = boost::hana;

namespace {
struct Fish {
  std::string name;
};
struct Cat {
  std::string name;
};
struct Dog {
  std::string name;
};
}  // namespace

TEST_CASE("tuple", "[haha]") {
  using namespace hana::literals;

  auto animals = hana::make_tuple(Fish{"Nemo"}, Cat{"Garfield"}, Dog{"Snoopy"});

  Cat grafield = animals[1_c];
  REQUIRE(grafield.name == "Garfield");
  // Perform high level algorithms on tuples (this is like std::transform)
  auto names = hana::transform(animals, [](auto a) { return a.name; });

  // REQUIRE(hana::reverse(names) == hana::make_tuple("Snoopy", "Garfield", "Nemo"));

  auto animal_types = hana::make_tuple(hana::type_c<Fish*>, hana::type_c<Cat&>, hana::type_c<Dog>);
  auto no_pointers =
      hana::remove_if(animal_types, [](auto a) { return hana::traits::is_pointer(a); });
  static_assert(no_pointers == hana::make_tuple(hana::type_c<Cat&>, hana::type_c<Dog>), "");
}

TEST_CASE("has mem", "[hana]") {
  auto has_mem_var_name = hana::is_valid([](auto&& x) -> decltype((void)x.name) {});
  auto has_mem_func_name = hana::is_valid([](auto&& x) -> decltype(x.name()) {});

  {
    struct {
      std::string name;
    } people;

    static_assert(has_mem_var_name(people), "");
    static_assert(!has_mem_var_name(1), "");
  }

  {
    struct {
      std::string name();
    } people;

    static_assert(has_mem_func_name(people), "");
    static_assert(!has_mem_func_name(1), "");
  }
}

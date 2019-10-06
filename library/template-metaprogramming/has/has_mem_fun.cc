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

#include <string>
#include <type_traits>
#include <utility>

// Ref:
// https://stackoverflow.com/questions/257288/templated-check-for-the-existence-of-a-class-member-function
// https://stackoverflow.com/questions/1966362/sfinae-to-check-for-inherited-member-functions

class Foo {
 public:
  std::string to_string(int n) { return std::to_string(n); }
};

// method one
#include <experimental/type_traits>

namespace one {
template <typename T>
using to_string_t = decltype(std::declval<T &>().to_string(int()));

template <typename T>
constexpr bool has_to_string_v = std::experimental::is_detected_v<to_string_t, T>;
}  // namespace one

// method two
namespace two {
// TODO(curoky): make it good with clang
// template <typename T>
// concept has_to_string = requires(T &t) {
//   { t.to_string(int()) } -> std::same_as<std::string>;
// };  // NOLINT
// template <typename T>
// constexpr bool has_to_string_v = has_to_string<T>;
}  // namespace two

// method three
#include <boost/hana.hpp>

namespace three {
static auto has_to_string_v =
    boost::hana::is_valid([](auto &&obj) -> decltype(obj.to_string(int())) {});
}  // namespace three

// method four
// https://www.boost.org/doc/libs/1_76_0/libs/tti/doc/html/the_type_traits_introspection_library/tti_detail_has_static_member_function.html
#include <boost/tti/has_member_function.hpp>

namespace four {
BOOST_TTI_HAS_MEMBER_FUNCTION(to_string);

template <typename T>
constexpr bool has_to_string_v =
    has_member_function_to_string<T, std::string, boost::mpl::vector<int>>::value;
}  // namespace four

// method five
namespace five {
namespace detail {
template <typename... Ts>
struct helper {};
}  // namespace detail

template <typename Container, class = void>
struct has_to_string : std::false_type {};

template <typename T>
struct has_to_string<
    T, typename std::conditional<
           false, detail::helper<decltype(std::declval<T>().to_string(int()))>, void>::type>
    : std::true_type {};

template <typename T>
constexpr bool has_to_string_v = has_to_string<T>::value;
}  // namespace five

TEST_CASE("has member", "[sfinae]") {
  REQUIRE(one::has_to_string_v<int> == false);
  REQUIRE(one::has_to_string_v<Foo> == true);
  // REQUIRE(two::has_to_string_v<int> == false);
  // REQUIRE(two::has_to_string_v<Foo> == true);
  // REQUIRE(three::has_to_string_v(int)) == true);
  // REQUIRE(three::has_to_string_v(Foo()) == true);
  REQUIRE(four::has_to_string_v<int> == false);
  REQUIRE(four::has_to_string_v<Foo> == true);
  REQUIRE(five::has_to_string_v<int> == false);
  REQUIRE(five::has_to_string_v<Foo> == true);
}

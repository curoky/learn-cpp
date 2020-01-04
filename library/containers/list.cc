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

#include <boost/intrusive/list.hpp>
#include <catch2/catch_test_macros.hpp>

#include <functional>
#include <list>
#include <utility>

TEST_CASE("erase", "[List]") {
  std::list<int> nubs = {1, 2, 3, 4};
  auto iter = nubs.begin();
  iter = nubs.erase(iter);
  REQUIRE(*iter == 2);
}

/* https://www.boost.org/doc/libs/1_78_0/doc/html/intrusive/usage.html
 * 需要在特定场景下配合特定的使用技巧。因为 intrusive list
 * 本身是不会维护节点的生命周期的，所以直接插入栈上分配的对象，完全没有意义，
 * 如果额外在用另外一个容器维护节点的生命周期，就略显脑残了。
 */

// Case1: Call Once Function list
struct Func : public boost::intrusive::list_base_hook<
                  boost::intrusive::link_mode<boost::intrusive::auto_unlink>> {
  using List = boost::intrusive::list<Func, boost::intrusive::constant_time_size<false>>;

  explicit Func(std::function<void()> func) : func(std::move(func)) {}

  void call() {
    std::invoke(func);
    delete this;
  }

  std::function<void()> func;
};

TEST_CASE("intrusive list", "[List]") {
  Func::List list;
  REQUIRE(list.size() == 0);
  size_t count = 0;
  {
    // insert func
    auto* func = new Func([&count]() { count++; });
    list.push_back(*func);
  }
  REQUIRE(list.size() == 1);
  list.front().call();
  REQUIRE(list.size() == 0);
  REQUIRE(count == 1);
}

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

#if __has_include(<Laugh/Actor.inl>)
#include <Laugh/Actor.hpp>
#include <catch2/catch_test_macros.hpp>
// #include <launch.hpp>

#include <Laugh/Actor.inl>
#include <iostream>
#include <memory>
#include <utility>

struct Counter : laugh::Actor {
  int i = 0;
  int Increment() { return ++i; }
};

struct User : laugh::Actor {
  void PlayAround() {
    auto counter = Self().Make<Counter>();
    for (int i = 0; i < 50; ++i) {
      // Fifty concurrent messages!
      counter.Bang(&Counter::Increment);
    }

    // How far has the counter come so far?
    Ask(counter, &Counter::Increment)->AndThen([](laugh::ActorRef<Actor> self, int there) {
      std::cout << "So far, he's at " << there << std::endl;
    });
  }
};

TEST_CASE("basic usage", "[laugh]") {
  // Let a set of three OS threads do the message processing.
  laugh::ActorContext acts{3};
  // Just create an actor like this. Even with arguments,
  // if you want to. And if the constructor allows it.
  auto user = acts.Make<User>();

  // Done and done.
  user.Bang(&User::PlayAround);

  std::cout << "Meanwhile, main thread sips coffee." << std::endl;
}

#endif

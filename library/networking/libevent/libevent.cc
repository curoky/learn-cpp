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

// http://www.wangafu.net/~nickm/libevent-book/
// https://www.gitbook.com/book/aceld/libevent

#include <catch2/catch_test_macros.hpp>
#include <event2/event.h>
#include <stdint.h>

#include <algorithm>
#include <set>
#include <string>

using namespace std::string_literals;  // NOLINT

TEST_CASE("version", "[Libevent]") {
  // REQUIRE(event_get_version() == "2.1.11-stable"s);
  // REQUIRE(event_get_version_number() == 33622784);
}

TEST_CASE("support method", "[Libevent]") {
  const char** method_list = event_get_supported_methods();
  std::set<std::string> methods;
  for (int i = 0; method_list[i] != nullptr; ++i) {
    methods.emplace(method_list[i]);
  }
  REQUIRE(methods == std::set<std::string>{"select", "poll", "epoll"});
}

TEST_CASE("create event base", "[Libevent]") {
  event_base* base = nullptr;
  SECTION("create default") {
    base = event_base_new();
    REQUIRE(event_base_get_method(base) == "epoll"s);
  }
  SECTION("create with config") {
    event_config* config = event_config_new();
    event_config_avoid_method(config, "epoll");
    base = event_base_new_with_config(config);
    event_config_free(config);

    REQUIRE(event_base_get_method(base) == "poll"s);
  }

  // REQUIRE(event_base_get_features(base) == 11);

  event_base_free(base);
}

TEST_CASE("loop", "[Libevent]") {
  event_base* base = event_base_new();

  // @return
  // 0 if successful,
  // -1 if an error occurred,
  // 1 if we exited because no events were pending or active.
  SECTION("loop once") { REQUIRE(event_base_loop(base, EVLOOP_ONCE) == 1); }
  SECTION("loop nonblock") { REQUIRE(event_base_loop(base, EVLOOP_NONBLOCK) == 1); }
  SECTION("loop forever") { REQUIRE(event_base_dispatch(base) == 1); }
  REQUIRE(event_base_got_exit(base) == 0);
  event_base_free(base);
}

TEST_CASE("loop break", "[Libevent]") {
  // int event_base_loopexit(struct event_base *base,
  //                     const struct timeval *tv);
  // int event_base_loopbreak(struct event_base *base);

  auto cb = [](int sock, int16_t what, void* arg) {
    (void)sock;
    (void)what;
    event_base* base = static_cast<event_base*>(arg);
    event_base_loopbreak(base);
  };

  event_base* base = event_base_new();

  int watchdog_fd = 0;
  event* watchdog_event = event_new(base, watchdog_fd, EV_READ, cb, base);
  event_add(watchdog_event, nullptr);
  // FIXME: can't break
  // event_base_dispatch(base);

  event_free(watchdog_event);

  event_base_free(base);
}

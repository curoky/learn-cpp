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
#include <httplib.h>

#include <memory>
#include <regex>

TEST_CASE("basic usage", "[Httplib]") {
  // using namespace httplib;

  httplib::Server svr;

  svr.Get("/hi", [](const httplib::Request& req, httplib::Response& res) {
    res.set_content("Hello World!", "text/plain");
  });

  svr.Get(R"(/numbers/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
  });

  svr.Get("/body-header-param", [](const httplib::Request& req, httplib::Response& res) {
    if (req.has_header("Content-Length")) {
      auto val = req.get_header_value("Content-Length");
    }
    if (req.has_param("key")) {
      auto val = req.get_param_value("key");
    }
    res.set_content(req.body, "text/plain");
  });

  svr.Get("/stop", [&](const httplib::Request& req, httplib::Response& res) { svr.stop(); });

  // svr.listen("localhost", 1234);
}

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

// https://gflags.github.io/gflags/

#include <fmt/printf.h>
#include <gflags/gflags.h>
#include <stdint.h>

#include <iostream>
#include <string>

DEFINE_bool(gbool, false, "");
DEFINE_int32(gint32, 1, "");
DEFINE_uint32(guint32, 1, "");
DEFINE_int64(gint64, 1, "");
DEFINE_uint64(guint64, 1, "");
DEFINE_string(gstring, "1", "");
DEFINE_double(gdouble, 1, "");

static bool ValidatePort(const char* flagname, int32_t value) {
  if (value > 0 && value < 32768) {  // value is ok
    return true;
  }
  fmt::print("Invalid value for --{}: {}\n", flagname, value);
  return false;
}

DEFINE_int32(port, 233333, "What port to listen on");
DEFINE_validator(port, &ValidatePort);

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  fmt::print(
      "--gbool = {}\n"
      "--gint32 = {}\n"
      "--guint32 = {}\n"
      "--gint64 = {}\n"
      "--guint64 = {}\n"
      "--gstring = {}\n"
      "--gdouble = {}\n"
      "--port = {}\n",
      FLAGS_gbool, FLAGS_gint32, FLAGS_guint32, FLAGS_gint64, FLAGS_guint64, FLAGS_gstring,
      FLAGS_gdouble, FLAGS_port);
  return 0;
}

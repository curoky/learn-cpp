# Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
#
# This file is part of learn-cpp.
# See https://github.com/curoky/learn-cpp for further info.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

load("@rules_cc//cc:defs.bzl", "cc_binary")

common_copts = [
    "-g",
    "-O0",
    "-fno-omit-frame-pointer",
]

cc_binary(
    name = "case0",
    srcs = [
        "case0.cc",
    ],
    deps = [
        "@com_github_gflags_gflags//:gflags",
    ],
)

cc_binary(
    name = "asm",
    srcs = [
        "asm.cc",
    ],
    copts = common_copts,
    deps = [
        "@com_github_gflags_gflags//:gflags",
    ],
)

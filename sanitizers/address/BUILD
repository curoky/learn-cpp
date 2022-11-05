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
load("//build/bazel:copts.bzl", "TEST_CPP_COPTS", "TEST_LINKOPTS")

cc_binary(
    name = "use-after-free",
    srcs = ["use-after-free.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
)

cc_binary(
    name = "heap-buffer-overflow",
    srcs = ["heap-buffer-overflow.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
)

cc_binary(
    name = "global-buffer-overflow",
    srcs = ["global-buffer-overflow.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
)

cc_binary(
    name = "stack-buffer-overflow",
    srcs = ["stack-buffer-overflow.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
)

cc_binary(
    name = "use-after-return",
    srcs = ["use-after-return.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
)

cc_binary(
    name = "use-after-scope",
    srcs = ["use-after-scope.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
)

cc_binary(
    name = "memory-leaks",
    srcs = ["memory-leaks.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
)

cc_binary(
    name = "process_overflow",
    srcs = ["process_overflow.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "@com_github_gflags_gflags//:gflags",
    ],
)

cc_binary(
    name = "thread_overflow",
    srcs = ["thread_overflow.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "@com_github_gflags_gflags//:gflags",
    ],
)

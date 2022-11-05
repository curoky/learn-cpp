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
    name = "stack_strace",
    srcs = ["stack_strace.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "@boost//:stacktrace",
        "@com_github_facebook_folly//:folly",
    ],
)

cc_binary(
    name = "crash",
    srcs = ["crash.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "@com_github_facebook_folly//:folly",
    ],
)

cc_binary(
    name = "small_sig_alt_stack_crash",
    srcs = ["small_sig_alt_stack_crash.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "@com_github_facebook_folly//:folly",
    ],
)

cc_binary(
    name = "execinfo",
    srcs = ["execinfo.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "@com_github_facebook_folly//:folly",
    ],
)

cc_binary(
    name = "folly_backtrace",
    srcs = ["folly_backtrace.cc"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "@com_github_facebook_folly//:folly",
    ],
)

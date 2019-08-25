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

'''
load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//bazel:copts.bzl", "TEST_LINKOPTS")

cc_binary(
    name = "matcher",
    srcs = ["matcher.cc"],
    copts = [
        "-g",
        "-fno-omit-frame-pointer",
        "-std=c++2a",
    ],
    linkopts = TEST_LINKOPTS,
    deps = [
        "@llvm//:clang",
    ],
)

cc_binary(
    name = "cast-matcher",
    srcs = ["cast-matcher.cc"],
    copts = [
        # "-g",
        # "-fno-omit-frame-pointer",
        "-std=c++2a",
    ],
    # linkopts = TEST_LINKOPTS,
    deps = [
        "@llvm//:clang",
        # "@llvm//:clangTooling",
        # "@llvm//:clangBasic",
        # "@llvm//:clangASTMatchers",
    ],
)

cc_binary(
    name = "class-matcher",
    srcs = ["class-matcher.cc"],
    copts = [
        # "-g",
        # "-fno-omit-frame-pointer",
        "-std=c++2a",
    ],
    # linkopts = TEST_LINKOPTS,
    deps = [
        "@llvm//:clang",
        "@com_github_nlohmann_json//:json",

        # "@llvm//:clangTooling",
        # "@llvm//:clangBasic",
        # "@llvm//:clangASTMatchers",
    ],
)
'''

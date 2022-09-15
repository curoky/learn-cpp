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
load("@rules_cc//cc:defs.bzl", "cc_import", "cc_library")

cc_import(
    name = "ssl_precompiled",
    static_library = "lib/libssl.a",
)

cc_import(
    name = "crypto_precompiled",
    static_library = "lib/libcrypto.a",
)

cc_library(
    name = "openssl",
    hdrs = glob(["include/**"]),
    includes = ["include"],
    linkopts = [
        "-ldl",
        "-lpthread",
        "-lrt",
    ],
    visibility = ["//visibility:public"],
    deps = [
        # do not sort
        ":ssl_precompiled",
        ":crypto_precompiled",
    ],
)

cc_library(
    name = "ssl",
    hdrs = glob(["include/**"]),
    includes = ["include"],
    linkopts = [
        "-ldl",
        "-lpthread",
        "-lrt",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":ssl_precompiled",
    ],
)

cc_library(
    name = "crypto",
    hdrs = glob(["include/**"]),
    includes = ["include"],
    linkopts = [
        "-ldl",
        "-lpthread",
        "-lrt",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":crypto_precompiled",
    ],
)

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

load("@com_curoky_tame//bazel:copts.bzl", "TEST_CPP_COPTS", "TEST_LINKOPTS")

cc_test(
    name = "main",
    testonly = False,
    srcs = glob([
        "**/*.h",
        "**/*.cc",
    ]),
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "@com_github_abseil_abseil_cpp//absl/container:inlined_vector",
        "@com_github_abseil_abseil_cpp//absl/debugging:demangle_internal",
        "@com_github_abseil_abseil_cpp//absl/strings:str_format",
        "@com_github_cginternals_cppfs//:cppfs",
        "@com_github_facebook_fatal//:fatal",
        "@com_github_facebook_folly//:folly",
        "@com_github_fmtlib_fmt//:fmt",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_libevent_libevent//:libevent",
        "@com_github_libuv_libuv//:libuv",
        "@com_github_renatogarcia_icecream_cpp//:icecream-cpp",
        "@com_github_ryanhaining_cppitertools//:cppitertools",
        "@com_github_yhirose_cpp_peglib//:cpp-peglib",
        "@jemalloc",
        "@libiberty",

        # logging
        "@com_github_google_glog//:glog",
        "@com_github_gabime_spdlog//:spdlog",

        # unittest
        "@com_github_catchorg_catch2//:catch2_main",
        "@com_github_google_googletest//:gtest",

        # concurrency
        "@com_github_tyckesak_laugh//:laugh",
        "@com_github_taskflow_taskflow//:taskflow",
        "@com_github_arximboldi_immer//:immer",
        "@com_github_oneapi_src_onetbb//:onetbb",
        "@com_github_cameron314_concurrentqueue//:concurrentqueue",
        "@com_github_greg7mdp_parallel_hashmap//:parallel-hashmap",

        # boost
        "@boost//:pfr",
        "@boost//:algorithm",
        "@boost//:assign",
        "@boost//:foreach",
        "@boost//:interprocess",
        "@boost//:lexical_cast",
        "@boost//:pool",
        "@boost//:range",
        "@boost//:serialization",
        "@boost//:tti",
        "@boost//:hana",
        "@boost//:coroutine2",

        # serialize
        "@com_github_felixguendling_cista//:cista",
        "@com_github_msgpack_msgpack_c//:msgpack-cxx",
        "@com_github_fraillt_bitsery//:bitsery",
        "@com_github_google_flatbuffers//:flatbuffers",

        # reflact
        "@com_github_neargye_nameof//:nameof",
        "@com_github_rttrorg_rttr//:rttr",
        "@com_github_ubpa_usrefl//:usrefl",
        "@com_github_veselink1_refl_cpp//:refl-cpp",
        "@com_github_aantron_better_enums//:better-enums",

        # crypto
        "@org_openssl//:crypto",
        "@org_openssl//:ssl",
        "@com_github_google_snappy//:snappy",
        "@com_github_google_cityhash//:cityhash",
        "@com_github_google_crc32c//:crc32c",
        "@com_github_facebook_zstd//:zstd",
        "@com_github_aappleby_smhasher//:murmurhash",

        # http
        # "@com_github_curl_curl//:curl",
        "@com_github_curl_curl//:libcurl",
        # "@com_github_mrtazz_restclient_cpp//:restclient",
        "@com_github_mrtazz_restclient_cpp//:restclient-cpp",
        "@com_github_libcpr_cpr//:cpr",
        "@com_github_yhirose_cpp_httplib//:cpp-httplib",

        # json
        "@com_github_nlohmann_json//:nlohmann_json",
        "@com_github_open_source_parsers_jsoncpp//:jsoncpp",
        "@com_github_tencent_rapidjson//:rapidjson",
        "@com_github_davegamble_cjson//:cjson",
    ],
)

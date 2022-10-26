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

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def dep_tools():
    http_archive(
        name = "hedron_compile_commands",
        urls = [
            "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "bazel-compile-commands-extractor-main",
    )
    http_archive(
        name = "com_github_nelhage_rules_boost",
        urls = [
            "https://github.com/nelhage/rules_boost/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "rules_boost-master",
        patch_cmds = [
            # "sed -i -e 's/openssl/org_openssl/g' boost/boost.bzl",
            # "sed -i -e 's/org_lzma_lzma/org_xz_xz/g' boost/boost.bzl",
            # "sed -i -e 's?org_lzma_lzma//:lzma?org_xz_xz//:xz?g' BUILD.boost",
            # "sed -i -e 's/org_lzma_lzma/org_xz_xz/g' BUILD.lzma"
        ],
    )
    http_archive(
        name = "rules_foreign_cc",
        urls = [
            "https://github.com/bazelbuild/rules_foreign_cc/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "rules_foreign_cc-main",
    )
    http_archive(
        name = "rules_pkg",
        urls = [
            "https://github.com/bazelbuild/rules_pkg/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "rules_pkg-main",
    )

    http_archive(
        name = "rules_proto",
        urls = [
            "https://github.com/bazelbuild/rules_proto/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "rules_proto-master",
    )

def dep_libs():
    http_archive(
        name = "com_github_abseil_abseil_cpp",
        urls = ["https://github.com/abseil/abseil-cpp/archive/refs/tags/20220623.1.tar.gz"],
        strip_prefix = "abseil-cpp-20220623.1",
    )

    http_archive(
        name = "com_github_google_double_conversion",
        urls = ["https://github.com/google/double-conversion/archive/refs/tags/v3.2.1.tar.gz"],
        patch_cmds = ["sed -i -e 's/linkopts/includes = [\".\"],linkopts/g' BUILD"],
        strip_prefix = "double-conversion-3.2.1",
    )

    http_archive(
        name = "baiduhook",
        urls = [
            "https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/baiduhook/bhook-1.0.0.tar.gz",
        ],
        strip_prefix = "bhook-1.0.0",
        patch_args = ["-p1"],
        patches = [
            "@com_curoky_tame//:recipes/b/baiduhook/default/patch/0002-fix-bfd-disassembler.patch",
        ],
    )

    http_archive(
        name = "com_github_google_benchmark",
        urls = [
            "https://github.com/google/benchmark/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "benchmark-main",
    )

    http_archive(
        name = "com_github_aantron_better_enums",
        urls = [
            "https://github.com/aantron/better-enums/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "better-enums-master",
        build_file =
            "@com_curoky_tame//:recipes/b/better-enums/default/BUILD",
    )

    http_archive(
        name = "com_github_catchorg_catch2",
        urls = [
            "https://github.com/catchorg/Catch2/archive/refs/heads/devel.tar.gz",
        ],
        strip_prefix = "Catch2-devel",
        # build_file = "@com_curoky_tame//:recipes/c/catch2/v3/BUILD",
        # patch_cmds = ["mv src/catch2/catch_all.hpp src/catch2/catch.hpp"],
    )

    http_archive(
        name = "com_github_facebook_fatal",
        urls = [
            "https://github.com/facebook/fatal/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "fatal-main",
        build_file = "@com_curoky_tame//:recipes/f/fatal/default/BUILD",
    )
    http_archive(
        name = "com_github_google_flatbuffers",
        urls = [
            "https://github.com/google/flatbuffers/archive/refs/tags/v2.0.0.tar.gz",
        ],
        strip_prefix = "flatbuffers-2.0.0",
    )
    http_archive(
        name = "com_github_facebook_folly",
        urls = [
            "https://github.com/facebook/folly/archive/refs/tags/v2022.04.25.00.tar.gz",
        ],
        strip_prefix = "folly-2022.04.25.00",
        build_file = "@com_curoky_tame//:recipes/f/folly/default/BUILD",
        patch_cmds = [
            "sed -i -e 's/constexpr ::folly::detail::safe_assert_terminate_w/::folly::detail::safe_assert_terminate_w/g' folly/lang/SafeAssert.h",
        ],
    )
    http_archive(
        name = "com_github_gflags_gflags",
        urls = [
            "https://github.com/gflags/gflags/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "gflags-master",
    )

    http_archive(
        name = "com_github_google_glog",
        urls = ["https://github.com/google/glog/archive/refs/tags/v0.5.0.tar.gz"],
        strip_prefix = "glog-0.5.0",
    )

    http_archive(
        name = "com_github_google_googletest",
        urls = [
            "https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz",
        ],
        strip_prefix = "googletest-release-1.12.1",
    )
    http_archive(
        name = "com_github_arximboldi_immer",
        urls = [
            "https://github.com/arximboldi/immer/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "immer-master",
    )

    http_archive(
        name = "com_github_open_source_parsers_jsoncpp",
        urls = [
            "https://github.com/open-source-parsers/jsoncpp/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "jsoncpp-master",
    )

    http_archive(
        name = "com_github_tyckesak_laugh",
        urls = [
            "https://github.com/tyckesak/laugh/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "laugh-main",
        build_file = "@com_curoky_tame//:recipes/l/laugh/default/BUILD",
        patch_cmds = [
            "sed -i -e 's$concurrentqueue/moodycamel/$$' Include/Laugh/Actor.hpp",
        ],
    )

    http_archive(
        name = "com_pagure_libaio",
        urls = [
            "https://pagure.io/libaio/archive/libaio-0.3.113/libaio-libaio-0.3.113.tar.gz",
        ],
        strip_prefix = "libaio-libaio-0.3.113",
        build_file = "@com_curoky_tame//:recipes/l/libaio/default/BUILD",
    )

    http_archive(
        name = "com_google_protobuf",
        urls = [
            "https://github.com/protocolbuffers/protobuf/archive/refs/tags/v3.19.4.tar.gz",
        ],
        strip_prefix = "protobuf-3.19.4",
        patch_cmds = ["sed -i -e 's/@zlib/@net_zlib_zlib/g' BUILD"],
    )

    http_archive(
        name = "com_github_google_re2",
        urls = ["https://github.com/google/re2/archive/refs/heads/main.tar.gz"],
        strip_prefix = "re2-main",
    )

    http_archive(
        name = "com_github_aappleby_smhasher",
        urls = [
            "https://github.com/aappleby/smhasher/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "smhasher-master",
        build_file = "@com_curoky_tame//:recipes/s/smhasher/default/BUILD",
    )

    http_archive(
        name = "com_github_protocolbuffers_upb",
        urls = [
            "https://github.com/protocolbuffers/upb/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "upb-main",
    )

    http_archive(
        name = "com_github_ubpa_usrefl",
        urls = [
            "https://github.com/Ubpa/USRefl/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "USRefl-master",
        build_file = "@com_curoky_tame//:recipes/u/usrefl/default/BUILD",
    )

def pkg_rules_dependencies():
    dep_libs()
    dep_tools()

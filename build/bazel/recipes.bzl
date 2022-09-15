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

def pkg_rules_dependencies():
    http_archive(
        name = "com_github_abseil_abseil_cpp",
        urls = [
            "https://github.com/abseil/abseil-cpp/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "abseil-cpp-master",
    )

    http_archive(
        name = "build_bazel_apple_support",
        urls = [
            "https://github.com/bazelbuild/apple_support/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "apple_support-master",
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
        name = "com_grail_bazel_compdb",
        urls = [
            "https://github.com/grailbio/bazel-compilation-database/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "bazel-compilation-database-master",
    )

    http_archive(
        name = "hedron_compile_commands",
        urls = [
            "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "bazel-compile-commands-extractor-main",
    )

    http_archive(
        name = "bazel_gazelle",
        urls = [
            "https://github.com/bazelbuild/bazel-gazelle/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "bazel-gazelle-master",
    )

    http_archive(
        name = "bazel_skylib",
        urls = [
            "https://github.com/bazelbuild/bazel-skylib/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "bazel-skylib-main",
    )

    # http_archive(
    #     name="com_justbuchanan_rules_qt",
    #     urls=[
    #         "https://github.com/justbuchanan/bazel_rules_qt/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="bazel_rules_qt-master",
    #     patch_cmds=[
    #         "sed -i -e 's^/usr/include/x86_64-linux-gnu/qt5^/home/linuxbrew/.linuxbrew/opt/qt@5/^g' qt_configure.bzl"
    #     ],
    # )

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

    # http_archive(
    #     name="binutils",
    #     urls=["https://ftp.gnu.org/gnu/binutils/binutils-2.38.tar.gz"],
    #     strip_prefix="binutils-2.38",
    #     patch_args=["-p1"],
    #     patches=[
    #         "@com_curoky_tame//:recipes/b/binutils/default/patch/0001-remove-bfd-config-check.patch"
    #     ],
    # )

    # http_archive(
    #     name="com_github_fraillt_bitsery",
    #     urls=[
    #         "https://github.com/fraillt/bitsery/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="bitsery-master",
    #     build_file="@com_curoky_tame//:recipes/b/bitsery/default/BUILD",
    # )

    http_archive(
        name = "com_github_google_boringssl",
        urls = [
            "https://github.com/google/boringssl/archive/refs/heads/master-with-bazel.tar.gz",
        ],
        strip_prefix = "boringssl-master-with-bazel",
    )

    http_archive(
        name = "com_github_google_brotli",
        urls = [
            "https://github.com/google/brotli/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "brotli-master",
    )

    http_archive(
        name = "com_github_catchorg_catch2",
        urls = [
            "https://github.com/catchorg/Catch2/archive/refs/heads/devel.tar.gz",
        ],
        strip_prefix = "Catch2-devel",
        build_file = "@com_curoky_tame//:recipes/c/catch2/v3/BUILD",
        patch_cmds = ["mv src/catch2/catch_all.hpp src/catch2/catch.hpp"],
    )

    http_archive(
        name="com_github_felixguendling_cista",
        urls=[
            "https://github.com/felixguendling/cista/archive/refs/heads/master.tar.gz"
        ],
        strip_prefix="cista-master",
        build_file="@com_curoky_tame//:recipes/c/cista/default/BUILD",
    )

    # http_archive(
    #     name="com_github_google_cityhash",
    #     urls=[
    #         "https://github.com/google/cityhash/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="cityhash-master",
    #     build_file="@com_curoky_tame//:recipes/c/cityhash/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_davegamble_cjson",
    #     urls=[
    #         "https://github.com/DaveGamble/cJSON/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="cJSON-master",
    #     build_file="@com_curoky_tame//:recipes/c/cjson/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_cameron314_concurrentqueue",
    #     urls=[
    #         "https://github.com/cameron314/concurrentqueue/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="concurrentqueue-master",
    #     build_file=
    #     "@com_curoky_tame//:recipes/c/concurrentqueue/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_yhirose_cpp_httplib",
    #     urls=[
    #         "https://github.com/yhirose/cpp-httplib/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="cpp-httplib-master",
    #     build_file="@com_curoky_tame//:recipes/c/cpp-httplib/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_yhirose_cpp_peglib",
    #     urls=[
    #         "https://github.com/yhirose/cpp-peglib/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="cpp-peglib-master",
    #     build_file="@com_curoky_tame//:recipes/c/cpp-peglib/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_cginternals_cppfs",
    #     urls=[
    #         "https://github.com/cginternals/cppfs/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="cppfs-master",
    #     build_file="@com_curoky_tame//:recipes/c/cppfs/cmake/BUILD",
    # )

    # http_archive(
    #     name="com_github_ryanhaining_cppitertools",
    #     urls=[
    #         "https://github.com/ryanhaining/cppitertools/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="cppitertools-master",
    #     build_file=
    #     "@com_curoky_tame//:recipes/c/cppitertools/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_libcpr_cpr",
    #     urls=["https://github.com/libcpr/cpr/archive/refs/heads/master.tar.gz"],
    #     strip_prefix="cpr-master",
    #     build_file="@com_curoky_tame//:recipes/c/cpr/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_google_crc32c",
    #     urls=[
    #         "https://github.com/google/crc32c/archive/refs/heads/main.tar.gz"
    #     ],
    #     strip_prefix="crc32c-main",
    #     build_file="@com_curoky_tame//:recipes/c/crc32c/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_curl_curl",
    #     urls=["https://github.com/curl/curl/archive/refs/heads/master.tar.gz"],
    #     strip_prefix="curl-master",
    #     build_file="@com_curoky_tame//:recipes/c/curl/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_google_diff_match_patch",
    #     urls=[
    #         "https://github.com/google/diff-match-patch/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="diff-match-patch-master",
    #     build_file=
    #     "@com_curoky_tame//:recipes/d/diff-match-patch/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_google_double_conversion",
    #     urls=[
    #         "https://github.com/google/double-conversion/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="double-conversion-master",
    #     build_file=
    #     "@com_curoky_tame//:recipes/d/double-conversion/default/BUILD",
    # )

    http_archive(
        name = "envoy_api",
        urls = [
            "https://github.com/envoyproxy/data-plane-api/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "data-plane-api-main",
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
        name = "com_github_facebook_fbthrift",
        urls = [
            "https://github.com/facebook/fbthrift/archive/refs/tags/v2022.04.25.00.tar.gz",
        ],
        strip_prefix = "fbthrift-2022.04.25.00",
        build_file = "@com_curoky_tame//:recipes/f/fbthrift/default/BUILD",
        patch_cmds = [
            "sed -i -e 's/folly::badge<ThriftServer>{},//g' thrift/lib/cpp2/server/ThriftServer.cpp",
            "sed -i -e 's/folly::badge<ThriftServer>,//g' thrift/lib/cpp2/server/ThriftServer.h",
        ],
    )

    http_archive(
        name = "com_github_facebookincubator_fizz",
        urls = [
            "https://github.com/facebookincubator/fizz/archive/refs/tags/v2022.04.25.00.tar.gz",
        ],
        strip_prefix = "fizz-2022.04.25.00",
        build_file = "@com_curoky_tame//:recipes/f/fizz/default/BUILD",
    )

    http_archive(
        name = "com_github_google_flatbuffers",
        urls = [
            "https://github.com/google/flatbuffers/archive/refs/tags/v2.0.0.tar.gz",
        ],
        strip_prefix = "flatbuffers-2.0.0",
    )

    # http_archive(
    #     name="com_github_fmtlib_fmt",
    #     urls=["https://github.com/fmtlib/fmt/archive/refs/heads/master.tar.gz"],
    #     strip_prefix="fmt-master",
    #     build_file="@com_curoky_tame//:recipes/f/fmt/default/BUILD",
    # )

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
        name = "com_google_googleapis",
        urls = [
            "https://github.com/googleapis/googleapis/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "googleapis-master",
    )

    http_archive(
        name="com_github_google_googletest",
        urls=[
            "https://github.com/google/googletest/archive/refs/heads/main.tar.gz"
        ],
        strip_prefix="googletest-main",
    )

    http_archive(
        name = "com_github_grpc_grpc",
        urls = ["https://github.com/grpc/grpc/archive/refs/heads/master.tar.gz"],
        strip_prefix = "grpc-master",
    )

    # http_archive(
    #     name="com_github_redis_hiredis",
    #     urls=[
    #         "https://github.com/redis/hiredis/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="hiredis-master",
    #     build_file="@com_curoky_tame//:recipes/h/hiredis/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_renatogarcia_icecream_cpp",
    #     urls=[
    #         "https://github.com/renatoGarcia/icecream-cpp/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="icecream-cpp-master",
    #     build_file=
    #     "@com_curoky_tame//:recipes/i/icecream-cpp/default/BUILD",
    # )

    http_archive(
        name = "com_github_arximboldi_immer",
        urls = [
            "https://github.com/arximboldi/immer/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "immer-master",
    )

    # http_archive(
    #     name="jemalloc",
    #     urls=[
    #         "https://github.com/jemalloc/jemalloc/archive/refs/heads/dev.tar.gz"
    #     ],
    #     strip_prefix="jemalloc-dev",
    #     build_file="@com_curoky_tame//:recipes/j/jemalloc/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_nlohmann_json",
    #     urls=[
    #         "https://github.com/nlohmann/json/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="json-master",
    #     build_file="@com_curoky_tame//:recipes/j/json/default/BUILD",
    # )

    http_archive(
        name = "com_github_open_source_parsers_jsoncpp",
        urls = [
            "https://github.com/open-source-parsers/jsoncpp/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "jsoncpp-master",
        # build_file="@com_curoky_tame//:recipes/j/jsoncpp/default/BUILD",
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

    # http_archive(
    #     name="libdwarf",
    #     urls=["https://www.prevanders.net/libdwarf-0.3.1.tar.xz"],
    #     strip_prefix="libdwarf-0.3.1",
    #     build_file="@com_curoky_tame//:recipes/l/libdwarf/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_libevent_libevent",
    #     urls=[
    #         "https://github.com/libevent/libevent/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="libevent-master",
    #     build_file="@com_curoky_tame//:recipes/l/libevent/cmake/BUILD",
    # )

    http_archive(
        name = "libiberty",
        urls = ["https://ftpmirror.gnu.org/gcc/gcc-11.2.0/gcc-11.2.0.tar.xz"],
        strip_prefix = "gcc-11.2.0",
        build_file = "@com_curoky_tame//:recipes/l/libiberty/default/BUILD",
    )

    # http_archive(
    #     name="com_github_jedisct1_libsodium",
    #     urls=[
    #         "https://github.com/jedisct1/libsodium/archive/refs/tags/1.0.16.tar.gz"
    #     ],
    #     strip_prefix="libsodium-1.0.16",
    #     build_file="@com_curoky_tame//:recipes/l/libsodium/default/BUILD",
    # )

    # http_archive(
    #     name="libunwind",
    #     urls=[
    #         "https://github.com/libunwind/libunwind/archive/refs/tags/v1.6.2.tar.gz"
    #     ],
    #     strip_prefix="libunwind-1.6.2",
    #     build_file="@com_curoky_tame//:recipes/l/libunwind/autotools/BUILD",
    # )

    # http_archive(
    #     name="com_github_axboe_liburing",
    #     urls=[
    #         "https://github.com/axboe/liburing/archive/refs/tags/liburing-2.1.tar.gz"
    #     ],
    #     strip_prefix="liburing-liburing-2.1",
    #     build_file="@com_curoky_tame//:recipes/l/liburing/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_libuv_libuv",
    #     urls=[
    #         "https://github.com/libuv/libuv/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="libuv-master",
    #     build_file="@com_curoky_tame//:recipes/l/libuv/cmake/BUILD",
    # )

    # http_archive(
    #     name="com_github_lua_lua",
    #     urls=["https://github.com/lua/lua/archive/refs/heads/master.tar.gz"],
    #     strip_prefix="lua-master",
    #     build_file="@com_curoky_tame//:recipes/l/lua/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_lz4_lz4",
    #     urls=["https://github.com/lz4/lz4/archive/refs/heads/dev.tar.gz"],
    #     strip_prefix="lz4-dev",
    #     build_file="@com_curoky_tame//:recipes/l/lz4/default/BUILD",
    # )

    http_archive(
        name="org_gnu_m4",
        urls=["https://ftp.gnu.org/gnu/m4/m4-1.4.19.tar.xz"],
        strip_prefix="m4-1.4.19",
        build_file="@com_curoky_tame//:recipes/m/m4/default/BUILD",
    )

    # http_archive(
    #     name="com_github_msgpack_msgpack_c",
    #     urls=[
    #         "https://github.com/msgpack/msgpack-c/archive/refs/heads/cpp_master.tar.gz"
    #     ],
    #     strip_prefix="msgpack-c-cpp_master",
    #     build_file="@com_curoky_tame//:recipes/m/msgpack-c/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_neargye_nameof",
    #     urls=[
    #         "https://github.com/Neargye/nameof/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="nameof-master",
    #     build_file="@com_curoky_tame//:recipes/n/nameof/default/BUILD",
    # )

    # http_archive(
    #     name="org_openssl",
    #     urls=[
    #         "https://github.com/openssl/openssl/archive/refs/tags/OpenSSL_1_1_1g.tar.gz"
    #     ],
    #     strip_prefix="openssl-OpenSSL_1_1_1g",
    #     build_file="@com_curoky_tame//:recipes/o/openssl/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_greg7mdp_parallel_hashmap",
    #     urls=[
    #         "https://github.com/greg7mdp/parallel-hashmap/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="parallel-hashmap-master",
    #     build_file=
    #     "@com_curoky_tame//:recipes/p/parallel-hashmap/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_p_h_c_phc_winner_argon2",
    #     urls=[
    #         "https://github.com/P-H-C/phc-winner-argon2/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="phc-winner-argon2-master",
    #     build_file=
    #     "@com_curoky_tame//:recipes/p/phc-winner-argon2/default/BUILD",
    # )

    http_archive(
        name = "com_google_protobuf",
        urls = [
            "https://github.com/protocolbuffers/protobuf/archive/refs/tags/v3.19.4.tar.gz",
        ],
        strip_prefix = "protobuf-3.19.4",
        patch_cmds = ["sed -i -e 's/@zlib/@net_zlib_zlib/g' BUILD"],
    )

    http_archive(
        name = "com_github_facebook_proxygen",
        urls = [
            "https://github.com/facebook/proxygen/archive/refs/tags/v2022.04.25.00.tar.gz",
        ],
        strip_prefix = "proxygen-2022.04.25.00",
        build_file = "@com_curoky_tame//:recipes/p/proxygen/default/BUILD",
    )

    # http_archive(
    #     name="com_github_tencent_rapidjson",
    #     urls=[
    #         "https://github.com/Tencent/rapidjson/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="rapidjson-master",
    #     build_file="@com_curoky_tame//:recipes/r/rapidjson/default/BUILD",
    # )

    http_archive(
        name = "com_github_google_re2",
        urls = ["https://github.com/google/re2/archive/refs/heads/main.tar.gz"],
        strip_prefix = "re2-main",
    )

    # http_archive(
    #     name="com_github_cameron314_readerwriterqueue",
    #     urls=[
    #         "https://github.com/cameron314/readerwriterqueue/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="readerwriterqueue-master",
    #     build_file=
    #     "@com_curoky_tame//:recipes/r/readerwriterqueue/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_veselink1_refl_cpp",
    #     urls=[
    #         "https://github.com/veselink1/refl-cpp/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="refl-cpp-master",
    #     build_file="@com_curoky_tame//:recipes/r/refl-cpp/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_mrtazz_restclient_cpp",
    #     urls=[
    #         "https://github.com/mrtazz/restclient-cpp/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="restclient-cpp-master",
    #     build_file=
    #     "@com_curoky_tame//:recipes/r/restclient-cpp/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_rttrorg_rttr",
    #     urls=[
    #         "https://github.com/rttrorg/rttr/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="rttr-master",
    #     build_file="@com_curoky_tame//:recipes/r/rttr/default/BUILD",
    # )

    http_archive(
        name = "build_bazel_rules_apple",
        urls = [
            "https://github.com/bazelbuild/rules_apple/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "rules_apple-master",
    )

    http_archive(
        name = "rules_bison",
        urls = [
            "https://github.com/jmillikin/rules_bison/archive/refs/tags/v0.2.tar.gz",
        ],
        strip_prefix = "rules_bison-0.2",
        patch_cmds = ["sed -i '83d' bison/bison.bzl"],
    )

    http_archive(
        name = "com_github_nelhage_rules_boost",
        urls = [
            "https://github.com/nelhage/rules_boost/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix="rules_boost-master",
        patch_cmds=[
            "sed -i -e 's/openssl/org_openssl/g' boost/boost.bzl",
            "sed -i -e 's/org_lzma_lzma/org_xz_xz/g' boost/boost.bzl",
            "sed -i -e 's?org_lzma_lzma//:lzma?org_xz_xz//:xz?g' BUILD.boost",
            "sed -i -e 's/org_lzma_lzma/org_xz_xz/g' BUILD.lzma"
        ],
    )

    http_archive(
        name = "rules_flex",
        urls = [
            "https://github.com/jmillikin/rules_flex/archive/refs/tags/v0.2.tar.gz",
        ],
        strip_prefix = "rules_flex-0.2",
        patch_cmds = ["sed -i '76d' flex/flex.bzl"],
    )

    http_archive(
        name = "rules_foreign_cc",
        urls = [
            "https://github.com/bazelbuild/rules_foreign_cc/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "rules_foreign_cc-main",
    )

    http_archive(
        name = "io_bazel_rules_go",
        urls = [
            "https://github.com/bazelbuild/rules_go/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "rules_go-master",
    )

    http_archive(
        name = "rules_m4",
        urls = [
            "https://github.com/jmillikin/rules_m4/archive/refs/heads/trunk.tar.gz",
        ],
        strip_prefix = "rules_m4-trunk",
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

    http_archive(
        name = "rules_python",
        urls = [
            "https://github.com/bazelbuild/rules_python/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "rules_python-main",
    )

    http_archive(
        name = "com_github_aappleby_smhasher",
        urls = [
            "https://github.com/aappleby/smhasher/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "smhasher-master",
        build_file = "@com_curoky_tame//:recipes/s/smhasher/default/BUILD",
    )

    # http_archive(
    #     name="com_github_google_snappy",
    #     urls=[
    #         "https://github.com/google/snappy/archive/refs/heads/main.tar.gz"
    #     ],
    #     strip_prefix="snappy-main",
    #     build_file="@com_curoky_tame//:recipes/s/snappy/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_gabime_spdlog",
    #     urls=[
    #         "https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz"
    #     ],
    #     strip_prefix="spdlog-1.10.0",
    #     build_file="@com_curoky_tame//:recipes/s/spdlog/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_taskflow_taskflow",
    #     urls=[
    #         "https://github.com/taskflow/taskflow/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="taskflow-master",
    #     build_file="@com_curoky_tame//:recipes/t/taskflow/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_oneapi_src_onetbb",
    #     urls=[
    #         "https://github.com/oneapi-src/oneTBB/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="oneTBB-master",
    #     build_file="@com_curoky_tame//:recipes/t/tbb/cmake/BUILD",
    # )

    http_archive(
        name = "com_github_apache_thrift",
        urls = [
            "https://github.com/apache/thrift/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "thrift-master",
        build_file = "@com_curoky_tame//:recipes/t/thrift/default/BUILD",
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

    http_archive(
        name = "com_github_facebook_wangle",
        urls = [
            "https://github.com/facebook/wangle/archive/refs/tags/v2022.04.25.00.tar.gz",
        ],
        strip_prefix = "wangle-2022.04.25.00",
        build_file = "@com_curoky_tame//:recipes/w/wangle/default/BUILD",
    )

    # http_archive(
    #     name="com_github_cyan4973_xxhash",
    #     urls=[
    #         "https://github.com/Cyan4973/xxHash/archive/refs/heads/dev.tar.gz"
    #     ],
    #     strip_prefix="xxHash-dev",
    #     build_file="@com_curoky_tame//:recipes/x/xxhash/default/BUILD",
    # )

    http_archive(
        name="org_xz_xz",
        urls=[
            "https://github.com/xz-mirror/xz/archive/refs/heads/master.tar.gz"
        ],
        strip_prefix="xz-master",
        build_file="@com_curoky_tame//:recipes/x/xz/default/BUILD",
    )

    # http_archive(
    #     name="net_zlib_zlib",
    #     urls=[
    #         "https://github.com/madler/zlib/archive/refs/heads/master.tar.gz"
    #     ],
    #     strip_prefix="zlib-master",
    #     build_file="@com_curoky_tame//:recipes/z/zlib/default/BUILD",
    # )

    # http_archive(
    #     name="com_github_facebook_zstd",
    #     urls=[
    #         "https://github.com/facebook/zstd/archive/refs/tags/v1.5.0.tar.gz"
    #     ],
    #     strip_prefix="zstd-1.5.0",
    #     build_file="@com_curoky_tame//:recipes/z/zstd/default/BUILD",
    # )

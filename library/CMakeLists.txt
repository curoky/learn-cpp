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

file(GLOB_RECURSE main_sources *.cc **/*.cc)

# list(REMOVE_ITEM main_sources "networking/http/cpr.cc")
list(FILTER main_sources EXCLUDE REGEX "benchmark/*")
list(FILTER main_sources EXCLUDE REGEX "construction/*")
list(FILTER main_sources EXCLUDE REGEX "compiler/gdb/*")
list(FILTER main_sources EXCLUDE REGEX "compiler/llvm/*")
list(FILTER main_sources EXCLUDE REGEX "coverage/*")
list(FILTER main_sources EXCLUDE REGEX "crypto/murmurhash.cc")
list(FILTER main_sources EXCLUDE REGEX "diagnostics/symbolizer/*")
list(FILTER main_sources EXCLUDE REGEX "formatting/icecream.cc")
list(FILTER main_sources EXCLUDE REGEX "gcc/compiler/feature_test.cc")
list(FILTER main_sources EXCLUDE REGEX "networking/http/cpr.cc")
list(FILTER main_sources EXCLUDE REGEX "numeric/constants.cc")
list(FILTER main_sources EXCLUDE REGEX "reflection/nameof.cc")
list(FILTER main_sources EXCLUDE REGEX "reflection/rttr.cc")
list(FILTER main_sources EXCLUDE REGEX "sanitizers/*")
list(FILTER main_sources EXCLUDE REGEX "serialization/cista.cc")
list(FILTER main_sources EXCLUDE REGEX "serialization/fbthrift/*")
list(FILTER main_sources EXCLUDE REGEX "serialization/flatbuffers/*")
list(FILTER main_sources EXCLUDE REGEX "serialization/protobuf/*")
list(FILTER main_sources EXCLUDE REGEX "serialization/thrift/*")
list(FILTER main_sources EXCLUDE REGEX "strings-library/abi-string/*")
list(FILTER main_sources EXCLUDE REGEX "technique/*")
list(FILTER main_sources EXCLUDE REGEX "template-metaprogramming/fatal/*")
list(FILTER main_sources EXCLUDE REGEX "template-metaprogramming/haha.cc")
list(FILTER main_sources EXCLUDE REGEX "template-metaprogramming/has/*")
list(FILTER main_sources EXCLUDE REGEX "testing/catch2.cc")
list(FILTER main_sources EXCLUDE REGEX "types/RTTI/typeinfo.cc")
list(FILTER main_sources EXCLUDE REGEX "utilities/program/abort/*")
list(FILTER main_sources EXCLUDE REGEX "wheel/catch2/*")
list(FILTER main_sources EXCLUDE REGEX "wheel/corotine/*")

cc_test(
  cpp_main
  SRCS ${main_sources}
  DEPS absl::algorithm_container
       absl::debugging
       absl::str_format
       absl::strings
       Crc32c::crc32c
       cjson
       cppfs::cppfs
       cpr::cpr
       CURL::libcurl
       Folly::folly
       glog::glog
       GTest::gmock
       GTest::gtest
       JsonCpp::JsonCpp
       restclient-cpp
       # RTTR::Core_Lib # TTR::Core
       Snappy::snappy
       TBB::tbb
       uv_a
       zstd::libzstd_static
       Boost::serialization
       Boost::context
       Catch2::Catch2WithMain
       cityhash
  # benchmark::benchmark
  #  gflags::gflags_static
  #  Boost::boost Boost::algorithm
)

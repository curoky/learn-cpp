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

# find_package(LLVM REQUIRED CONFIG) add_definitions(${LLVM_DEFINITIONS})
# include_directories(${LLVM_INCLUDE_DIRS})
# link_directories(${LLVM_LIBRARY_DIRS}) if(${LLVM_VERSION_MAJOR}
# VERSION_GREATER_EQUAL 10) set(CMAKE_CXX_STANDARD 14) endif()

add_library(
  HelloPass MODULE
  # List your source files here.
  hello_pass.cc)

target_compile_options(HelloPass PRIVATE "-fno-rtti")
target_include_directories(HelloPass PRIVATE ${TARO_INCLUDE_DIRS})

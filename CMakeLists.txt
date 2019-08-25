# Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
#
# This file is part of my-own-x.
# See https://github.com/curoky/my-own-x for further info.
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

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

cmake_policy(VERSION 3.20)

set(PACKAGE_NAME "my-own-x")
set(PACKAGE_VERSION "1.0.0")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TARNAME "${PACKAGE_NAME}-${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "https://github.com/curoky/my-own-x/issues")
project(${PACKAGE_NAME} LANGUAGES CXX)

# Specify compiler
# set(CMAKE_C_COMPILER /usr/bin/gcc)
# set(CMAKE_CXX_COMPILER /usr/bin/g++)
include(config/cmake/Copts.cmake)

# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setup iwyu(need iwyu)
# set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "/home/linuxbrew/.linuxbrew/bin/include-what-you-use;-Xiwyu;any;-Xiwyu;iwyu;-Xiwyu;args")

# list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Setup ccache
set(CMAKE_CXX_COMPILER_LAUNCHER "ccache")

# Setup bazel.cmake
include(build-system/cmake/bazel.cmake)

if(${USED_PM} STREQUAL "vcpkg")
  include(config/cmake/vcpkg/setup.cmake)
  include(config/cmake/vcpkg/deps.cmake)
elseif(${USED_PM} STREQUAL "conan")
  include(builddir/conan/conan_toolchain.cmake)
  include(config/cmake/conan/deps.cmake)
elseif(${USED_PM} STREQUAL "cpm")
  include(config/cmake/vcpkg/setup.cmake)
  include(config/cmake/cpm/setup.cmake)
  include(config/cmake/cpm/deps.cmake)
endif()

# Setup generator
include(config/cmake/generator/gen_thrift.cmake)

# Add subdirectory
add_subdirectory(design-pattern)
add_subdirectory(lang/cpp)
add_subdirectory(library/thrift/tutorial/idl)
add_subdirectory(library/thrift/tutorial/cpp)

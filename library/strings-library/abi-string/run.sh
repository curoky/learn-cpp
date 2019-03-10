#!/usr/bin/env bash
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

set -xeuo pipefail

export PATH=/home/linuxbrew/.linuxbrew/opt/gcc@4.9/bin:/home/linuxbrew/.linuxbrew/opt/gcc@10/bin:$PATH

# g++-4.9 -o gcc4-string sizeof-string.cc
# g++-10 -o gcc10-string sizeof-string.cc

# ./gcc4-string
# ./gcc10-string

unset CC
unset CXX
bazel run sizeof-string

export CC=/home/linuxbrew/.linuxbrew/opt/gcc@4.9/bin/gcc-4.9
export CXX=/home/linuxbrew/.linuxbrew/opt/gcc@4.9/bin/g++-4.9
bazel run sizeof-string

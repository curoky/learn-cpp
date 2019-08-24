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

BAZEL_BIN=$(bazel info bazel-bin)
BIN_PATH=$BAZEL_BIN/dumbo/magic/hook/preload

echo "BAZEL_BIN: $BAZEL_BIN"
echo "BIN_PATH: $BIN_PATH"

# ls -la $BIN_PATH
LD_PRELOAD="$BIN_PATH/libtime.so $BIN_PATH/libmalloc.so" "$BIN_PATH/main"

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

EXEC_ROOT=$(bazel info execution_root)
BAZEL_BIN=$(bazel info bazel-bin)
CMDS_PATH=$BAZEL_BIN/bazel/compdb/compile_commands.json

echo "EXEC_ROOT: $EXEC_ROOT"
echo "BAZEL_BIN: $BAZEL_BIN"
echo "CMDS_PATH: $CMDS_PATH"

# gen compile_commands.json
bazel build //bazel/compdb:compdb --check_visibility=false

# patch compile_commands.json
sed -i 's/-fno-canonical-system-headers//g' "$CMDS_PATH"
sed -i 's/-Wunused-but-set-parameter/-Wunused-parameter/g' "$CMDS_PATH"
sed -i 's/-Wno-free-nonheap-object/-Wno-sequence-point/g' "$CMDS_PATH"
sed -i 's/-gno-statement-frontiers//g' "$CMDS_PATH"
sed -i 's/-gno-variable-location-views//g' "$CMDS_PATH"
# sed -i 's%__EXEC_ROOT__%/shm/bazel/execroot/com_github_curoky_dumbo%g' $CMDS_PATH
cp -f "$CMDS_PATH" "$EXEC_ROOT"/compile_commands.json

analyze-build --verbose --cdb "$EXEC_ROOT"/compile_commands.json -o clang-analysis \
  --html-title "Dumbo report" \
  --exclude "$EXEC_ROOT"/external \
  --exclude "$EXEC_ROOT"/bazel-out

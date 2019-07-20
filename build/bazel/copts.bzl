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

"""dumbo specific copts.
"""

DUMBO_DEFAULT_COPTS = [
    "-g",
    "-fno-omit-frame-pointer",
    # "-fsanitize=address",
    "-std=c++2a",
]

DEFAULT_C_COPTS = BASE_C_COPTS
DEFAULT_CPP_COPTS = BASE_CPP_COPTS
TEST_CPP_COPTS = _TEST_CPP_COPTS

DEFAULT_LINKOPTS = _DEFAULT_LINKOPTS
TEST_LINKOPTS = _TEST_LINKOPTS

/*
 * Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
 *
 * This file is part of learn-cpp.
 * See https://github.com/curoky/learn-cpp for further info.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// constructor 支持 so 文件的函数调用
// 参考：https://blog.csdn.net/tianmohust/article/details/45310349

#include <catch2/catch_test_macros.hpp>

int count = 0;

// 函数属性声明
void brefore_main() __attribute__((constructor));
void after_main() __attribute__((destructor));

void brefore_main() { count++; }
void after_main() { count--; }

TEST_CASE("simple test", "[Constructor]") { REQUIRE(count == 1); }

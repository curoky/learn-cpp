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

#include <folly/experimental/symbolizer/SignalHandler.h>

/*
*** Aborted at 1612434399 (Unix time, try 'date -d @1612434399') ***
*** Signal 4 (SIGILL) (0x5652e5fffc78) received by PID 573792 (pthread TID 0x7f4769aed400) (linux
TID 573792) (code: illegal operand), stack trace: *** (error retrieving stack trace) [1]    573792
illegal hardware instruction (core dumped)  bazel-bin/dumbo/magic/symbolizer/crash
*/
int main() {
  folly::symbolizer::installFatalSignalHandler();
  __builtin_trap();
}

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

// clang-format off
/*

## throw

*** Aborted at 1661872059 (unix time) try "date -d @1661872059" if you are using GNU date ***
PC: @                0x0 (unknown)
*** SIGABRT (@0x3e800130d82) received by PID 1248642 (TID 0x7f2b5512d740) from PID 1248642; stack trace: ***
    @     0x7f2b5516fbf0 (unknown)
    @     0x7f2b551bcbc7 __pthread_kill_implementation
    @     0x7f2b5516fb46 __GI_raise
    @     0x7f2b5515a4b5 __GI_abort
    @     0x7f2b554dfa89 _ZN9__gnu_cxx27__verbose_terminate_handlerEv.cold
    @     0x7f2b554eaf0a __cxxabiv1::__terminate()
    @     0x7f2b554eaf75 std::terminate()
    @     0x7f2b554eb1c7 __cxa_throw
    @           0x4064c5 A()
    @           0x4064ce B()
    @           0x4064ea main
    @     0x7f2b5515b24e __libc_start_call_main
    @     0x7f2b5515b309 __libc_start_main_alias_2
    @           0x4063d5 _start
    @                0x0 (unknown)
[1]    1248642 abort (core dumped)  bazel run :with-glog

## bad pointer

*** Aborted at 1661872756 (unix time) try "date -d @1661872756" if you are using GNU date ***
PC: @                0x0 (unknown)
*** SIGSEGV (@0xffffffffffffffff) received by PID 1331203 (TID 0x7ff167322740) from PID 18446744073709551615; stack trace: ***
    @     0x7ff167364bf0 (unknown)
    @           0x406529 A_bad_pointer()
    @           0x40654d B()
    @           0x406569 main
    @     0x7ff16735024e __libc_start_call_main
    @     0x7ff167350309 __libc_start_main_alias_2
    @           0x406425 _start
    @                0x0 (unknown)
[1]    1331203 segmentation fault (core dumped)  bazel run :with-glog

*/

// clang-format on

#include <glog/logging.h>

void A_throw() { throw "Oh my god!"; }

void A_bad_pointer() {
  int *foo = (int *)-1;  // make a bad pointer
  printf("%d\n", *foo);  // causes segfault
}

void B() { A_bad_pointer(); }

int main(int argc, char const *argv[]) {
  google::InstallFailureSignalHandler();
  B();
  return 0;
}

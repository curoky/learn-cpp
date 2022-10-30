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

// Ref: https://github.com/google/sanitizers/wiki/MemorySanitizer#using-memorysanitizer
// Direct run: clang++ -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g -O2 umr.cc

#include <stdio.h>

int main(int argc, char** argv) {
  int* a = new int[10];
  a[5] = 0;
  if (a[argc]) printf("xx\n");
  delete[] a;
  return 0;
}

// Output:
// clang-format off
/*
  $ ./a.out
  ==560821==WARNING: MemorySanitizer: use-of-uninitialized-value
  /home/linuxbrew/.linuxbrew/bin/llvm-symbolizer: /home/linuxbrew/.linuxbrew/Cellar/llvm@11/11.reinstall/bin/../lib/libtinfo.so.5: no version information available (required by /home/linuxbrew/.linuxbrew/bin/llvm-symbolizer)
      #0 0x55f280aa0c35 in main /home/curoky/repos/cpp/dumbo/dumbo/sanitizers/memory/uninitialized-memory-read.cc:10:7
      #1 0x7f7aa6bdf0b2 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x270b2)
      #2 0x55f280a2424d in _start (/home/curoky/repos/cpp/dumbo/dumbo/sanitizers/memory/a.out+0x1e24d)

  SUMMARY: MemorySanitizer: use-of-uninitialized-value /home/curoky/repos/cpp/dumbo/dumbo/sanitizers/memory/uninitialized-memory-read.cc:10:7 in main
  Exiting
*/
// clang-format on

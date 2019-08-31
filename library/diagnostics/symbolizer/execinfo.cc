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

#include <execinfo.h>
#include <stdio.h>

#include <cstdlib>

void bt_sighandler() {
  void *trace[16];
  char **messages = static_cast<char **>(nullptr);
  int i, trace_size = 0;

  trace_size = backtrace(trace, 16);
  /* overwrite sigaction with caller's address */
  // trace[1] = (void *)ctx.rip;
  messages = backtrace_symbols(trace, trace_size);
  /* skip first stack frame (points here) */
  printf("[bt] Execution path:\n");
  for (i = 1; i < trace_size; ++i) {
    printf("[bt] #%d %s\n", i, messages[i]);

    /* find first occurence of '(' or ' ' in message[i] and assume
     * everything before that is the file name. (Don't go beyond 0 though
     * (string terminator)*/
    size_t p = 0;
    while (messages[i][p] != '(' && messages[i][p] != ' ' && messages[i][p] != 0) ++p;

    char syscom[256];
    sprintf(syscom, "addr2line %p -e %.*s", trace[i], p, messages[i]);  // NOLINT
    // last parameter is the file name of the symbol
    system(syscom);
  }

  exit(0);
}

int func_a(int a, char b) {
  char *p = reinterpret_cast<char *>(0xdeadbeef);

  a = a + b;
  bt_sighandler();
  return 0;
}

int func_b() {
  int res, a = 5;

  res = 5 + func_a(a, 't');

  return res;
}

int main() { printf("%d\n", func_b()); }

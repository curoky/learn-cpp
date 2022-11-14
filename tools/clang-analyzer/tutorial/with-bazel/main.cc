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
#include <stdio.h>
#include <stdlib.h>

#include <vector>

int main(int argc, char const *argv[]) {
  // Case: arrayIndexOutOfBounds
  {
    int a[2];
    a[0] = 0;
    a[1] = 0;
    a[2] = 0;
  }

  // Case: bufferAccessOutOfBounds
  {
    int a[3];
    int i;
    for (i = 0; i < 3; i++) a[i] = 0;
  }

  // Case: erase
  {
    std::vector<int> items;
    items.push_back(1);
    items.push_back(2);
    items.push_back(3);
    std::vector<int>::iterator iter;
    for (iter = items.begin(); iter != items.end();) {
      if (*iter == 2) {
        iter = items.erase(iter);
      } else {
        ++iter;
      }
    }
  }

  // Case: outOfBounds
  {
    char str[10];
    snprintf(str, 10, "%s", "abc");  // NOLINT
  }

  // Case: resourceLeak
  {
    FILE *a = fopen("good.c", "r");
    if (!a) return 0;
    fclose(a);
  }

  // Case: memleak
  {
    int result;
    char *a = (char *)malloc(10);
    a[0] = 0;
    result = a[0];
    free(a);
  }

  return 0;
}

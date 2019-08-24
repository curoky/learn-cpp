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

#include <dlfcn.h>
#include <stddef.h>

typedef void *(*sys_malloc_t)(size_t size);
typedef void (*sys_free_t)(void *ptr);

void *malloc(size_t size) {
  sys_malloc_t sys_malloc = (sys_malloc_t)dlsym(RTLD_NEXT, "malloc");
  if (sys_malloc) {
    void *p = sys_malloc(size);
    return p;
  } else {
    return NULL;
  }
}

void free(void *ptr) {
  sys_free_t sys_free = (sys_free_t)dlsym(RTLD_NEXT, "free");
  if (sys_free != NULL) {
    sys_free(ptr);
  } else {
  }
}

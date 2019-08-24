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

// 使用 _init 版本的 hook 方案
// 优点: 效率高
// 缺点: 存在递归依赖, 尤其不适合 malloc 这种

/*
  坑: bazel 编译报错如下
  ERROR: dumbo/magic/hook/preload/BUILD:14:11: Linking dumbo/magic/hook/preload/libtime.so failed:
(Exit 1): gcc failed: error executing command /usr/bin/gcc
@bazel-out/k8-dbg/bin/dumbo/magic/hook/preload/libtime.so-2.params
  /usr/bin/ld.gold: error: bazel-out/k8-dbg/bin/dumbo/magic/hook/preload/_objs/time/time-init.pic.o:
multiple definition of '_init'
  /usr/bin/ld.gold: /usr/lib/gcc/x86_64-linux-gnu/10/../../../x86_64-linux-gnu/crti.o: previous
definition here collect2: error: ld returned 1 exit status
  修复方案: 增加 -nostartfiles 编译参数
  参考:
  - https://stackoverflow.com/questions/5474969/overriding-init-function-in-c-how-safe-is-it
  - http://www.faqs.org/docs/Linux-HOWTO/Program-Library-HOWTO.html#INIT-AND-CLEANUP
*/

#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>

typedef time_t (*sys_time_t)(time_t *);
typedef int (*sys_rand_t)(void);

static sys_time_t g_sys_time = NULL;
static sys_rand_t g_sys_rand = NULL;

typedef void (*sys_init_t)(void);

void _init(void) {
  printf("[hook]: %s start\n", __func__);
  const char *err;

  g_sys_time = (sys_time_t)dlsym(RTLD_NEXT, "time");
  if ((err = dlerror()) != NULL) {
    fprintf(stderr, "dlsym (time) failed: %s\n", err);
  }

  g_sys_rand = (sys_rand_t)dlsym(RTLD_NEXT, "rand");
  if ((err = dlerror()) != NULL) {
    fprintf(stderr, "dlsym (rand) failed: %s\n", err);
  }

  // TODO(curoky): 是否需要调用被 hook 之前的_init
  /*
  sys_init_t sys_init = (sys_init_t)dlsym(RTLD_NEXT, "_init");
  if ((err = dlerror()) != NULL) {
    fprintf(stderr, "dlsym (_init) failed: %s\n", err);
  } else {
    sys_init();
  }
  */
}

time_t time(time_t *__timer) {
  printf("[hook]: %s start\n", __func__);
  return g_sys_time(__timer);
}

int rand(void) {
  printf("[hook]: %s start\n", __func__);
  return g_sys_rand();
}

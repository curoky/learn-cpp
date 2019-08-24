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

// ref: https://gist.github.com/nolanlum/ad2f2f01d0b2a2258895

/*
   LD_PRELOAD library to make bind and connect to use a virtual
   IP address as localaddress. Specified via the enviroment
   variable BIND_ADDR.

   Compile on Linux with:
   gcc -nostartfiles -fpic -shared bind.c -o bind.so -ldl -D_GNU_SOURCE


   Example in bash to make inetd only listen to the localhost
   lo interface, thus disabling remote connections and only
   enable to/from localhost:

   BIND_ADDR="127.0.0.1" LD_PRELOAD=./bind.so /sbin/inetd


   Example in bash to use your virtual IP as your outgoing
   sourceaddress for ircII:

   BIND_ADDR="your-virt-ip" LD_PRELOAD=./bind.so ircII

   Note that you have to set up your servers virtual IP first.


   This program was made by Daniel Ryde
   email: daniel@ryde.net
   web:   http://www.ryde.net/

   TODO: I would like to extend it to the accept calls too, like a
   general tcp-wrapper. Also like an junkbuster for web-banners.
   For libc5 you need to replace socklen_t with int.
*/

#include <arpa/inet.h>
#include <dlfcn.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int (*real_bind)(int, const struct sockaddr *, socklen_t);
int (*real_connect)(int, const struct sockaddr *, socklen_t);

char *bind_addr_env;
char *bind_addr6_env;

uint32_t inaddr_any_saddr;

uint32_t bind_addr_saddr;
struct sockaddr_in local_sockaddr_in[] = {0};

struct in6_addr bind_addr6;
struct sockaddr_in6 local_sockaddr_in6[] = {0};

void _init(void) {
  const char *err;

  real_bind = dlsym(RTLD_NEXT, "bind");
  if ((err = dlerror()) != NULL) {
    fprintf(stderr, "dlsym (bind): %s\n", err);
  }

  real_connect = dlsym(RTLD_NEXT, "connect");
  if ((err = dlerror()) != NULL) {
    fprintf(stderr, "dlsym (connect): %s\n", err);
  }

  inaddr_any_saddr = htonl(INADDR_ANY);
  if (bind_addr_env = getenv("BIND_ADDR")) {
    bind_addr_saddr = inet_addr(bind_addr_env);
    local_sockaddr_in->sin_family = AF_INET;
    local_sockaddr_in->sin_addr.s_addr = bind_addr_saddr;
    local_sockaddr_in->sin_port = htons(0);
  }

  if (bind_addr6_env = getenv("BIND_ADDR6")) {
    inet_pton(AF_INET6, bind_addr6_env, &bind_addr6);
    memset(local_sockaddr_in6, 0, sizeof(struct sockaddr_in6));
    local_sockaddr_in6->sin6_family = AF_INET6;
    memcpy(&local_sockaddr_in6->sin6_addr, &bind_addr6, sizeof(struct in6_addr));
    local_sockaddr_in6->sin6_port = htons(0);
  }
}

int bind(int fd, const struct sockaddr *sk, socklen_t sl) {
  static struct sockaddr_in *lsk_in;
  static struct sockaddr_in6 *lsk_in6;
  static char addr_str[INET6_ADDRSTRLEN];

  lsk_in = (struct sockaddr_in *)sk;
  lsk_in6 = (struct sockaddr_in6 *)sk;

  if (lsk_in->sin_family == AF_INET) {
#ifdef DEBUG
    inet_ntop(AF_INET, &lsk_in->sin_addr, addr_str, INET6_ADDRSTRLEN);
    printf("-bind: %d %s:%d\n", fd, addr_str, ntohs(lsk_in->sin_port));
#endif
    if ((lsk_in->sin_addr.s_addr == inaddr_any_saddr) && bind_addr_env) {
      lsk_in->sin_addr.s_addr = bind_addr_saddr;
    }
#ifdef DEBUG
    inet_ntop(AF_INET, &lsk_in->sin_addr, addr_str, INET6_ADDRSTRLEN);
    printf("+bind: %d %s:%d\n", fd, addr_str, ntohs(lsk_in->sin_port));
#endif
  } else if (lsk_in->sin_family == AF_INET6) {
#ifdef DEBUG
    inet_ntop(AF_INET6, &lsk_in6->sin6_addr, addr_str, INET6_ADDRSTRLEN);
    printf("-bind6: %d [%s]:%d\n", fd, addr_str, ntohs(lsk_in->sin_port));
#endif
    if (!memcmp(&lsk_in6->sin6_addr, &in6addr_any, sizeof(struct in6_addr)) && bind_addr6_env) {
      memcpy(&lsk_in6->sin6_addr, &bind_addr6, sizeof(struct in6_addr));
    }
#ifdef DEBUG
    inet_ntop(AF_INET6, &lsk_in6->sin6_addr, addr_str, INET6_ADDRSTRLEN);
    printf("+bind6: %d [%s]:%d\n", fd, addr_str, ntohs(lsk_in->sin_port));
#endif
  }

  return real_bind(fd, sk, sl);
}

int connect(int fd, const struct sockaddr *sk, socklen_t sl) {
  static struct sockaddr_in *rsk_in;
  static struct sockaddr_in6 *rsk_in6;
  static char addr_str[INET6_ADDRSTRLEN];

  rsk_in = (struct sockaddr_in *)sk;
  rsk_in6 = (struct sockaddr_in6 *)sk;

  if (rsk_in->sin_family == AF_INET) {
#ifdef DEBUG
    inet_ntop(AF_INET, &rsk_in->sin_addr, addr_str, INET6_ADDRSTRLEN);
    printf("connect: %d %s:%d\n", fd, addr_str, ntohs(rsk_in->sin_port));
#endif
    if (bind_addr_env) {
#ifdef DEBUG
      inet_ntop(AF_INET, &local_sockaddr_in->sin_addr, addr_str, INET6_ADDRSTRLEN);
      printf("++ bind: %d %s\n", fd, addr_str);
#endif
      real_bind(fd, (struct sockaddr *)local_sockaddr_in, sizeof(struct sockaddr_in));
    }
  } else if (rsk_in->sin_family == AF_INET6) {
#ifdef DEBUG
    inet_ntop(AF_INET6, &rsk_in6->sin6_addr, addr_str, INET6_ADDRSTRLEN);
    printf("connect6: %d [%s]:%d\n", fd, addr_str, ntohs(rsk_in->sin_port));
#endif
    if (bind_addr6_env) {
#ifdef DEBUG
      inet_ntop(AF_INET6, &local_sockaddr_in6->sin6_addr, addr_str, INET6_ADDRSTRLEN);
      printf("++ bind6: %d [%s]\n", fd, addr_str);
#endif
      real_bind(fd, (struct sockaddr *)local_sockaddr_in6, sizeof(struct sockaddr_in6));
    }
  }

  return real_connect(fd, sk, sl);
}

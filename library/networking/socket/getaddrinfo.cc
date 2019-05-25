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

#include <catch2/catch_test_macros.hpp>

TEST_CASE("simple test", "[Getaddrinfo]") {
  // struct addrinfo hints;
  // struct addrinfo *result, *rp;
  // int sfd, s;
  // struct sockaddr_storage peer_addr;
  // socklen_t peer_addr_len;
  // ssize_t nread;
  // char buf[BUF_SIZE];

  // memset(&hints, 0, sizeof(struct addrinfo));
  // hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  // hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
  // hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  // hints.ai_protocol = 0;          /* Any protocol */
  // hints.ai_canonname = NULL;
  // hints.ai_addr = NULL;
  // hints.ai_next = NULL;

  // REQUIRE(getaddrinfo(NULL, argv[1], &hints, &result) == 0);
  // if (!= 0) {
  //     fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
  //     exit(EXIT_FAILURE);
  // }
}

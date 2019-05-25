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

// http://man7.org/linux/man-pages/man3/getifaddrs.3.html#EXAMPLE

#include <catch2/catch_test_macros.hpp>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

TEST_CASE("simple test", "[Ifaddrs]") {
  /*
  lo       AF_PACKET (17)
                  tx_packets =  361683198; rx_packets =  361683198
                  tx_bytes   = 3714118275; rx_bytes   = 3714118275
  eth0     AF_PACKET (17)
                  tx_packets = 2560646282; rx_packets = 3189477124
                  tx_bytes   =  730767045; rx_bytes   = 1641058594
  docker0  AF_PACKET (17)
                  tx_packets =         14; rx_packets =        135
                  tx_bytes   =        588; rx_bytes   =       8132
  lo       AF_INET (2)
                  address: <127.0.0.1>
  eth0     AF_INET (2)
                  address: <10.115.139.242>
  docker0  AF_INET (2)
                  address: <172.17.0.1>
  tun4     AF_INET (2)
                  address: <192.168.100.102>
  eth0     AF_INET6 (10)
                  address: <fe80::216:3eff:fe02:ccb6%eth0>
  */
  struct ifaddrs *ifaddr, *ifa;
  int family, s, n;
  char host[NI_MAXHOST];

  if (getifaddrs(&ifaddr) == -1) {
    perror("getifaddrs");
    FAIL("getifaddrs error");
    // exit(EXIT_FAILURE);
  }

  /* Walk through linked list, maintaining head pointer so we
     can free list later */

  for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
    if (ifa->ifa_addr == NULL) continue;

    family = ifa->ifa_addr->sa_family;

    /* Display interface name and family (including symbolic
       form of the latter for the common families) */

    printf("%-8s %s (%d)\n", ifa->ifa_name,
           (family == AF_PACKET)  ? "AF_PACKET"
           : (family == AF_INET)  ? "AF_INET"
           : (family == AF_INET6) ? "AF_INET6"
                                  : "???",
           family);

    /* For an AF_INET* interface address, display the address */

    if (family == AF_INET || family == AF_INET6) {
      s = getnameinfo(
          ifa->ifa_addr,
          (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), host,
          NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
      if (s != 0) {
        FAIL("getnameinfo() failed: " << gai_strerror(s));
        // exit(EXIT_FAILURE);
      }

      // printf("\t\taddress: <%s>\n", host);
      printf("\t\taddress: %s \n", host);

    } else if (family == AF_PACKET && ifa->ifa_data != NULL) {
      struct rtnl_link_stats* stats = static_cast<rtnl_link_stats*>(ifa->ifa_data);

      printf(
          "\t\ttx_packets = %10u; rx_packets = %10u\n"
          "\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
          stats->tx_packets, stats->rx_packets, stats->tx_bytes, stats->rx_bytes);
    }
  }

  freeifaddrs(ifaddr);
  // exit(EXIT_SUCCESS);
}

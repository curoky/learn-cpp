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
#include <fcntl.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <string>

// https://gityuan.com/2019/01/06/linux-epoll/
// https://blog.butonly.com/archives/page/2/
// https://aceld.gitbooks.io/libevent/content/
// https://www.cnblogs.com/Seapeak/archive/2010/04/08/1707807.html

TEST_CASE("ET LT", "[epoll]") {
  // epoll的水平触发和边缘触发
  // https://cloud.tencent.com/developer/article/1736793
  int pipefd[2];
  REQUIRE(pipe2(pipefd, O_NONBLOCK) == 0);

  int epollfd = epoll_create1(0);
  REQUIRE(epollfd > 0);

  struct epoll_event event;

  SECTION("LT") {
    // 1. socket接收缓冲区不为空 有数据可读 读事件一直触发
    // 2. socket发送缓冲区不满 可以继续写入数据 写事件一直触发
    // 备注：符合思维习惯，epoll_wait返回的事件就是socket的状态

    // by default, use level-triggered
    event.events = EPOLLIN;
    REQUIRE(epoll_ctl(epollfd, EPOLL_CTL_ADD, pipefd[0], &event) == 0);
    REQUIRE(epoll_wait(epollfd, &event, /*maxevents=*/10, /*timeout=*/10) == 0);

    write(pipefd[1], "a", 1);
    REQUIRE(epoll_wait(epollfd, &event, 10, 10) == 1);

    REQUIRE(epoll_wait(epollfd, &event, 10, 10) == 1);
    char buf;
    read(pipefd[0], &buf, 1);
    REQUIRE(epoll_wait(epollfd, &event, 10, 10) == 0);
  }

  SECTION("ET") {
    // 1. socket的接收缓冲区状态变化时触发读事件，即空的接收缓冲区刚接收到数据时触发读事件
    // 2. socket的发送缓冲区状态变化时触发写事件，即满的缓冲区刚空出空间时触发读事件
    // 备注：仅在状态变化时触发事件

    event.events = EPOLLIN | EPOLLET;
    REQUIRE(epoll_ctl(epollfd, EPOLL_CTL_ADD, pipefd[0], &event) == 0);

    REQUIRE(epoll_wait(epollfd, &event, 10, 10) == 0);

    write(pipefd[1], "a", 1);
    REQUIRE(epoll_wait(epollfd, &event, 10, 10) == 1);

    REQUIRE(epoll_wait(epollfd, &event, 10, 10) == 0);
  }
}

// TODO(curoky): add EPOLLRDHUP example
// https://blog.csdn.net/yongqingjiao/article/details/78819791

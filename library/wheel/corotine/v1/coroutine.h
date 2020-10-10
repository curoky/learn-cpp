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

// https://github.com/chenyahui/AnnotatedCode/blob/master/coroutine/coroutine.c

#pragma once
#include <boost/intrusive/list.hpp>
#include <spdlog/spdlog.h>
#include <ucontext.h>

#include <array>
#include <functional>
#include <list>
#include <memory>
#include <utility>
#include <vector>
#include <boost/
constexpr static size_t STACK_SIZE = 1024 * 1024;

struct Coroutine;
struct Schedule {
  Schedule() {
    //
  }

  std::array<char, STACK_SIZE> ucontext_t main;
  std::shared_ptr<Coroutine> cur_co = nullptr;

  boost::intrusive::list<std::shared_ptr<Coroutine>> CoListType;
  CoListType cos;
};

struct Coroutine : public boost::intrusive::list_base_hook<>,
                   public std::enable_shared_from_this<Coroutine> {
  using Func = std::function<void(Schedule &, void *ud)>;

  enum class Status {
    DEAD = 0,
    READY,
    RUNNING,
    SUSPEND,
  };

  Coroutine(Schedule &sched, Func func, void *ud) : sched(sched), func(std::move(func)), ud(ud) {}

  static std::shared_ptr<Coroutine> make(Schedule &sched, coroutine_func func, void *ud) {
    auto co = std::make_shared<Coroutine>(sched, func, ud);
    sched.cos.push_back(co);
    return co;
  }

  // static MainFunc(Schedule& sched ) {

  // }

  void resume() {
    // assert(S->running == -1);
    // assert(id >=0 && id < S->cap);
    switch (status) {
      case Status::READY:
        getcontext(*ctx);
        // NOTE: important!
        ctx.uc_stack.ss_sp = sched.stack;
        ctx.uc_stack.ss_size = STACK_SIZE;
        ctx.uc_link = &sched.main;

        sched.cur_co = shared_from_this();
        status = Status::RUNNING;

        uintptr_t ptr = reinterpret_cast<uintptr_t>(S);
        makecontext(
            &ctx,
            [this]() {
              this->sched.cur_co->func(this->sched, this->ud);
              this->sched.cur_co = nullptr;
            },
            0);

        break;
      case Status::SUSPEND:
        break;
      default:
        break;
    }
  }

  // TODO(curoky): why need this
  ~Coroutine() { free(stack); }

  Func func;
  void *ud;
  ucontext_t ctx;
  Schedule &sched;
  size_t cap = 0;
  size_t size = 0;
  Status status = Status::READY;
  char *stack = nullptr;
};

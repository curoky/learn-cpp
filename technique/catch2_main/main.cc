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

#include <catch2/catch_session.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>
#include <catch2/internal/catch_config_wchar.hpp>
#include <catch2/internal/catch_leak_detector.hpp>
#include <catch2/internal/catch_platform.hpp>
#include <folly/Singleton.h>
#include <folly/init/Init.h>
#include <folly/init/Phase.h>
// #include <folly/logging/Init.h>
#include <folly/synchronization/HazptrThreadPoolExecutor.h>
#include <gflags/gflags.h>

// Just for vscode test plugin
DEFINE_string(catch2, "Catch v2.12.2", "Catch v2.12.2");

namespace Catch {
CATCH_INTERNAL_START_WARNINGS_SUPPRESSION
CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS
LeakDetector leakDetector;
CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION
}  // namespace Catch

int main(int argc, char* argv[]) {
  // We want to force the linker not to discard the global variable
  // and its constructor, as it (optionally) registers leak detector
  (void)&Catch::leakDetector;
  // google::AllowCommandLineReparsing();

  // folly::init(&argc, &argv, false);
  // copy from folly init
  // google::InstallFailureSignalHandler();
  folly::set_process_phases();
  // folly::initLoggingOrDie(true);

  folly::SingletonVault::singleton()->registrationComplete();
  folly::enable_hazptr_thread_pool_executor();

  // google::ParseCommandLineFlags(&argc, &argv, false);
  google::InitGoogleLogging(argv[0]);
  return Catch::Session().run(argc, argv);
}

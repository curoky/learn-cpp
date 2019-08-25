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

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;

class CastAlert : public MatchFinder::MatchCallback {
 public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const CStyleCastExpr *CE = Result.Nodes.getNodeAs<clang::CStyleCastExpr>("cast")) {
      // If it comes from a macro expansion in the SystemHeaders, forget
      // about it. This handles the case of `NULL`.
      auto &SourceManager = *Result.SourceManager;
      if (SourceManager.isInSystemMacro(CE->getLParenLoc())) return;

      // Report it as an error.
      auto &DiagEngine = SourceManager.getDiagnostics();
      auto DiagID = DiagEngine.getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Error,
                                                                   "explicit cast detected");
      // Add a removal hint.
      DiagEngine.Report(CE->getBeginLoc(), DiagID)
          << FixItHint::CreateRemoval({CE->getBeginLoc(), CE->getEndLoc()});
    }
  }
};

static llvm::cl::OptionCategory CastMatcherCategory("cast-matcher options");
static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static llvm::cl::extrahelp MoreHelp(
    "\nThis tool helps the detection of explicit"
    "C-style casts.");

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, CastMatcherCategory);
  CastAlert Alert;
  ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

  MatchFinder Finder;

  // Match all explicit casts in the main file (exclude system headers).
  Finder.addMatcher(cStyleCastExpr(unless(isExpansionInSystemHeader())).bind("cast"), &Alert);

  return Tool.run(newFrontendActionFactory(&Finder).get());
}

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

#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Basic/Diagnostic.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using json = nlohmann::json;

json global_data;
json &class_data = global_data["class"];
json &member_data = global_data["member"];

class ClassMatcherCallback : public MatchFinder::MatchCallback {
 public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const RecordDecl *CE = Result.Nodes.getNodeAs<clang::RecordDecl>("class")) {
      auto &SourceManager = *Result.SourceManager;
      json local_data;

      std::string ns;
      llvm::raw_string_ostream rso(ns);
      CE->printNestedNameSpecifier(rso);
      local_data["filepath"] = CE->getBeginLoc().printToString(SourceManager);
      local_data["fullname"] = ns + CE->getNameAsString();

      json members;
      for (FieldDecl *fdec : CE->fields()) {
        json field_data;
        field_data["type"] = fdec->getType().getAsString();
        field_data["name"] = fdec->getNameAsString();
        members.push_back(field_data);
      }

      local_data["members"] = members;
      class_data.push_back(local_data);
    }
  }
};

class MemberCallback : public MatchFinder::MatchCallback {
 public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const MemberExpr *CE = Result.Nodes.getNodeAs<clang::MemberExpr>("member")) {
      auto &SourceManager = *Result.SourceManager;
      json local_data;
      local_data["filepath"] = CE->getBeginLoc().printToString(SourceManager);
      local_data["type"] = CE->getMemberDecl()->getType().getAsString();
      local_data["name"] = CE->getMemberDecl()->getNameAsString();
      local_data["base"] = CE->getBase()->getType().getAsString();

      member_data.push_back(local_data);
      //          llvm::outs()
      //      << "Base: " << CE->getBase()->getType().getAsString()
      //      << " member[ type: " < < < <
      //  ", value: " < < < < "\n";
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
  ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

  MatchFinder Finder;

  // Match all explicit casts in the main file (exclude system headers).
  ClassMatcherCallback class_matcher_callback;
  MemberCallback member_callback;
  Finder.addMatcher(cxxRecordDecl(hasName("xxx")).bind("class"), &class_matcher_callback);

  Finder.addMatcher(
      memberExpr(hasObjectExpression(hasType(cxxRecordDecl(hasName("NN"))))).bind("member"),
      &member_callback);

  int code = Tool.run(newFrontendActionFactory(&Finder).get());
  // llvm::outs() << global_data.dump(2) << "\n";

  std::ofstream myfile;
  myfile.open("output.json");
  myfile << global_data.dump(2);
  myfile.close();

  return code;
}

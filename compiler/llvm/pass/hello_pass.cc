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

#include <llvm/IR/Function.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

using namespace llvm;

namespace {
// Helper method for converting the name of a LLVM type to a string
static std::string LLVMTypeAsString(const Type *T) {
  std::string TypeName;
  raw_string_ostream N(TypeName);
  T->print(N);
  return N.str();
}
struct Hello : public FunctionPass {
  static char ID;
  Hello() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    errs() << "Hello: ";
    errs().write_escaped(F.getName()) << '\n';
    return false;
  }
};  // end of struct Hello

struct HelloModuel : public ModulePass {
  static char ID;
  HelloModuel() : ModulePass(ID) {}

  bool runOnModule(Module &M) override {
    // for (Module::const_global_iterator GI = M.global_begin(), GE = M.global_end(); GI != GE;
    // ++GI) {
    //   errs() << "Found global named: " << GI->getName()
    //          << "\tType: " << LLVMTypeAsString(GI->getType()) << "!\n";
    // }
    errs() << "In a Module: " << M.getName() << '\n';

    // for (auto &item : M.getGlobalList()) {
    //   // item.getName();
    //   errs().write_escaped(item.getName()) << '\n';
    // }
    for (auto &F : M) {
      for (auto &B : F) {
        errs() << "In a Module called : " << B.getName() << '\n';
        // for (auto &I : B) {
        // errs() << I.getOpcodeName() << "\n";
        // }
      }
    }
    return false;
  }
};

}  // end of anonymous namespace

char Hello::ID = 0;
char HelloModuel::ID = 0;

static RegisterPass<Hello> X("hello", "Hello World Pass", false /* Only looks at CFG */,
                             false /* Analysis Pass */);
static RegisterPass<HelloModuel> XX("hellomodule", "Hello World Pass2",
                                    false /* Only looks at CFG */, false /* Analysis Pass */);

static RegisterStandardPasses Y(PassManagerBuilder::EP_EarlyAsPossible,
                                [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM) {
                                  PM.add(new Hello());
                                });

static RegisterStandardPasses YY(PassManagerBuilder::EP_EarlyAsPossible,
                                 [](const PassManagerBuilder &Builder,
                                    legacy::PassManagerBase &PM) { PM.add(new HelloModuel()); });

#ifndef REPLACEIRVAR_H
#define REPLACEIRVAR_H

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Module.h"
#include <map>
#include <string>

class ReplaceIRVar {
private:
  /// NewName is used to set new name to the IR variable
  std::string NewName;
  /// HashMap is used to store mapping between IR Variable between and Source
  /// Variable
  std::map<std::string, std::string> HashMap;
  void init(llvm::Function &F);
  void init(llvm::BasicBlock &BB);
  void init(llvm::Module &M);
  void format(std::string First, std::string Second);
  void insert(std::string);

public:
  ReplaceIRVar();
  void run(llvm::Function &F);
  void run(llvm::BasicBlock &BB);
  void run(llvm::Module &M);
};
#endif
#ifndef CFGUTILS_H
#define CFGUTILS_H

#include "vector"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"

namespace spatial {

void InstNamer(llvm::Function &F);
bool SkipFunction(llvm::Function &F);
std::vector<llvm::Instruction *> GetPred(llvm::Instruction *);
std::vector<llvm::Instruction *> GetSucc(llvm::Instruction *);
int getPointerOperandIndex(llvm::Instruction *);

} // namespace spatial
#endif

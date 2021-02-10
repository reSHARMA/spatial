#include "Worklist/Worklist.h"

namespace spatial {

Worklist::Worklist(llvm::Instruction *Inst) { this->push(Inst); }

Worklist::Worklist(llvm::Function *Func) {
  for (llvm::BasicBlock &BB : *Func) {
    this->push(&BB);
  }
}

Worklist::Worklist(llvm::BasicBlock *BB) {
  for (llvm::Instruction &Inst : *BB) {
    this->push(&Inst);
  }
}

Worklist::Worklist(llvm::Module *M) {
  for (llvm::Function &F : M->functions()) {
    this->push(&F);
  }
}

llvm::Instruction *Worklist::pop() {
  llvm::Instruction *Inst = this->Queue.front();
  this->Queue.pop();
  return Inst;
}

void Worklist::push(llvm::Instruction *Inst) { this->Queue.push(Inst); }

void Worklist::push(llvm::BasicBlock *BB) {
  for (llvm::Instruction &Inst : *BB) {
    this->push(&Inst);
  }
}

void Worklist::push(llvm::Function *Func) {
  for (llvm::BasicBlock &BB : *Func) {
    this->push(&BB);
  }
}

int Worklist::size() { return this->Queue.size(); }

bool Worklist::empty() { return (this->size() == 0); }

} // namespace spatial

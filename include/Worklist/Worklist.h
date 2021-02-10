#include "queue"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Module.h"

namespace spatial {

class Worklist {
private:
  std::queue<llvm::Instruction *> Queue;

public:
  Worklist(llvm::Instruction *);
  Worklist(llvm::BasicBlock *);
  Worklist(llvm::Function *);
  Worklist(llvm::Module *);
  llvm::Instruction *pop();
  void push(llvm::Instruction *);
  void push(llvm::BasicBlock *);
  void push(llvm::Function *);
  int size();
  bool empty();
};

} // namespace spatial

#include "Benchmark/Benchmark.h"
#include "Benchmark/PTABenchmark.h"
#include "set"
#include "string"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

namespace spatial {

std::ostream &operator<<(std::ostream &OS, const PTABenchmarkRunner &B) {
  for (auto R : B.Result) {
    OS << R.second << "\n";
  }
}

void PTABenchmarkRunner::evaluateUtil(llvm::CallInst *Inst, int A, int B,
                                   int Result) {
  std::string Status, Expected, Got;
  llvm::StringRef FunctionName = Inst->getCalledFunction()->getName();
  if (FunctionName.contains("MAY"))
    Expected = "may";
  if (FunctionName.contains("MUST"))
    Expected = "must";
  if (FunctionName.contains("NO"))
    Expected = "no";
  if (A == 0 || B == 0 || 2 * A == Result)
    Got = "no";
  else if (A == Result)
    Got = "must";
  else
    Got = "may";
  if (Expected == Got || (Expected == "may" && Got == "must"))
    Status = "Pass";
  else
    Status = "Fail";
  this->Result[Inst] =
      "[" + Status + "] Expected: " + Expected + " Got: " + Got;
}

std::vector<llvm::Value *> PTABenchmarkRunner::extract(llvm::Instruction *Inst) {
  std::vector<llvm::Value *> Tokens;
  if (llvm::CallInst *CI = llvm::dyn_cast<llvm::CallInst>(Inst)) {
    llvm::Function *CalledFunction = CI->getCalledFunction();
    if (CalledFunction && CalledFunction->getName().contains(this->Key)) {
      for (llvm::Value *CallArg : CI->args()) {
        if (llvm::BitCastInst *BI =
                llvm::dyn_cast<llvm::BitCastInst>(CallArg)) {
          Tokens.push_back(BI->getOperand(0));
        } else if (llvm::BitCastOperator *BN =
                       llvm::dyn_cast<llvm::BitCastOperator>(CallArg)) {
          Tokens.push_back(BN->getOperand(0));
        } else {
          Tokens.push_back(CallArg);
        }
      }
    }
  }
  return Tokens;
}

} // namespace spatial

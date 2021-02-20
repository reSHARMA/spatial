#ifndef PTA_BENCHMARK_H
#define PTA_BENCHMARK_H

#include "Benchmark.h"
#include "set"
#include "string"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

namespace spatial {

class PTABenchmarkRunner : public BenchmarkRunner {
private:
  std::map<llvm::Instruction *, std::string> Result;
  void evaluateUtil(llvm::CallInst *, int, int, int);

public:
  PTABenchmarkRunner() : BenchmarkRunner("ALIAS"){};
  std::vector<llvm::Value *> extract(llvm::Instruction *Inst);
  friend std::ostream &operator<<(std::ostream &OS,
                                  const PTABenchmarkRunner &B);
  template <class Ty>
  void evaluate(llvm::Instruction *Inst, std::set<Ty *>, std::set<Ty *>);
};

template <class Ty>
void PTABenchmarkRunner::evaluate(llvm::Instruction *I, std::set<Ty *> A,
                                  std::set<Ty *> B) {
  llvm::CallInst *Inst = llvm::cast<llvm::CallInst>(I);
  std::set<Ty> Result;
  for (auto a : A)
    Result.insert(*a);
  for (auto b : B)
    Result.insert(*b);
  evaluateUtil(Inst, A.size(), B.size(), Result.size());
}
} // namespace spatial

#endif

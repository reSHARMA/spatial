#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "set"
#include "string"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

namespace spatial {

class BenchmarkRunner {
protected:
  std::string Key;

public:
  BenchmarkRunner(std::string Key) { this->Key = Key; }
  virtual std::vector<llvm::Value *> extract(llvm::Instruction *Inst) = 0;
};

} // namespace spatial

#endif

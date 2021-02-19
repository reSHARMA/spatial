#ifndef PTA_BENCHMARK_H_
#define PTA_BENCHMARK_H_
#include "Benchmark.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/DebugInfoMetadata.h"

namespace spatial {

enum Soundness {
  Sound,
  Unsound,
};
class PTABenchmarkRunner : public BenchmarkRunner {
  Soundness SoundOrUnsound;
  std::map<llvm::Instruction *, std::vector<std::string>> TCResult;
  std::map<llvm::BasicBlock *, std::vector<int>> PrecisionResult;

public:
  PTABenchmarkRunner() : BenchmarkRunner(){    
    SoundOrUnsound = Sound;
  }
  std::vector<llvm::Value *> extract(llvm::Instruction *Inst);
  friend std::ostream &operator<<(std::ostream &OS, const PTABenchmarkRunner &B);
  template <class Ty>
  void evaluate(llvm::Instruction *Inst, std::set<Ty *>, Ty *);
  spatial::Soundness CheckSoundness();
  void evaluatePrecision(llvm::Function &);
};

template <class Ty>
void PTABenchmarkRunner::evaluate(llvm::Instruction *I, std::set<Ty *> A,
                                     Ty *B) {
  llvm::CallInst *Inst = llvm::cast<llvm::CallInst>(I);
  std::string Status, Expected;
  llvm::StringRef FunctionName = Inst->getCalledFunction()->getName();

  llvm::MDNode *md = I->getMetadata("dbg");
  int lineno = llvm::cast<llvm::DILocation>(md)->getLine();

  // std::cout << lineno << "\n";

  if (FunctionName.contains("May"))
    Expected = "MayPointsTo";
  else if (FunctionName.contains("Must"))
    Expected = "MustPointsTo";
  else if (FunctionName.contains("DoesNot"))
    Expected = "DoesNotPointsTo";

  if (Expected == "MayPointsTo") {
    Status = "Fail";
    for (auto it = A.begin(); it != A.end(); it++) {
      if (*it == B) {
        Status = "Pass";
        break;
      }
    }
  } else if (Expected == "MustPointsTo") {
    if (A.size() > 1 || A.size() == 0) {
      Status = "Fail";
    } else {
      Status = "Pass";
      for (auto it = A.begin(); it != A.end(); it++) {
        if (*it != B) {
          Status = "Fail";
          break;
        }
      }
    }
  } else {
    Status = "Pass";
    for (auto it = A.begin(); it != A.end(); it++) {
      if (*it == B) {
        Status = "Fail";
        break;
      }
    }
  }
  TCResult[Inst].push_back(Status);
  TCResult[Inst].push_back(Expected);
  TCResult[Inst].push_back(std::to_string(lineno));
}

} // namespace spatial

#endif
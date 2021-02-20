#ifndef POINTS_TO_BENCHMARK_H_
#define POINTS_TO_BENCHMARK_H_
#include "Benchmark.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Metadata.h"

namespace spatial {

class PointsToBenchmarkRunner : public BenchmarkRunner {
  bool isSound;
  std::map<llvm::Instruction *, std::vector<std::string>> TCResult;
  std::map<llvm::BasicBlock *, std::vector<int>> PrecisionResult;

public:
  PointsToBenchmarkRunner() : BenchmarkRunner("PointsTo") { isSound = 1; }
  std::vector<llvm::Value *> extract(llvm::Instruction *Inst);
  friend std::ostream &operator<<(std::ostream &OS,
                                  const PointsToBenchmarkRunner &B);
  template <class Ty>
  void evaluate(llvm::Instruction *Inst, std::set<Ty *>, Ty *);
  bool CheckSoundness();
  void evaluatePrecision(llvm::Function &);
};

/**
 * @brief This Function evaluates the predicates defined in testcases for
 * pointer analysis.
 *
 * @param I CallInst which defines either one of the predicates :
 * MayPointsTo(x,y), MustPointsTo(x,y) or DoesNotPointsTo(x,y)
 * @param A Pointee Set of the first argument of the call to function.
 * @param B Pointee which we have to check if is present in the Pointee set of A
 * or not.
 */
template <class Ty>
void PointsToBenchmarkRunner::evaluate(llvm::Instruction *I, std::set<Ty *> A,
                                       Ty *B) {
  llvm::CallInst *Inst = llvm::cast<llvm::CallInst>(I);
  std::string Status, Expected;
  llvm::StringRef FunctionName = Inst->getCalledFunction()->getName();

  llvm::MDNode *MD = I->getMetadata("dbg");
  int LineNo = llvm::cast<llvm::DILocation>(MD)->getLine();

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
  TCResult[Inst].push_back(std::to_string(LineNo));
}

} // namespace spatial

#endif
#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "llvm/IR/Argument.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "set"
#include "string"
#include <iostream>
namespace spatial
{
    enum Soundness
    {
        Sound,
        Unsound,
    };
    class BenchmarkRunner
    {
    private:
        std::string Key;
        Soundness SoundOrUnsound;
        std::map<llvm::Instruction *, std::vector<std::string>> Result;
        std::map<llvm::BasicBlock *, std::vector<int>> PrecisionResult;
        // void evaluateUtil(llvm::CallInst* Inst, std::set<Ty*> A, std::set<Ty*> B);

    public:
        BenchmarkRunner()
        {
            Key = "PointsTo";
            SoundOrUnsound = Sound;
        }
        std::vector<llvm::Value *> extract(llvm::Instruction *Inst);
        friend std::ostream &operator<<(std::ostream &OS, const BenchmarkRunner &B);
        template <class Ty>
        void evaluate(llvm::Instruction *Inst, std::set<Ty *>, Ty *);
        spatial::Soundness CheckSoundness();
        void evaluatePrecision(llvm::Function &);
    };

    template <class Ty>
    void BenchmarkRunner::evaluate(llvm::Instruction *I, std::set<Ty *> A, Ty *B)
    {
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

        if (Expected == "MayPointsTo")
        {
            Status = "Fail";
            for (auto it = A.begin(); it != A.end(); it++)
            {
                if (*it == B)
                {
                    Status = "Pass";
                    break;
                }
            }
        }
        else if (Expected == "MustPointsTo")
        {
            if (A.size() > 1 || A.size() == 0)
            {
                Status = "Fail";
            }
            else
            {
                Status = "Pass";
                for (auto it = A.begin(); it != A.end(); it++)
                {
                    if (*it != B)
                    {
                        Status = "Fail";
                        break;
                    }
                }
            }
        }
        else
        {
            Status = "Pass";
            for (auto it = A.begin(); it != A.end(); it++)
            {
                if (*it == B)
                {
                    Status = "Fail";
                    break;
                }
            }
        }
        Result[Inst].push_back(Status);
        Result[Inst].push_back(Expected);
        Result[Inst].push_back(std::to_string(lineno));
    }
} // namespace spatial

#endif

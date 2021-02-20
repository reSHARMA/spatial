#include "Benchmark/PTABenchmark.h"
#include "Benchmark/PointsToBenchmark.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"
#include "set"
#include "string"
#include <iomanip>
#define CYANB "\033[1;46m"
#define REDT "\033[1;91m"
#define GREENT "\033[1;92m"
#define YELLOWT "\033[1;93m"
#define RST "\033[0;m"

namespace spatial {

std::string print_args(llvm::CallInst* ci){    
    std::string TCResult;
    int i=0;
	while(i<ci->getNumArgOperands())
	{
		std::string arg = llvm::dyn_cast<llvm::Instruction>(ci->getArgOperand(i))->getOperand(0)->getName().str();		
		TCResult += arg;			
		i++;
		if(i!=ci->getNumArgOperands()) TCResult += ", " ;		
	}
    return TCResult;
}

spatial::Soundness PointsToBenchmarkRunner::CheckSoundness(){
    for(auto i : TCResult){
        if(i.second[0] == "Fail" && (i.second[1] == "MayPointsTo")){
            SoundOrUnsound = Soundness::Unsound;
            break;
        }
        else{
            SoundOrUnsound = Soundness::Sound;
        }
    }
    return SoundOrUnsound;
}

std::ostream& operator<<(std::ostream& OS, const PointsToBenchmarkRunner& B) {
    int i = 1;
    std::string header = "*********************************************** BENCHMARK RESULTS *********************************************************",res;
    OS << "\n__________________________________________________________________________________________________________________________\n";
    OS << header + "\n";
    OS << "---------------------------------------------------------------------------------------------------------------------------\n\n";    
    for (auto R = B.TCResult.begin();R != B.TCResult.end();R++) {
        if(R == B.TCResult.begin()){
            OS << "\t\t=================================================================================\n";
        }
        llvm::CallInst* ci = llvm::dyn_cast<llvm::CallInst>((*R).first); 
        OS << std::setw(15) << "\t\t|  TestCase " << i << ":\t|\t" 
        << std::setw(10) << "Line:" << (*R).second[2] << "   " << (*R).second[1] <<"(" 
        << print_args(ci) << ")\t" << std::setw(5) << "|\t" ;
        res = (((*R).second[0] == "Pass") ? (GREENT + (*R).second[0] + RST ): (REDT + (*R).second[0] + RST)); 
        OS << res;
        OS <<  "\t|\n";        
        OS << "\t\t=================================================================================\n";
        i++;
    }
    OS << "\n---------------------------------------------------------------------------------\n";
    if(B.SoundOrUnsound == Soundness::Sound){
        OS << "\nSoundness Check : Analysis is \033[1;92mSound\033[0;m\n";
    }
    else{
        OS << "\nSoundness Check : Analysis is \033[1;91mUnsound\033[0;m\n";
    }
    OS << "\n---------------------------------------------------------------------------------\n";
    OS << "Precision Evaluation :\n\n";  
    OS << "\t\t=========================================================================================================\n";
    OS << "\t\t|\tProgram Point\t|\t" <<  "Total Pointers incorrect\t" << "|\tTotal Failed Predicates\t\t|\n";
    for(auto i : B.PrecisionResult){
        if(i == *(B.PrecisionResult.begin())){
            OS << "\t\t=========================================================================================================\n";
        }
        OS << "\t\t|\tOut [" << (i.first)->getName().str() << "]\t" << std::setw(1) << "|";        
        OS << std::setw(14) << "\t" << i.second[0] << "\t"<< std::setw(13) << "\t|\t" << std::setw(14) << i.second[1] << std::setw(13) << "\t|\n";        
        OS << "\t\t=========================================================================================================\n";
    }
    OS << "____________________________________________________________________________________________________________________________\n\n";
    return OS;
}

std::vector<llvm::Value*> PointsToBenchmarkRunner::extract(llvm::Instruction* Inst) {
    std::vector<llvm::Value*> Tokens;    
    if (llvm::CallInst* CI = llvm::dyn_cast<llvm::CallInst>(Inst)) {        
        llvm::Function* CalledFunction = CI->getCalledFunction();        
        if (CalledFunction && CalledFunction->getName().contains(this->Key)) {            
            for (llvm::Value* CallArg : CI->args()) {
                if(CallArg != *(CI->args().begin()))
                    Tokens.push_back(llvm::dyn_cast<llvm::Instruction>(CallArg)->getOperand(0));
                else
                    Tokens.push_back(CallArg);                
            }
        }
    }
    return Tokens;
}
void PointsToBenchmarkRunner::evaluatePrecision(llvm::Function& F){
    for(llvm::BasicBlock& BB : F){        
        std::map<llvm::Value*, bool> visited;
        PrecisionResult[&BB] = std::vector<int>(2,0);
        for(llvm::Instruction& I : BB){
            if(llvm::CallInst* ci = llvm::dyn_cast<llvm::CallInst>(&I)){
                if(ci->getCalledFunction()->getName().contains("DoesNotPointsTo")){
                    std::vector<std::string> res = TCResult[&I];
                    if(res[0] == "Fail"){
                        // Format -- Pointer Count for which it fails, Total predicates it fails;
                        llvm::Value* arg1 = llvm::dyn_cast<llvm::Instruction>(ci->getArgOperand(0))->getOperand(0);                    
                        if(!visited[arg1]){
                            PrecisionResult[&BB][0]++;    
                            visited[arg1] = true;
                        }                    
                        PrecisionResult[&BB][1]++;
                    }

                }
            }
        }
    }

}
}  // namespace spatial
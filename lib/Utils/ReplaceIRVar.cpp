#include "Utils/ReplaceIRVar.h"

/// Constructor of ReplaceIRVar class
ReplaceIRVar::ReplaceIRVar(){
	this->NewName = "\0";
	this->HashMap.clear();
}

void ReplaceIRVar::format(std::string First, std::string Second){
	this->NewName = "( " + First + " : " + Second + ")"; 
}

/// replace IR variable to Temporary Variable for the Function passed as parameter
void ReplaceIRVar::init(llvm::Function& F){
	for (auto &Arg : F.args()) {
	    if (!Arg.hasName()){
	    	Arg.setName("arg");
  		}
    }
    for (llvm::BasicBlock &BB : F) {
	    this->init(BB);
  	}
}
/// replace IR variable to Temporary Variable for the BasicBlock passed as parameter
void ReplaceIRVar::init(llvm::BasicBlock& BB){
	if (!BB.hasName()){
      BB.setName("bb");
    }
    for (llvm::Instruction& I : BB) {
      if (!I.hasName() && !I.getType()->isVoidTy()){
      	I.setName("i");
      }
    }
}
/// replace IR variable to Temporary Variable for the Module passed as parameter
void ReplaceIRVar::init(llvm::Module& M){
	for(llvm::Function& F : M){
		this->init(F);
	}
}

/// replace IR variable to Actual Variable for the Function passed as parameter
void ReplaceIRVar::runOnFunction(llvm::Function& F){
	this->init(F);
	for(llvm::BasicBlock& BB : F){
		this->runOnBasicBlock(BB);
	}
}

/// replace IR variable to Actual Variable for the Basic Block passed as parameter
void ReplaceIRVar::runOnBasicBlock(llvm::BasicBlock& BB){
	this->init(BB);
	for(llvm::Instruction& I : BB){
		if(const llvm::DbgDeclareInst *DbgDeclare = llvm::dyn_cast<llvm::DbgDeclareInst>(&I)){
			this->format(std::to_string(DbgDeclare->getVariable()->getLine()) , (DbgDeclare->getVariable()->getName()).str());
			if(llvm::Instruction *I = llvm::dyn_cast<llvm::Instruction>(DbgDeclare->getAddress())){
				llvm::StringRef strref(this->NewName);
				HashMap.insert(std::pair<std::string,std::string>(I->getName().str(),this->NewName));
			}
		}
	}
	for(llvm::Instruction& I : BB){
    	std::string Name = I.getName().str();
        if(HashMap.find(Name)!=HashMap.end()){
            I.setName(HashMap[Name]);
        }
    }
}

/// replace IR variable to Actual Variable for the Module passed as parameter
void ReplaceIRVar::runOnModule(llvm::Module& M){
	this->init(M);
	for(llvm::Function& F : M){
		this->runOnFunction(F);
	}
}
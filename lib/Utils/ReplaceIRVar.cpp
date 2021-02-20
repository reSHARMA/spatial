#include <iostream>
#include <map>
#include "Utils/ReplaceIRVar.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DebugInfoMetadata.h"

/// Constructor of ReplaceIRVar class
ReplaceIRVar::ReplaceIRVar(){
	this->NewName="\0";
	this->HashMap.clear();
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
			NewName = "( "+ std::to_string(DbgDeclare->getVariable()->getLine()) + " : " + (DbgDeclare->getVariable()->getName()).str() + " )";
			if(llvm::Instruction *I = llvm::dyn_cast<llvm::Instruction>(DbgDeclare->getAddress())){
				llvm::StringRef strref(NewName);
				HashMap.insert(std::pair<std::string,std::string>(I->getName().str(),NewName));
			}
		}
	}
	for(llvm::Instruction& I : BB){
    	std::string name = I.getName().str();
        if(HashMap.find(name)!=HashMap.end()){
            I.setName(HashMap[name]);
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
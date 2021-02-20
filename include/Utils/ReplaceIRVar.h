#ifndef REPLACEIRVAR_H
#define REPLACEIRVAR_H

#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Module.h"
#include <iostream>
#include <map>

class ReplaceIRVar{
private:
	std::string NewName;
	std::map<std::string,std::string> HashMap;
	void init(llvm::Function& F);
	void init(llvm::BasicBlock& F);
	void init(llvm::Module& F);
public:
	ReplaceIRVar();
	void runOnFunction(llvm::Function& F);
	void runOnBasicBlock(llvm::BasicBlock& BB);
	void runOnModule(llvm::Module& M);
};
#endif
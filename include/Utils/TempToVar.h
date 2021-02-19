#ifndef TEMPTOVAR_H
#define TEMPTOVAR_H

#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Module.h"
#include <iostream>
#include <map>

class TempToVar{
private:
	std::string new_name;
	std::map<std::string,std::string> hash_map;
public:
	TempToVar();
	void replace(llvm::Function& F);
	void replace(llvm::BasicBlock& BB);
	void replace(llvm::Module& M);
};
#endif
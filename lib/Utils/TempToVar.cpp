#include <iostream>
#include <map>
#include "Utils/TempToVar.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DebugInfoMetadata.h"

TempToVar::TempToVar(){
	this->new_name="\0";
	this->hash_map.clear();
}
void TempToVar::replace(llvm::Function& F){
	for(llvm::BasicBlock& BB : F){
		for(llvm::Instruction& I : BB){
			if(const llvm::DbgDeclareInst *DbgDeclare = llvm::dyn_cast<llvm::DbgDeclareInst>(&I)){
    			new_name = (DbgDeclare->getVariable()->getName()).str() + "_" + std::to_string(DbgDeclare->getVariable()->getLine());
    			if(llvm::Instruction *I = llvm::dyn_cast<llvm::Instruction>(DbgDeclare->getAddress())){
    				llvm::StringRef strref(new_name);
    				hash_map.insert(std::pair<std::string,std::string>(I->getName().str(),new_name));
    			}
			}
		}
	}
	for(llvm::BasicBlock &BB : F){
	    for(llvm::Instruction &I : BB){
	    	std::string name = I.getName().str();
	        if(hash_map.find(name)!=hash_map.end()){
	            I.setName(hash_map[name]);
	        }
	    }
	}
}
void TempToVar::replace(llvm::BasicBlock& BB){
	for(llvm::Instruction& I : BB){
		if(const llvm::DbgDeclareInst *DbgDeclare = llvm::dyn_cast<llvm::DbgDeclareInst>(&I)){
			new_name = (DbgDeclare->getVariable()->getName()).str() + "_" + std::to_string(DbgDeclare->getVariable()->getLine());
			if(llvm::Instruction *I = llvm::dyn_cast<llvm::Instruction>(DbgDeclare->getAddress())){
				llvm::StringRef strref(new_name);
				hash_map.insert(std::pair<std::string,std::string>(I->getName().str(),new_name));
			}
		}
	}
	for(llvm::Instruction &I : BB){
    	std::string name = I.getName().str();
        if(hash_map.find(name)!=hash_map.end()){
            I.setName(hash_map[name]);
        }
    }
}
void TempToVar::replace(llvm::Module& M){
	for(llvm::Function& F : M){
		for(llvm::BasicBlock& BB : F){
			for(llvm::Instruction& I : BB){
				if(const llvm::DbgDeclareInst *DbgDeclare = llvm::dyn_cast<llvm::DbgDeclareInst>(&I)){
	    			new_name = (DbgDeclare->getVariable()->getName()).str() + "_" + std::to_string(DbgDeclare->getVariable()->getLine());
	    			if(llvm::Instruction *I = llvm::dyn_cast<llvm::Instruction>(DbgDeclare->getAddress())){
	    				llvm::StringRef strref(new_name);
	    				hash_map.insert(std::pair<std::string,std::string>(I->getName().str(),new_name));
	    			}
				}
			}
		}
	}
	for(llvm::Function& F : M){
		for(llvm::BasicBlock& BB : F){
			for(llvm::Instruction& I : BB){
				std::string name = I.getName().str();
		        if(hash_map.find(name)!=hash_map.end()){
		            I.setName(hash_map[name]);
		        }
			}
		}
	}
}
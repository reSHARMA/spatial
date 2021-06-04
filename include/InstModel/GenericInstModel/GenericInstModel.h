#ifndef GENERICINSTMODEL_GENERICINSTMODEL_H
#define GENERICINSTMODEL_GENERICINSTMODEL_H

#include "InstInfo/InstInfo.h"
#include "InstModel/InstModel.h"
#include "Token/Token.h"
#include "vector"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Operator.h"

namespace spatial {

class GenericInstModel : public InstModel {
public:
  using InstModel::InstModel;

  ~GenericInstModel();
  std::vector<int> extractRedirections(llvm::Instruction *);
  InstInfo extractInstInfo(llvm::Instruction *);

  std::vector<Token *> extractToken(llvm::Instruction *);
  std::vector<Token *> extractToken(llvm::StoreInst *);
  std::vector<Token *> extractToken(llvm::LoadInst *);
  std::vector<Token *> extractToken(llvm::AllocaInst *);
  std::vector<Token *> extractToken(llvm::BitCastInst *);
  std::vector<Token *> extractToken(llvm::ReturnInst *);
  std::vector<Token *> extractToken(llvm::GetElementPtrInst *);
  std::vector<Token *> extractToken(llvm::GlobalVariable *);
  std::vector<Token *> extractToken(llvm::CallInst *);
  std::vector<Token *> extractToken(llvm::Argument *, llvm::Function *);
  std::vector<Token *> extractPHINodeToken(llvm::Instruction *);

  std::vector<int> extractRedirections(llvm::GlobalVariable *);
  template <typename GEP> Token *handleGEPUtil(GEP *, Token *);
};
} // namespace spatial

#endif

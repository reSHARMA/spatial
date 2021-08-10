#ifndef LFCPAINSTMODEL_LFCPAINSTMODEL_H
#define LFCPAINSTMODEL_LFCPAINSTMODEL_H

#include "spatial/InstInfo/InstInfo.h"
#include "spatial/InstModel/InstModel.h"
#include "spatial/Token/Token.h"
#include "vector"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Operator.h"

namespace spatial {

class LFCPAInstModel : public InstModel {
  std::map<llvm::Instruction*, spatial::InstInfo*> InstInfoMap;
public:
 using InstModel::InstModel;
 
  ~LFCPAInstModel();
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
  std::vector<Token *> extractToken(llvm::CmpInst *);
  std::vector<Token *> extractToken(llvm::Argument *, llvm::Function *);

  std::vector<int> extractRedirections(llvm::GlobalVariable *);
  template <typename GEP> Token *handleGEPUtil(GEP *, Token *);
  bool isInstSkip (llvm::Instruction *);
  template <typename GOP> bool isStructFieldPointerTy(GOP *);
  Token* extractDummy(std::string);
};
} // namespace spatial

#endif

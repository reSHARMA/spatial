#ifndef TOKENWRAPPER_H
#define TOKENWRAPPER_H

#include "Token.h"
#include "set"
#include "string"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

namespace spatial {

class TokenWrapper {
private:
  std::map<std::string, Token *> TokenBank;
  bool isCached(Token *);
  bool insert(Token *);

public:
  Token *getToken(llvm::Value *);
  Token *getToken(llvm::Argument *);
  Token *getToken(llvm::Type *);
  Token *getToken(llvm::Instruction *);
  Token *getToken(Token *);
  Token *getToken(std::string, llvm::Function *);
  Token *getToken(llvm::GEPOperator *, llvm::Function *);

  Token *getTokenWithoutIndex(Token *);

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

  template <typename Ty> std::pair<int, int> extractStatementType(Ty *);

  template <typename GEP> Token *handleGEPUtil(GEP *, Token *);

  ~TokenWrapper();
};

} // namespace spatial

#endif

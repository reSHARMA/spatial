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
  std::vector<Token *> extractPHINodeToken(llvm::Instruction *);

  template <typename Ty> std::pair<int, int> extractStatementType(Ty *);
  
  std::vector<int> extractPHINodeStatementType(llvm::Instruction *);
  template <typename GEP> Token *handleGEPUtil(GEP *, Token *);

  ~TokenWrapper();
};

} // namespace spatial

namespace spatial{
  /// extractStatementType - Returns the relative level of redirection based of
  /// LHS and RHS on the statement
	template <typename Ty>
  std::pair<int, int> TokenWrapper::extractStatementType(Ty *Inst) {
    if (llvm::isa<llvm::AllocaInst>(Inst) ||
        llvm::isa<llvm::GlobalVariable>(Inst) ||
        llvm::isa<llvm::GetElementPtrInst>(Inst))
      return {1, 0};
    if (llvm::isa<llvm::StoreInst>(Inst))
      return {2, 1};
    if (llvm::isa<llvm::LoadInst>(Inst))
      return {1, 2};
    return {1, 1};
  }
}

#endif

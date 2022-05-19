#ifndef TOKEN_H
#define TOKEN_H

#include "string"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/BitVector.h"

namespace spatial {

enum opTokenTy {isArray, isAlloca, isOpBitcast, isPhiGEPOpd, isIcmpGEPOpd, isOneGEPIndx, isFunPtr, isFunArg, isRetGEP};

class Token {
private:
  llvm::Value *Val;
  llvm::Type *Ty;
  llvm::Argument *Arg;
  // 0 is Value
  // 1 is Type
  // 2 is Argument
  // 3 is Dummy
  std::string Index;
  unsigned int Kind;
  llvm::Function *Func;
  std::string name;
  bool IsGlobal;

  void set(llvm::Value *Val, unsigned int Kind, std::string Index,
           llvm::Function *Func, bool Global = false);
  void set(llvm::Type *Ty, unsigned int Kind, std::string Index);
  void set(llvm::Argument *Arg, unsigned int Kind, std::string Index,
           llvm::Function *Func);
  void set(std::string S, unsigned int Kind, std::string Index,
           llvm::Function *Func);
  llvm::BitVector opTokenTy;
  unsigned int TyLength;


public:
  void setIndex(llvm::GetElementPtrInst *GEPInst);
  void setIndex(llvm::GEPOperator *GEPOp);
  void setIndex(Token*, std::string);
  void setIndex(Token*);
  void resetIndex();
  void resetIndexToZero();
  void resetIndexToZero(std::string);
  std::string getIndex(llvm::GEPOperator *GEPOp);
  
  Token(llvm::Value *Val, std::string Index = "");
  Token(llvm::GEPOperator *GOP, llvm::Function *Func, std::string Index = "");
  Token(llvm::Argument *Arg, std::string Index = "");
  Token(llvm::Type *Ty, std::string Index = "");
  Token(std::string S, llvm::Function *Func, std::string Index = "");
  Token(Token *A);
  Token();

  llvm::Value *getValue() const;
  llvm::StringRef getName() const;
  std::string getMemTypeName() const;
  std::string getFunctionName() const;
  std::string getFieldIndex() const;
  
  friend std::ostream &operator<<(std::ostream &OS, const Token &A);

  bool isMem() const;
  bool isArg() const;
  bool isField() const;
  bool isGlobalVar() const;
  bool isAllocaOrArgOrGlobal() const;
  bool sameFunc(llvm::Function *Func) const;
  bool isBasePointerType() const;
  bool isValPointerType() const;
  std::string getHash() const;
  bool isPointerType() const;

  bool operator<(const Token &TheToken) const;
  bool operator==(const Token &TheToken) const;
  void operator=(const Token &TheToken);
  void setIsGlobal();
  void setIsArray();
  bool getIsArray();
  void setIsAlloca(); 
  bool getIsAlloca();
  void setIsOpBitcast();
  bool getIsOpBitcast();  
  void setIsPhiGEPOpd();
  bool getIsPhiGEPOpd();
  void setIsIcmpGEPOpd();
  bool getIsIcmpGEPOpd();
  void setIsOneGEPIndx();
  bool getIsOneGEPIndx();
  void setIsFunPtr();
  bool getIsFunPtr();
  void setIsFunArg();
  bool getIsFunArg();
  void setIsRetGEP();
  bool getIsRetGEP();

  template <typename GOP> bool isGEPOperandArrayTy(GOP *, int);
  template <typename GEP> std::vector<int> getGEPArrayIndex(GEP*);

  bool isNullToken();
  void setNullToken();
  llvm::Type* getTy();
  void setTy(llvm::Type*);
  void setFunction(llvm::Function*);
  llvm::Function* getFunction();
};
} // namespace spatial

#endif

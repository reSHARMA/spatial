#include "Token/AliasToken.h"

namespace spatial {

/// isCached - Returns true if Alias \p A is already present in cache
bool AliasTokens::isCached(Alias *A) {
  std::string hash = A->getHash();
  return (AliasBank.find(hash) != AliasBank.end());
}

/// insert - Returns true after inserting the Alias \p A in cache, retuns false
/// if it is already present
bool AliasTokens::insert(Alias *A) {
  if (isCached(A)) {
    delete A;
    return false;
  } else {
    std::string hash = A->getHash();
    AliasBank[hash] = A;
    return true;
  }
}

/// getAliasToken - Returns Alias object for Value \p Val, returns the object
/// from cache if it already exists
Alias *AliasTokens::getAliasToken(llvm::Value *Val) {
  Alias *A = new Alias(Val);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return AliasBank[hash];
}

/// getAliasToken - Returns Alias object for Value \p GEPOperator and Function
/// \p Func, returns the object from cache if it already exists
Alias *AliasTokens::getAliasToken(llvm::GEPOperator *GOP,
                                  llvm::Function *Func) {
  Alias *A = new Alias(GOP, Func);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return AliasBank[hash];
}

/// getAliasToken - Returns Alias object for Argument \p Arg, returns the object
/// from cache if it already exists
Alias *AliasTokens::getAliasToken(llvm::Argument *Arg) {
  Alias *A = new Alias(Arg);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return AliasBank[hash];
}

/// getAliasToken - Returns Alias object for Type \p Ty, returns the object from
/// cache if it already exists
Alias *AliasTokens::getAliasToken(llvm::Type *Ty) {
  Alias *A = new Alias(Ty);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return AliasBank[hash];
}

/// getAliasToken - Returns Alias object for Instruction \p Inst, returns the
/// object from cache if it already exists
Alias *AliasTokens::getAliasToken(llvm::Instruction *Inst) {
  Alias *A = new Alias(Inst);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return AliasBank[hash];
}

/// getAliasToken - Returns Alias object from another alias object \p A, returns
/// the object from cache if it already exists
Alias *AliasTokens::getAliasToken(Alias *A) {
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return AliasBank[hash];
}

/// getAliasToken - Returns Alias object from another alias object \p A, returns
/// the object from cache if it already exists
Alias *AliasTokens::getAliasTokenWithoutIndex(Alias *A) {
  Alias *Tok = new Alias(A);
  Tok->resetIndex();
  std::string hash = Tok->getHash();
  if (insert(Tok))
    return Tok;
  return AliasBank[hash];
}

/// getAliasToken - Returns Alias object for String \p S, returns the object
/// from cache if it already exists.
///
/// \S is the name of dummy alias
/// \Func is the function associated with the alias object, pass nullptr if the
/// dummy oject at a global scope
Alias *AliasTokens::getAliasToken(std::string S, llvm::Function *Func) {
  Alias *A = new Alias(S, Func);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return AliasBank[hash];
}

/// extractAliasToken - Returns a vector of alias objects derived from
/// Instruction \Inst operands
std::vector<Alias *> AliasTokens::extractAliasToken(llvm::Instruction *Inst) {
  if (llvm::StoreInst *SI = llvm::dyn_cast<llvm::StoreInst>(Inst)) {
    return extractAliasToken(SI);
  } else if (llvm::LoadInst *LI = llvm::dyn_cast<llvm::LoadInst>(Inst)) {
    return extractAliasToken(LI);
  } else if (llvm::AllocaInst *AI = llvm::dyn_cast<llvm::AllocaInst>(Inst)) {
    return extractAliasToken(AI);
  } else if (llvm::BitCastInst *BI = llvm::dyn_cast<llvm::BitCastInst>(Inst)) {
    return extractAliasToken(BI);
  } else if (llvm::ReturnInst *RI = llvm::dyn_cast<llvm::ReturnInst>(Inst)) {
    return extractAliasToken(RI);
  } else if (llvm::GetElementPtrInst *GEP =
                 llvm::dyn_cast<llvm::GetElementPtrInst>(Inst)) {
    return extractAliasToken(GEP);
  } else if (llvm::CallInst *CI = llvm::dyn_cast<llvm::CallInst>(Inst)) {
    return extractAliasToken(CI);
  } else {
    // Direct support to some instructions may not be useful example
    // CallInst, as it is more useful to generate alias object for call
    // arguments on the fly
    llvm::errs() << "[TODO]: Unsupported Instruction " << *Inst << "\n";
  }
  return {};
}

/// extractAliasToken - Returns a vector of alias objects derived from
/// Global variable \Global operands
std::vector<Alias *>
AliasTokens::extractAliasToken(llvm::GlobalVariable *Global) {
  std::vector<Alias *> AliasVec;
  if (Global->hasName() && !Global->getName().startswith("_")) {
    AliasVec.push_back(this->getAliasToken(Global));
    AliasVec.push_back(
        this->getAliasToken(Global->getName().str() + "-orig", nullptr));
  }
  return AliasVec;
}

/// extractAliasToken - Returns a vector of alias objects for StoreInst \Inst
/// operands.
std::vector<Alias *> AliasTokens::extractAliasToken(llvm::StoreInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example store op1 op2
  std::vector<Alias *> AliasVec;
  AliasVec.push_back(this->getAliasToken(Inst->getPointerOperand()));
  llvm::Value *ValOp = Inst->getValueOperand();
  if (!llvm::isa<llvm::ConstantInt>(ValOp))
    AliasVec.push_back(this->getAliasToken(ValOp));
  return AliasVec;
}

/// extractAliasToken - Returns a vector of alias objects for StoreInst \Inst
/// operands.
std::vector<Alias *> AliasTokens::extractAliasToken(llvm::LoadInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = load op1
  std::vector<Alias *> AliasVec;
  AliasVec.push_back(this->getAliasToken(Inst));
  AliasVec.push_back(this->getAliasToken(Inst->getPointerOperand()));
  return AliasVec;
}

/// extractAliasToken - Returns a vector of alias objects for AllocaInst \Inst
/// operands.
std::vector<Alias *> AliasTokens::extractAliasToken(llvm::AllocaInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = alloca op1
  std::vector<Alias *> AliasVec;
  Alias *Alloca = this->getAliasToken(Inst);
  AliasVec.push_back(Alloca);
  AliasVec.push_back(this->getAliasToken(Alloca->getName().str() + "-orig",
                                         Inst->getParent()->getParent()));
  return AliasVec;
}

/// extractAliasToken - Returns a vector of alias objects for ReturnInst \Inst
/// operands.
std::vector<Alias *> AliasTokens::extractAliasToken(llvm::ReturnInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example return op1
  std::vector<Alias *> AliasVec;
  llvm::Value *RetVal = Inst->getReturnValue();
  if (RetVal && !llvm::isa<llvm::ConstantInt>(RetVal))
    AliasVec.push_back(this->getAliasToken(RetVal));
  return AliasVec;
}

/// extractAliasToken - Returns a vector of alias objects for BitCastInst \Inst
/// operands.
std::vector<Alias *> AliasTokens::extractAliasToken(llvm::BitCastInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = bitcast op1
  std::vector<Alias *> AliasVec;
  AliasVec.push_back(this->getAliasToken(Inst));
  if (llvm::CallInst *CI =
          llvm::dyn_cast<llvm::CallInst>(Inst->getOperand(0))) {
    if (CI->getCalledFunction()->getName().startswith("_Zn") ||
        CI->getCalledFunction()->getName().startswith("_zn"))
      AliasVec.push_back(this->getAliasToken(Inst->getDestTy()));
  } else if (llvm::BitCastInst *BI =
                 llvm::dyn_cast<llvm::BitCastInst>(Inst->getOperand(0))) {
    AliasVec.push_back(this->getAliasToken(BI->getDestTy()));
  }
  if (AliasVec.size() == 1) {
    AliasVec.push_back(this->getAliasToken(Inst->getOperand(0)));
  }
  return AliasVec;
}

/// extractAliasToken - Returns a vector of alias objects for GetElementPointer
/// \Inst operands.
std::vector<Alias *>
AliasTokens::extractAliasToken(llvm::GetElementPtrInst *Inst) {
  // Only provides partial support and returns {op1, op2} for op1 = GEP op2
  // idx1 idx2
  std::vector<Alias *> AliasVec;
  llvm::Function *Func = Inst->getParent()->getParent();
  AliasVec.push_back(this->getAliasToken(Inst));
  AliasVec.push_back(
      this->getAliasToken(llvm::cast<llvm::GEPOperator>(Inst), Func));
  return AliasVec;
}

/// extractAliasToken - Returns a vector of alias objects for Argument \Arg of
/// Function \Func
std::vector<Alias *> AliasTokens::extractAliasToken(llvm::Argument *Arg,
                                                    llvm::Function *Func) {
  std::vector<Alias *> AliasVec;
  Alias *ArgAlias = this->getAliasToken(Arg);
  AliasVec.push_back(ArgAlias);
  AliasVec.push_back(this->getAliasToken(Arg->getName().str() + "-orig", Func));
  return AliasVec;
}

/// extractAliasToken - Returns the alias object for variable storing the
/// return value from the function call
std::vector<Alias *> AliasTokens::extractAliasToken(llvm::CallInst *CI) {
  std::vector<Alias *> AliasVec;
  if (!CI->doesNotReturn()) {
    AliasVec.push_back(this->getAliasToken(CI));
  }
  return AliasVec;
}

/// extractStatementType - Returns the relative level of redirection based of
/// LHS and RHS on the statement
template <typename Ty>
std::pair<int, int> AliasTokens::extractStatementType(Ty *Inst) {
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
template std::pair<int, int>
AliasTokens::extractStatementType<llvm::Instruction>(llvm::Instruction *);
template std::pair<int, int>
AliasTokens::extractStatementType<llvm::GlobalVariable>(llvm::GlobalVariable *);

/// handleGEPUtil - Returns the extended field value for a GEP
template <typename GEP> Alias *AliasTokens::handleGEPUtil(GEP *G, Alias *Ptr) {
  if (!Ptr)
    return Ptr;
  Alias *FieldVal = new Alias(Ptr);
  FieldVal->setIndex(G);
  FieldVal = this->getAliasToken(FieldVal);
  return FieldVal;
}
template Alias *
AliasTokens::handleGEPUtil<llvm::GetElementPtrInst>(llvm::GetElementPtrInst *G,
                                                    Alias *Ptr);
template Alias *
AliasTokens::handleGEPUtil<llvm::GEPOperator>(llvm::GEPOperator *G, Alias *Ptr);

AliasTokens::~AliasTokens() {
  for (auto X : AliasBank) {
    delete X.second;
  }
}

} // namespace spatial

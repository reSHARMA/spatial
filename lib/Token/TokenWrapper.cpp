#include "Token/TokenWrapper.h"

namespace spatial {

/// isCached - Returns true if Token \p A is already present in cache
bool TokenWrapper::isCached(Token *A) {
  std::string hash = A->getHash();
  return (TokenBank.find(hash) != TokenBank.end());
}

/// insert - Returns true after inserting the Token \p A in cache, retuns false
/// if it is already present
bool TokenWrapper::insert(Token *A) {
  if (isCached(A)) {
    delete A;
    return false;
  } else {
    std::string hash = A->getHash();
    TokenBank[hash] = A;
    return true;
  }
}

/// getToken - Returns Token object for Value \p Val, returns the object
/// from cache if it already exists
Token *TokenWrapper::getToken(llvm::Value *Val) {
  Token *A = new Token(Val);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return TokenBank[hash];
}

/// getToken - Returns Token object for Value \p GEPOperator and Function
/// \p Func, returns the object from cache if it already exists
Token *TokenWrapper::getToken(llvm::GEPOperator *GOP, llvm::Function *Func) {
  Token *A = new Token(GOP, Func);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return TokenBank[hash];
}

/// getToken - Returns Token object for Argument \p Arg, returns the object
/// from cache if it already exists
Token *TokenWrapper::getToken(llvm::Argument *Arg) {
  Token *A = new Token(Arg);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return TokenBank[hash];
}

/// getToken - Returns Token object for Type \p Ty, returns the object from
/// cache if it already exists
Token *TokenWrapper::getToken(llvm::Type *Ty) {
  Token *A = new Token(Ty);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return TokenBank[hash];
}

/// getToken - Returns Token object for Instruction \p Inst, returns the
/// object from cache if it already exists
Token *TokenWrapper::getToken(llvm::Instruction *Inst) {
  Token *A = new Token(Inst);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return TokenBank[hash];
}

/// getToken - Returns Token object from another alias object \p A, returns
/// the object from cache if it already exists
Token *TokenWrapper::getToken(Token *A) {
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return TokenBank[hash];
}

/// getToken - Returns Token object from another alias object \p A, returns
/// the object from cache if it already exists
Token *TokenWrapper::getTokenWithoutIndex(Token *A) {
  Token *Tok = new Token(A);
  Tok->resetIndex();
  std::string hash = Tok->getHash();
  if (insert(Tok))
    return Tok;
  return TokenBank[hash];
}

/// getToken - Returns Token object for String \p S, returns the object
/// from cache if it already exists.
///
/// \S is the name of dummy alias
/// \Func is the function associated with the alias object, pass nullptr if the
/// dummy oject at a global scope
Token *TokenWrapper::getToken(std::string S, llvm::Function *Func) {
  Token *A = new Token(S, Func);
  std::string hash = A->getHash();
  if (insert(A))
    return A;
  return TokenBank[hash];
}

/// extractToken - Returns a vector of alias objects derived from
/// Instruction \Inst operands
std::vector<Token *> TokenWrapper::extractToken(llvm::Instruction *Inst) {
  if (llvm::StoreInst *SI = llvm::dyn_cast<llvm::StoreInst>(Inst)) {
    return extractToken(SI);
  } else if (llvm::LoadInst *LI = llvm::dyn_cast<llvm::LoadInst>(Inst)) {
    return extractToken(LI);
  } else if (llvm::AllocaInst *AI = llvm::dyn_cast<llvm::AllocaInst>(Inst)) {
    return extractToken(AI);
  } else if (llvm::BitCastInst *BI = llvm::dyn_cast<llvm::BitCastInst>(Inst)) {
    return extractToken(BI);
  } else if (llvm::ReturnInst *RI = llvm::dyn_cast<llvm::ReturnInst>(Inst)) {
    return extractToken(RI);
  } else if (llvm::GetElementPtrInst *GEP =
                 llvm::dyn_cast<llvm::GetElementPtrInst>(Inst)) {
    return extractToken(GEP);
  } else if (llvm::CallInst *CI = llvm::dyn_cast<llvm::CallInst>(Inst)) {
    return extractToken(CI);
  } else if(llvm::isa<llvm::PHINode>(Inst)){
  	return extractPHINodeToken(Inst);
  }else {
    // Direct support to some instructions may not be useful example
    // CallInst, as it is more useful to generate alias object for call
    // arguments on the fly
    llvm::errs() << "[TODO]: Unsupported Instruction " << *Inst << "\n";
  }
  return {};
}

/// extractToken - Returns a vector of alias objects derived from
/// Global variable \Global operands
std::vector<Token *> TokenWrapper::extractToken(llvm::GlobalVariable *Global) {
  std::vector<Token *> TokenVec;
  if (Global->hasName() && !Global->getName().startswith("_")) {
    TokenVec.push_back(this->getToken(Global));
    TokenVec.push_back(
        this->getToken(Global->getName().str() + "-orig", nullptr));
  }
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for StoreInst \Inst
/// operands.
std::vector<Token *> TokenWrapper::extractToken(llvm::StoreInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example store op1 op2
  std::vector<Token *> TokenVec;
  TokenVec.push_back(this->getToken(Inst->getPointerOperand()));
  llvm::Value *ValOp = Inst->getValueOperand();
  // if (!llvm::isa<llvm::ConstantInt>(ValOp))
  //   TokenVec.push_back(this->getToken(ValOp));
	if(llvm::ConstantPointerNull *Constant = llvm::dyn_cast<llvm::ConstantPointerNull>(ValOp)){
		std::string s("NULL");
		TokenVec.push_back(this->getToken(s,Inst->getParent()->getParent()));
	}
	else if(!llvm::isa<llvm::ConstantInt>(ValOp)){
		TokenVec.push_back(this->getToken(ValOp));
	}
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for StoreInst \Inst
/// operands.
std::vector<Token *> TokenWrapper::extractToken(llvm::LoadInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = load op1
  std::vector<Token *> TokenVec;
  TokenVec.push_back(this->getToken(Inst));
  TokenVec.push_back(this->getToken(Inst->getPointerOperand()));
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for AllocaInst \Inst
/// operands.
std::vector<Token *> TokenWrapper::extractToken(llvm::AllocaInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = alloca op1
  std::vector<Token *> TokenVec;
  Token *Alloca = this->getToken(Inst);
  TokenVec.push_back(Alloca);
  TokenVec.push_back(this->getToken(Alloca->getName().str() + "-orig",
                                    Inst->getParent()->getParent()));
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for ReturnInst \Inst
/// operands.
std::vector<Token *> TokenWrapper::extractToken(llvm::ReturnInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example return op1
  std::vector<Token *> TokenVec;
  llvm::Value *RetVal = Inst->getReturnValue();
  if (RetVal && !llvm::isa<llvm::ConstantInt>(RetVal))
    TokenVec.push_back(this->getToken(RetVal));
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for BitCastInst \Inst
/// operands.
std::vector<Token *> TokenWrapper::extractToken(llvm::BitCastInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = bitcast op1
  std::vector<Token *> TokenVec;
  TokenVec.push_back(this->getToken(Inst));
  if (llvm::CallInst *CI =
          llvm::dyn_cast<llvm::CallInst>(Inst->getOperand(0))) {
    if (CI->getCalledFunction()->getName().startswith("_Zn") ||
        CI->getCalledFunction()->getName().startswith("_zn"))
      TokenVec.push_back(this->getToken(Inst->getDestTy()));
  } else if (llvm::BitCastInst *BI =
                 llvm::dyn_cast<llvm::BitCastInst>(Inst->getOperand(0))) {
    TokenVec.push_back(this->getToken(BI->getDestTy()));
  }
  if (TokenVec.size() == 1) {
    TokenVec.push_back(this->getToken(Inst->getOperand(0)));
  }
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for GetElementPointer
/// \Inst operands.
std::vector<Token *> TokenWrapper::extractToken(llvm::GetElementPtrInst *Inst) {
  // Only provides partial support and returns {op1, op2[idx1]} for op1 = GEP
  // op2 0 idx1
  std::vector<Token *> TokenVec;
  llvm::Function *Func = Inst->getParent()->getParent();
  TokenVec.push_back(this->getToken(Inst));
  TokenVec.push_back(this->getToken(llvm::cast<llvm::GEPOperator>(Inst), Func));
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for Argument \Arg of
/// Function \Func
std::vector<Token *> TokenWrapper::extractToken(llvm::Argument *Arg,
                                                llvm::Function *Func) {
  std::vector<Token *> TokenVec;
  Token *ArgToken = this->getToken(Arg);
  TokenVec.push_back(ArgToken);
  TokenVec.push_back(this->getToken(Arg->getName().str() + "-orig", Func));
  return TokenVec;
}

/// extractToken - Returns the alias object for variable storing the
/// return value from the function call
std::vector<Token *> TokenWrapper::extractToken(llvm::CallInst *CI) {
  std::vector<Token *> TokenVec;
  if (!CI->doesNotReturn()) {
    TokenVec.push_back(this->getToken(CI));
  }
  return TokenVec;
}

/// extractPHINodeToken - Returns aliases for the PHINode instruction
std::vector<Token *> TokenWrapper::extractPHINodeToken(llvm::Instruction *Inst){
	std::vector<Token *> TokenVec;
	Token *PhiNode = this->getToken(Inst);
	TokenVec.push_back(PhiNode);
	if(Inst->getOperand(0)->hasName()){
		TokenVec.push_back(this->getToken(Inst->getOperand(0)));
	}
	if(Inst->getOperand(1)->hasName()){
		TokenVec.push_back(this->getToken(Inst->getOperand(1)));
	}
	return TokenVec;
}

/// extractPHINodeStetementType - Returns relative level of redirection based on LHS and RHS
/// for PHINode instruction.
std::vector<int> TokenWrapper::extractPHINodeStatementType(llvm::Instruction *Inst){
	if(llvm::isa<llvm::PHINode>(Inst)){
		return {1,1,1};
	}
	return {};
}

/// handleGEPUtil - Returns the extended field value for a GEP
template <typename GEP> Token *TokenWrapper::handleGEPUtil(GEP *G, Token *Ptr) {
  if (!Ptr)
    return Ptr;
  Token *FieldVal = new Token(Ptr);
  FieldVal->setIndex(G);
  FieldVal = this->getToken(FieldVal);
  return FieldVal;
}
template Token *
TokenWrapper::handleGEPUtil<llvm::GetElementPtrInst>(llvm::GetElementPtrInst *G,
                                                     Token *Ptr);
template Token *
TokenWrapper::handleGEPUtil<llvm::GEPOperator>(llvm::GEPOperator *G,
                                               Token *Ptr);

TokenWrapper::~TokenWrapper() {
  for (auto X : TokenBank) {
    delete X.second;
  }
}

} // namespace spatial

#include "InstModel/GenericInstModel/GenericInstModel.h"
#include "InstInfo/InstInfo.h"
#include "vector"

namespace spatial {

/// extractInstInfo - Returns empty InstInfo for every instruction as it is not
/// support right now
InstInfo GenericInstModel::extractInstInfo(llvm::Instruction *) {
  InstInfo II;
  return II;
}

/// extractToken - Returns a vector of alias objects derived from
/// Instruction \Inst operands
std::vector<Token *> GenericInstModel::extractToken(llvm::Instruction *Inst) {
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
  } else {
    // Direct support to some instructions may not be useful example
    // CallInst, as it is more useful to generate alias object for call
    // arguments on the fly
    llvm::errs() << "[TODO]: Unsupported Instruction " << *Inst << "\n";
  }
  return {};
}

/// extractToken - Returns a vector of alias objects derived from
/// Global variable \Global operands
std::vector<Token *>
GenericInstModel::extractToken(llvm::GlobalVariable *Global) {
  std::vector<Token *> TokenVec;
  if (Global->hasName() && !Global->getName().startswith("_")) {
    TokenVec.push_back(this->getTokenWrapper()->getToken(Global));
    TokenVec.push_back(this->getTokenWrapper()->getToken(
        Global->getName().str() + "-orig", nullptr));
  }
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for StoreInst \Inst
/// operands.
std::vector<Token *> GenericInstModel::extractToken(llvm::StoreInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example store op1 op2
  std::vector<Token *> TokenVec;
  TokenVec.push_back(
      this->getTokenWrapper()->getToken(Inst->getPointerOperand()));
  llvm::Value *ValOp = Inst->getValueOperand();
  if (!llvm::isa<llvm::ConstantInt>(ValOp)){
    if(llvm::isa<llvm::ConstantPointerNull>(ValOp)){
      std::string s("NULL");
      TokenVec.push_back(this->getTokenWrapper()->getToken(s,nullptr));
    }
    else{
      TokenVec.push_back(this->getTokenWrapper()->getToken(ValOp));
    }
  }
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for StoreInst \Inst
/// operands.
std::vector<Token *> GenericInstModel::extractToken(llvm::LoadInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = load op1
  std::vector<Token *> TokenVec;
  TokenVec.push_back(this->getTokenWrapper()->getToken(Inst));
  TokenVec.push_back(
      this->getTokenWrapper()->getToken(Inst->getPointerOperand()));
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for AllocaInst \Inst
/// operands.
std::vector<Token *> GenericInstModel::extractToken(llvm::AllocaInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = alloca op1
  std::vector<Token *> TokenVec;
  Token *Alloca = this->getTokenWrapper()->getToken(Inst);
  TokenVec.push_back(Alloca);
  TokenVec.push_back(this->getTokenWrapper()->getToken(
      Alloca->getName().str() + "-orig", Inst->getParent()->getParent()));
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for ReturnInst \Inst
/// operands.
std::vector<Token *> GenericInstModel::extractToken(llvm::ReturnInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example return op1
  std::vector<Token *> TokenVec;
  llvm::Value *RetVal = Inst->getReturnValue();
  if (RetVal && !llvm::isa<llvm::ConstantInt>(RetVal))
    TokenVec.push_back(this->getTokenWrapper()->getToken(RetVal));
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for BitCastInst \Inst
/// operands.
std::vector<Token *> GenericInstModel::extractToken(llvm::BitCastInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = bitcast op1
  std::vector<Token *> TokenVec;
  TokenVec.push_back(this->getTokenWrapper()->getToken(Inst));
  if (llvm::CallInst *CI =
          llvm::dyn_cast<llvm::CallInst>(Inst->getOperand(0))) {
    if (CI->getCalledFunction()->getName().startswith("_Zn") ||
        CI->getCalledFunction()->getName().startswith("_zn"))
      TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getDestTy()));
  } else if (llvm::BitCastInst *BI =
                 llvm::dyn_cast<llvm::BitCastInst>(Inst->getOperand(0))) {
    TokenVec.push_back(this->getTokenWrapper()->getToken(BI->getDestTy()));
  }
  if (TokenVec.size() == 1) {
    TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getOperand(0)));
  }
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for GetElementPointer
/// \Inst operands.
std::vector<Token *>
GenericInstModel::extractToken(llvm::GetElementPtrInst *Inst) {
  // Only provides partial support and returns {op1, op2[idx1]} for op1 = GEP
  // op2 0 idx1
  std::vector<Token *> TokenVec;
  llvm::Function *Func = Inst->getParent()->getParent();
  TokenVec.push_back(this->getTokenWrapper()->getToken(Inst));
  TokenVec.push_back(this->getTokenWrapper()->getToken(
      llvm::cast<llvm::GEPOperator>(Inst), Func));
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for Argument \Arg of
/// Function \Func
std::vector<Token *> GenericInstModel::extractToken(llvm::Argument *Arg,
                                                    llvm::Function *Func) {
  std::vector<Token *> TokenVec;
  Token *ArgToken = this->getTokenWrapper()->getToken(Arg);
  TokenVec.push_back(ArgToken);
  TokenVec.push_back(
      this->getTokenWrapper()->getToken(Arg->getName().str() + "-orig", Func));
  return TokenVec;
}

/// extractToken - Returns the alias object for variable storing the
/// return value from the function call
std::vector<Token *> GenericInstModel::extractToken(llvm::CallInst *CI) {
  std::vector<Token *> TokenVec;
  if (!CI->doesNotReturn()) {
    TokenVec.push_back(this->getTokenWrapper()->getToken(CI));
  }
  return TokenVec;
}
/// extractPHINodeToken - Returns the alias objects for PHInode instruction
std::vector<Token *> GenericInstModel::extractPHINodeToken(llvm::Instruction *Inst){
	std::vector<Token *> TokenVec;
	TokenVec.push_back(this->getTokenWrapper()->getToken(Inst));
	if(Inst->getOperand(0)->hasName()){
		TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getOperand(0)));
	}
	if(Inst->getOperand(1)->hasName()){
		TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getOperand(1)));
	}
	return TokenVec;
}

/// extractRedirections - Returns the relative level of redirection based of
/// LHS and RHS on the statement
std::vector<int>
GenericInstModel::extractRedirections(llvm::Instruction *Inst) {
  std::vector<int> load{1, 2}, store{2, 1}, copy{1, 1}, assign{1, 0}, phiNode{1,1,1};
  if (llvm::isa<llvm::AllocaInst>(Inst) ||
      llvm::isa<llvm::GetElementPtrInst>(Inst))
    return assign;
  if (llvm::isa<llvm::StoreInst>(Inst))
    return store;
  if (llvm::isa<llvm::LoadInst>(Inst))
    return load;
  if(llvm::isa<llvm::PHINode>(Inst))
    return phiNode;
  return copy;
}

std::vector<int>
GenericInstModel::extractRedirections(llvm::GlobalVariable *G) {
  std::vector<int> load{1, 2}, store{2, 1}, copy{1, 1}, assign{1, 0};
  if (llvm::isa<llvm::GlobalVariable>(G))
    return assign;
}

/// handleGEPUtil - Returns the extended field value for a GEP
template <typename GEP>
Token *GenericInstModel::handleGEPUtil(GEP *G, Token *Ptr) {
  if (!Ptr)
    return Ptr;
  Token *FieldVal = new Token(Ptr);
  FieldVal->setIndex(G);
  FieldVal = this->getTokenWrapper()->getToken(FieldVal);
  return FieldVal;
}
template Token *GenericInstModel::handleGEPUtil<llvm::GetElementPtrInst>(
    llvm::GetElementPtrInst *G, Token *Ptr);
template Token *
GenericInstModel::handleGEPUtil<llvm::GEPOperator>(llvm::GEPOperator *G,
                                                   Token *Ptr);

GenericInstModel::~GenericInstModel(){};
} // namespace spatial

#include "Token/Token.h"

namespace spatial {

Token::Token() {
  this->TyLength = 3;
  this->opTokenTy = llvm::BitVector(this->TyLength, false);
}

void Token::set(llvm::Value *Val, unsigned int Kind, std::string Index,
                llvm::Function *Func, bool Global) {
  this->Val = Val;
  this->Ty = Val->getType();
  this->Kind = Kind;
  this->Index = Index;
  this->Func = Func;
  this->IsGlobal = Global;
  if (!Func)
    this->IsGlobal = true;
}

void Token::set(llvm::Type *Ty, unsigned int Kind, std::string Index) {
  this->Ty = Ty;
  this->Kind = Kind;
  this->Index = Index;
  this->IsGlobal = false;
}

void Token::set(llvm::Argument *Arg, unsigned int Kind, std::string Index,
                llvm::Function *Func) {
  this->Arg = Arg;
  this->Ty = Arg->getType();
  this->Kind = Kind;
  this->Index = Index;
  this->Func = Func;
  this->IsGlobal = false;
}

void Token::set(std::string S, unsigned int Kind, std::string Index,
                llvm::Function *Func) {
  this->Val = nullptr;
  this->name = S;
  this->Kind = Kind;
  this->Index = Index;
  this->IsGlobal = false;
  if (!Func)
    this->IsGlobal = true;
  this->Func = Func;
}

Token::Token(llvm::Value *Val, std::string Index) {
  this->TyLength = 3;
  this->opTokenTy = llvm::BitVector(this->TyLength, false);

  if (llvm::Argument *Arg = llvm::dyn_cast<llvm::Argument>(Val)) {
    set(Arg, /* Kind = */ 2, Index, Arg->getParent());
  } else {
    // If Val is GEPOperator, it must be coming from load/store
    if (llvm::GEPOperator *GOP = llvm::dyn_cast<llvm::GEPOperator>(Val)) {
      // We handle GEPInst separately
      if (!llvm::isa<llvm::Instruction>(GOP)) {
        Val = GOP->getPointerOperand();
        Index = this->getIndex(GOP);
      }
    }
    llvm::Function *func = nullptr;
    if (llvm::Instruction *Inst = llvm::dyn_cast<llvm::Instruction>(Val))
      func = Inst->getParent()->getParent();
    if (llvm::isa<llvm::GlobalVariable>(Val) || !func)
      set(Val, /* Kind = */ 0, Index, func, true);
    else
      set(Val, /* Kind = */ 0, Index, func);
  }
}

Token::Token(llvm::GEPOperator *GOP, llvm::Function *Func, std::string Index) {
  this->TyLength = 3;
  this->opTokenTy = llvm::BitVector(this->TyLength, false);

  llvm::Value *Val = GOP->getPointerOperand();
  Index = this->getIndex(GOP);
  set(Val, /* Kind = */ 0, Index, Func);
}

Token::Token(llvm::Argument *Arg, std::string Index) {
  this->TyLength = 3;
  this->opTokenTy = llvm::BitVector(this->TyLength, false);
  set(Arg, /* Kind = */ 2, Index, Arg->getParent());
}

Token::Token(llvm::Type *Ty, std::string Index) {
  this->TyLength = 3;
  this->opTokenTy = llvm::BitVector(this->TyLength, false);
  set(Ty, /* Kind = */ 1, Index);
}

Token::Token(std::string S, llvm::Function *Func, std::string Index) {
  this->TyLength = 3;
  this->opTokenTy = llvm::BitVector(this->TyLength, false);
  set(S, /* Kind = */ 3, Index, Func);
}

Token::Token(Token *A) {
  this->TyLength = 3;
  this->opTokenTy = llvm::BitVector(this->TyLength, false);
  unsigned int Kind = A->Kind;
  if (Kind == 0) {
    set(A->Val, A->Kind, A->Index, A->Func);
  } else if (Kind == 1) {
    set(A->Ty, A->Kind, A->Index);
  } else if (Kind == 2) {
    set(A->Arg, A->Kind, A->Index, A->Func);
  } else if (Kind == 3) {
    set(A->name, A->Kind, A->Index, A->Func);
  }
}

/// setIndex - For a GEP Instruction find the offset and store it
void Token::setIndex(llvm::GetElementPtrInst *GEPInst) {
  if (llvm::GEPOperator *GEPOp = llvm::dyn_cast<llvm::GEPOperator>(GEPInst)) {
    this->Index = getIndex(GEPOp);
  }
}

/// setIndex - For a GEP Operator find the offset and store it
void Token::setIndex(llvm::GEPOperator *GEPOp) {
  this->Index = getIndex(GEPOp);
}

/// setIndex - For a Token. Required in case of nested structures
/// wherein the token belongs to a chain of GEP instructions
void Token::setIndex(Token *T, std::string indx) {
  this->Index = indx + T->Index;
}

/// setIndex - For a Token
void Token::setIndex(Token *T) { this->Index = T->Index; }

/// resetIndex - Resets the index back to an empty string
void Token::resetIndex() { this->Index = ""; }

/// resetIndexToZero - Resets the index to string zero for bitcast instr
void Token::resetIndexToZero() { this->Index = "[0]"; }

/// resetIndexToZero - Resets the index to string zero for nested bitcast instr
void Token::resetIndexToZero(std::string S) { this->Index = S + "[0]"; }

/// getIndex - For a GEP Operator find the offset
std::string Token::getIndex(llvm::GEPOperator *GEPOp) {
 auto Iter = GEPOp->idx_begin();
 std::string Index = "[";
 while (Iter != GEPOp->idx_end()) { 
    llvm::Value *temp = &(*Iter->get());
    if (llvm::ConstantInt *CI = llvm::dyn_cast<llvm::ConstantInt>(temp)) 
      Index += CI->getValue().toString(10, true) + "][";
    else 
	Index += temp->getName().str() + "][";
    Iter++;
  }
  return Index.substr(0, Index.size() - 1);
}

template <typename GOP> bool Token::isGEPOperandArrayTy(GOP *G, int Idx) {
  llvm::Type *StructType = G->getOperand(0)->getType();
  if (StructType->getNumContainedTypes() > 0)
    StructType = StructType->getContainedType(0);
  int OpNum = G->getNumOperands();
  Idx += 1;
  if (Idx > 1)
    OpNum = Idx;
  for (int i = 2; i < OpNum; i++) {
    while (StructType->isArrayTy()) {
      StructType = StructType->getArrayElementType();
      i = i + 1;
    }
    if (i >= OpNum)
      break;
    llvm::Value *IdxV = G->getOperand(i);
    llvm::ConstantInt *Idx = llvm::cast<llvm::ConstantInt>(IdxV);
    StructType = StructType->getStructElementType(Idx->getSExtValue());
  }
  return StructType->isArrayTy();
}

template bool
Token::isGEPOperandArrayTy<llvm::GetElementPtrInst>(llvm::GetElementPtrInst *G,
                                                    int Idx = -1);
template bool
Token::isGEPOperandArrayTy<llvm::GEPOperator>(llvm::GEPOperator *G,
                                              int Idx = -1);

/// getValue - Returns the underlying Value* for the alias
llvm::Value *Token::getValue() const {
  if (this->Kind == 0) {
    return this->Val;
  }
  return nullptr;
}

std::ostream &operator<<(std::ostream &OS, const Token &A) {
  if (!A.isGlobalVar() && (A.Kind == 0 || A.Kind == 2 || A.Kind == 3)) {
    OS << "[" << A.Func->getName().str() << "]"
       << " ";
  }
  if (A.Kind == 0) {
    OS << A.Val->getName().str();
  } else if (A.Kind == 1) {
    OS << A.getMemTypeName();
  } else if (A.Kind == 2) {
    OS << A.Arg->getName().str();
  } else if (A.Kind == 3) {
    OS << A.name;
  }
  if (A.Index != "") {
    OS << A.Index;
  }
  return OS;
}

/// getName - Returns the name of alias with other informations like parent
/// function etc
llvm::StringRef Token::getName() const {
  if (this->Kind == 0) {
    return this->Val->getName();
  } else if (this->Kind == 2) {
    return this->Arg->getName();
  } else if (this->Kind == 3) {
    return this->name;
  }
  return "";
}

/// getMemTypeName - Returns the memory type name
std::string Token::getMemTypeName() const {
  std::string MemTyName = "";
  if (!this->isMem())
    return MemTyName;
  llvm::raw_string_ostream RSO(MemTyName);
  this->Ty->print(RSO);
  return MemTyName;
}

/// getFunctionName - Returns the name of the parent function
std::string Token::getFunctionName() const {
  if (this->isMem() || this->isGlobalVar())
    return "";
  assert(Func != nullptr && "Function can not be null");
  return (this->Func->getName()).str();
}

/// getFieldIndex - Returns index of the field
std::string Token::getFieldIndex() const { return this->Index; }

/// isMem - Returns true if the alias denotes a location in heap
bool Token::isMem() const { return this->Kind == 1; }

/// isGlobalVar - Returns true if the alias is global
bool Token::isGlobalVar() const { return this->IsGlobal; }

/// isArg - Returns true if alias is a function argument
bool Token::isArg() const { return this->Kind == 2; }

/// isField - Returns true if alias is a field
bool Token::isField() const { return this->Index != ""; }

/// isAllocaOrArgOrGlobal - Returns true if the alias is global, an argument or
/// alloca
bool Token::isAllocaOrArgOrGlobal() const {
  return this->isMem() || this->isGlobalVar() || this->isArg();
}

/// sameFunc = Returns true if the parent function of alias is same as /p Func
bool Token::sameFunc(llvm::Function *Func) const {
  if (this->Func)
    return this->Func == Func;
  return false;
}

/// isBasePointerType - Returns true if the Token type's base type is a pointer
bool Token::isBasePointerType() const {
  if (this->Kind == 0 || this->Kind == 1 || this->Kind == 2) {
    // check for no base types
    if (Ty->getNumContainedTypes() == 0)
      return false;
    llvm::Type *BaseTy = Ty->getContainedType(0);
    return BaseTy->isPointerTy();
  }
  return false;
}

bool Token::isValPointerType() const {
  if (this->Ty->isPointerTy())
    return true;
  return false;
}

///  getHash - Calculates the hash for alias to avoid multiple enteries of same
///  alias
std::string Token::getHash() const {
  std::string hash = "";
  if (this->isGlobalVar())
    hash += "G";
  hash += this->getName().str();
  hash += this->getFunctionName();
  hash += this->getMemTypeName();
  hash += this->getFieldIndex();
  return hash;
}

bool Token::operator<(const Token &TheToken) const {
  return (this->getHash() < TheToken.getHash());
}

bool Token::operator==(const Token &TheToken) const {
  return (this->getHash() == TheToken.getHash());
}

void Token::operator=(const Token &TheToken) {
  unsigned int Kind = TheToken.Kind;
  if (Kind == 0) {
    set(TheToken.Val, TheToken.Kind, TheToken.Index, TheToken.Func);
  } else if (Kind == 1) {
    set(TheToken.Ty, TheToken.Kind, TheToken.Index);
  } else if (Kind == 2) {
    set(TheToken.Arg, TheToken.Kind, TheToken.Index, TheToken.Func);
  } else if (Kind == 3) {
    set(TheToken.name, TheToken.Kind, TheToken.Index, TheToken.Func);
  }
}

void Token::setIsGlobal() { this->IsGlobal = true; }

void Token::setIsArray() { this->opTokenTy.set(isArray); }

bool Token::getIsArray() { return opTokenTy.test(isArray); }

void Token::setIsAlloca() { this->opTokenTy.set(isAlloca); }

bool Token::getIsAlloca() { return opTokenTy.test(isAlloca); }

void Token::setIsOpBitcast() { this->opTokenTy.set(isOpBitcast); }

bool Token::getIsOpBitcast() { return opTokenTy.test(isOpBitcast); }

template <typename GOP> std::vector<int> Token::getGEPArrayIndex(GOP *G) {
  std::vector<int> Idx;
  for (int i = 2; i < G->getNumOperands(); i++) {
    if (isGEPOperandArrayTy(G, i - 1)) {
      Idx.push_back(i);
    }
  }
  return Idx;
}

template std::vector<int>
Token::getGEPArrayIndex<llvm::GetElementPtrInst>(llvm::GetElementPtrInst *G);
template std::vector<int>
Token::getGEPArrayIndex<llvm::GEPOperator>(llvm::GEPOperator *G);

} // namespace spatial

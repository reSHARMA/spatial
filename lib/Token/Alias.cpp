#include "Token/Alias.h"

namespace spatial {

void Alias::set(llvm::Value* Val, unsigned int Kind, std::string Index,
                llvm::Function* Func, bool Global) {
    this->Val = Val;
    this->Kind = Kind;
    this->Index = Index;
    this->Func = Func;
    this->IsGlobal = Global;
    if (!Func) this->IsGlobal = true;
}

void Alias::set(llvm::Type* Ty, unsigned int Kind, std::string Index) {
    this->Ty = Ty;
    this->Kind = Kind;
    this->Index = Index;
    this->IsGlobal = false;
}

void Alias::set(llvm::Argument* Arg, unsigned int Kind, std::string Index,
                llvm::Function* Func) {
    this->Arg = Arg;
    this->Kind = Kind;
    this->Index = Index;
    this->Func = Func;
    this->IsGlobal = false;
}

void Alias::set(std::string S, unsigned int Kind, std::string Index,
                llvm::Function* Func) {
    this->Val = nullptr;
    this->name = S;
    this->Kind = Kind;
    this->Index = Index;
    this->IsGlobal = false;
    if (!Func) this->IsGlobal = true;
    this->Func = Func;
}

Alias::Alias(llvm::Value* Val, std::string Index) {
    if (llvm::Argument* Arg = llvm::dyn_cast<llvm::Argument>(Val)) {
        set(Arg, /* Kind = */ 2, Index, Arg->getParent());
    } else {
        llvm::Function* func = nullptr;
        if (llvm::Instruction* Inst = llvm::dyn_cast<llvm::Instruction>(Val))
            func = Inst->getParent()->getParent();
        if (llvm::isa<llvm::GlobalVariable>(Val) || !func)
            set(Val, /* Kind = */ 0, Index, func, true);
        else
            set(Val, /* Kind = */ 0, Index, func);
    }
}

Alias::Alias(llvm::Argument* Arg, std::string Index) {
    set(Arg, /* Kind = */ 2, Index, Arg->getParent());
}

Alias::Alias(llvm::Type* Ty, std::string Index) {
    set(Ty, /* Kind = */ 1, Index);
}

Alias::Alias(std::string S, llvm::Function* Func, std::string Index) {
    set(S, /* Kind = */ 3, Index, Func);
}

Alias::Alias(Alias* A) {
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
void Alias::setIndex(llvm::GetElementPtrInst* GEPInst) {
    auto IterRange = GEPInst->indices();
    auto Iter = IterRange.begin();
    std::string Index = "[";
    while (Iter != IterRange.end()) {
        llvm::Value* temp = &(*Iter->get());
        if (llvm::ConstantInt* CI = llvm::dyn_cast<llvm::ConstantInt>(temp)) {
            Index += CI->getValue().toString(10, true) + "][";
        }
        Iter++;
    }
    this->Index = Index.substr(3, Index.size() - 4);
}

/// setIndex - For a GEP Operator find the offset and store it
void Alias::setIndex(llvm::GEPOperator* GEPOp) {
    auto Iter = GEPOp->idx_begin();
    std::string Index = "[";
    while (Iter != GEPOp->idx_end()) {
        llvm::Value* temp = &(*Iter->get());
        if (llvm::ConstantInt* CI = llvm::dyn_cast<llvm::ConstantInt>(temp)) {
            Index += CI->getValue().toString(10, true) + "][";
        }
        Iter++;
    }
    this->Index = Index.substr(3, Index.size() - 4);
}

/// getValue - Returns the underlying Value* for the alias
llvm::Value* Alias::getValue() const {
    if (this->Kind == 0) {
        return this->Val;
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& OS, const Alias& A) {
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
llvm::StringRef Alias::getName() const {
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
std::string Alias::getMemTypeName() const {
    std::string MemTyName = "";
    if (!this->isMem()) return MemTyName;
    llvm::raw_string_ostream RSO(MemTyName);
    this->Ty->print(RSO);
    return MemTyName;
}

/// getFunctionName - Returns the name of the parent function
std::string Alias::getFunctionName() const {
    if (this->isMem() || this->isGlobalVar()) return "";
    assert(Func != nullptr && "Function can not be null");
    return (this->Func->getName()).str();
}

/// getFieldIndex - Returns index of the field
std::string Alias::getFieldIndex() const { return this->Index; }

/// isMem - Returns true if the alias denotes a location in heap
bool Alias::isMem() const { return this->Kind == 1; }

/// isGlobalVar - Returns true if the alias is global
bool Alias::isGlobalVar() const { return this->IsGlobal; }

/// isArg - Returns true if alias is a function argument
bool Alias::isArg() const { return this->Kind == 2; }

/// isField - Returns true if alias is a field
bool Alias::isField() const { return this->Index != ""; }

/// isAllocaOrArgOrGlobal - Returns true if the alias is global, an argument or
/// alloca
bool Alias::isAllocaOrArgOrGlobal() const {
    return this->isMem() || this->isGlobalVar() || this->isArg();
}

/// sameFunc = Returns true if the parent function of alias is same as /p Func
bool Alias::sameFunc(llvm::Function* Func) const {
    if (this->Func) return this->Func == Func;
    return false;
}

///  getHash - Calculates the hash for alias to avoid multiple enteries of same
///  alias
std::string Alias::getHash() const {
    std::string hash = "";
    if (this->isGlobalVar()) hash += "G";
    hash += this->getName().str();
    hash += this->getFunctionName();
    hash += this->getMemTypeName();
    hash += this->getFieldIndex();
    return hash;
}

bool Alias::operator<(const Alias& TheAlias) const {
    return (this->getHash() < TheAlias.getHash());
}

bool Alias::operator==(const Alias& TheAlias) const {
    return (this->getHash() == TheAlias.getHash());
}

void Alias::operator=(const Alias& TheAlias) {
    unsigned int Kind = TheAlias.Kind;
    if (Kind == 0) {
        set(TheAlias.Val, TheAlias.Kind, TheAlias.Index, TheAlias.Func);
    } else if (Kind == 1) {
        set(TheAlias.Ty, TheAlias.Kind, TheAlias.Index);
    } else if (Kind == 2) {
        set(TheAlias.Arg, TheAlias.Kind, TheAlias.Index, TheAlias.Func);
    } else if (Kind == 3) {
        set(TheAlias.name, TheAlias.Kind, TheAlias.Index, TheAlias.Func);
    }
}

}  // namespace spatial

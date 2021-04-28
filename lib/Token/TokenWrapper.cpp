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

TokenWrapper::~TokenWrapper() {
  for (auto X : TokenBank) {
    delete X.second;
  }
}

} // namespace spatial

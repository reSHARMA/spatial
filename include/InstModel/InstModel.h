#ifndef INSTMODEL_INSTMODEL_H
#define INSTMODEL_INSTMODEL_H

#include "InstInfo/InstInfo.h"
#include "Token/Token.h"
#include "Token/TokenWrapper.h"
#include "vector"
#include "llvm/IR/Instruction.h"

namespace spatial {

class InstModel {
private:
  TokenWrapper *TW;

public:
  InstModel(TokenWrapper *TW);
  virtual ~InstModel();
  TokenWrapper *getTokenWrapper();
  virtual std::vector<Token *> extractToken(llvm::Instruction *) = 0;
  virtual std::vector<int> extractRedirections(llvm::Instruction *) = 0;
  virtual InstInfo extractInstInfo(llvm::Instruction *) = 0;
};

} // namespace spatial

#endif

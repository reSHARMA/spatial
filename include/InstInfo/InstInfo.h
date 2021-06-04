#ifndef INSTINFO_H
#define INSTINFO_H

#include "llvm/ADT/BitVector.h"

namespace spatial {

enum InfoType { Call, Phi, Skip, RWMem };

class InstInfo {
private:
  llvm::BitVector Info;
  // Length = 4
  // Call, Phi, Skip, Read-write-memory
  unsigned int Length;

public:
  InstInfo();
  void setCallInst();
  void setPhiInst();
  void setSkipInst();
  void setRWMemInst();
  bool isCallInst();
  bool isPhiInst();
  bool isSkipInst();
  bool isRWMem();
};
} // namespace spatial

#endif

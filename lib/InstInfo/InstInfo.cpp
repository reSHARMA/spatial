#include "InstInfo/InstInfo.h"

namespace spatial {
InstInfo::InstInfo() {
  this->Length = 4;
  Info = llvm::BitVector(this->Length, false);
}

/// setCallInst - set call bit true
void InstInfo::setCallInst() { Info.set(Call); }

/// setPhiInst - set phi bit true
void InstInfo::setPhiInst() { Info.set(Phi); }

/// setSkipInst - set skip bit true
void InstInfo::setSkipInst() { Info.set(Skip); }

/// setRWmemInst - set true for instructions that read or write from memory
void InstInfo::setRWMemInst() { Info.set(RWMem); }

/// isCallInst - returns true if the call bit is set to true
bool InstInfo::isCallInst() { return Info.test(Call); }

/// isPhiInst - Returns the phi bit
bool InstInfo::isPhiInst() { return Info.test(Phi); }

/// isSkipInst - Returns true if the instruction is to be skipped
bool InstInfo::isSkipInst() { return Info.test(Skip); }

/// isRWMem - Returns true if the instruction touches memory
bool InstInfo::isRWMem() { return Info.test(RWMem); }

} // namespace spatial

#include "InstModel/LFCPAInstModel/LFCPAInstModel.h"
#include "InstInfo/InstInfo.h"
#include "vector"
#include "queue"

namespace spatial {

/// extractInstInfo - Returns empty InstInfo for every instruction as it is not
/// support right now
InstInfo LFCPAInstModel::extractInstInfo(llvm::Instruction *) {
  InstInfo II;
  return II;
}

/// extractToken - Returns a vector of alias objects derived from
/// Instruction \Inst operands
std::vector<Token *> LFCPAInstModel::extractToken(llvm::Instruction *Inst) {
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
  } else if (llvm::CmpInst *CM = llvm::dyn_cast<llvm::CmpInst>(Inst)) {
    return extractToken(CM);
  } else if (llvm::CallInst *CI = llvm::dyn_cast<llvm::CallInst>(Inst)) {
    return extractToken(CI);
  } else if (llvm::PHINode *PHI = llvm::dyn_cast<llvm::PHINode>(Inst)) {
    return extractToken(PHI);
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
LFCPAInstModel::extractToken(llvm::GlobalVariable *Global) {
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
std::vector<Token *> LFCPAInstModel::extractToken(llvm::StoreInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example store op1 op2
  std::vector<Token *> TokenVec;
  //Check for store to non-pointers
  if (llvm::isa<llvm::GEPOperator>(Inst->getOperand(1))) {  

    llvm::GEPOperator *GOP = llvm::dyn_cast<llvm::GEPOperator>(Inst->getOperand(1));
  
    if (isStructFieldPointerTy(GOP)) { 
  	Token* opLhs = handleGEPUtil(GOP, this->getTokenWrapper()->getToken(Inst->getPointerOperand()));
	TokenVec.push_back(opLhs);
        llvm::Value *ValOp = Inst->getValueOperand();
	if (!llvm::isa<llvm::ConstantInt>(ValOp))
	    TokenVec.push_back(this->getTokenWrapper()->getToken(ValOp));
    }//end if
    else {
	llvm::errs() << "\n ****Store Instruction skipped:Struct field is not pointer type.\n "<<*Inst;
        InstInfo *II = new InstInfo();
        II->setSkipInst();
    }//end else
  }//end outer if
   else if (this->getTokenWrapper()->getToken(Inst->getPointerOperand())->isBasePointerType()) { /* Ignore Stores to non-pointers */
     llvm::errs()<<"\n STORE TO A POINTER";
     TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getPointerOperand()));
     llvm::Value *ValOp = Inst->getValueOperand();
     if (!llvm::isa<llvm::ConstantInt>(ValOp)) {  
         //if (this->getTokenWrapper()->getToken(ValOp)->isNullToken())
	//	llvm::errs() << "\n TOKEN IS A NULL";
     	 TokenVec.push_back(this->getTokenWrapper()->getToken(ValOp));
	}
  }
  else {
	llvm::errs() << "\n ****Store Instruction skipped: Store to a non pointer.\n"<<*Inst;
	InstInfo *II = new InstInfo();
        II->setSkipInst();   
  }
  return TokenVec;	
}

/// extractToken - Returns a vector of alias objects for LoadInst \Inst
/// operands.
std::vector<Token *> LFCPAInstModel::extractToken(llvm::LoadInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = load op1
std::vector<Token *> TokenVec;
//Check for load of non-pointers
if (llvm::isa<llvm::GEPOperator>(Inst->getPointerOperand())) {
    llvm::GEPOperator *GOP = llvm::dyn_cast<llvm::GEPOperator>(Inst->getOperand(0));

    if (isStructFieldPointerTy(GOP)) { 
	TokenVec.push_back(this->getTokenWrapper()->getToken(Inst)); 
	TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getPointerOperand()));	  
    }//end if
    else {
	llvm::errs() << "\n ****Load Instruction skipped: Struct field is not pointer type.\n"<<*Inst;
        InstInfo *II = new InstInfo();
        II->setSkipInst();
    }//end else
}//end outer if
else if (this->getTokenWrapper()->getToken(Inst->getPointerOperand())->isBasePointerType()) { /* Ignore load of non-pointers */
     TokenVec.push_back(this->getTokenWrapper()->getToken(Inst));
     TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getPointerOperand()));     
}
else {
	llvm::errs() << "\n ****Load Instruction skipped: Load of a non pointer. \n"<<*Inst;
	InstInfo *II = new InstInfo();
        II->setSkipInst();   
}	
return TokenVec;	
}

/// extractToken - Returns a vector of Token objects for PHI Inst operands.
std::vector<Token *> LFCPAInstModel::extractToken(llvm::PHINode *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = phi op1 op2

 std::vector<Token *> TokenVec;
 TokenVec.push_back(this->getTokenWrapper()->getToken(Inst)); //Push Lhs
 
if(Inst->getType()->isPointerTy()) {
 for (int i = 0; i < Inst->getNumOperands(); i++) {

  if (!llvm::isa<llvm::ConstantInt>(Inst->getOperand(i))) {   //Consider only if not a constant
	TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getOperand(i)));
	if (llvm::isa<llvm::GEPOperator>(Inst->getOperand(i))) {
		llvm::GEPOperator *GOP = llvm::dyn_cast<llvm::GEPOperator>(Inst->getOperand(i));
		if(isArrayType(GOP)) 
			this->getTokenWrapper()->getToken(Inst->getOperand(i))->setIsArray();
	}
  }//if not constant
  else 
	llvm::errs() << "\n ****Phi Instruction skipped non-pointer/constant ";
 }//end for
}//end if type pointer
 return TokenVec;
}

/// extractToken - Returns a vector of alias objects for AllocaInst \Inst
/// operands.
std::vector<Token *> LFCPAInstModel::extractToken(llvm::AllocaInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = alloca op1
  std::vector<Token *> TokenVec;
  Token *Alloca = this->getTokenWrapper()->getToken(Inst);
  //Alloca->setKindToZero();
  Alloca->setIsAlloca(); //Set isAlloca explicitly for all ALLOCA Lhs
  Alloca->setIsGlobal(); //Set type of Alloca variable to GLOBAL
  TokenVec.push_back(Alloca);
  TokenVec.push_back(this->getTokenWrapper()->getToken(
  Alloca->getName().str() + "-orig", Inst->getParent()->getParent()));
  return TokenVec;
}

/// extractToken - Returns a vector of Token objects for CmpInst \Inst
/// operands.
/* Compare Instruction is not skipped but the Load instrs for loading the operand value are skipped */ 
std::vector<Token *> LFCPAInstModel::extractToken(llvm::CmpInst *Inst) {
   InstInfo *II = new InstInfo();
   II->setSkipInst();
    
   bool skipFlag = false;
   std::vector<Token *> TokenVec;
   llvm::Instruction* Ins, *I;
   Ins = llvm::dyn_cast<llvm::Instruction>(Inst);
   std::queue<llvm::Instruction*> q;

   I = llvm::dyn_cast<llvm::Instruction>(Inst);
   for(int i = 0;i < I->getNumOperands(); i++) {
 	 auto *Op = I->getOperand(i);
	 Token *Opd = new Token(Op);
      if(Opd->getName() != "NULL") {  //Operand is not NULL
         if (!Opd->isValPointerType()) { //if not pointer check if it is loading a pointer
            while(llvm::isa<llvm::LoadInst>(Op)){ 
		  Ins = llvm::dyn_cast<llvm::LoadInst>(Op); 
        	  Op = llvm::cast<llvm::LoadInst>(Op)->getPointerOperand();
		  InstInfoMap[Ins] = II;		  
            }
           Token* OpVal = new Token(Op);
	    if (OpVal->isBasePointerType())
		TokenVec.push_back(this->getTokenWrapper()->getToken(OpVal));
	    else 
		llvm::errs() << "\n ****Compare Instruction Operand skipped non-pointer: \n"<<*Ins;
	 }//end if
	 else
	    TokenVec.push_back(this->getTokenWrapper()->getToken(Op));	  
	}//end null for if
   }//end for
   return TokenVec;
}

/// extractToken - Returns a vector of Token objects for ReturnInst \Inst
/// operands.

/* Return Instruction is not skipped but the Load instrs for loading the return value are skipped */ 
std::vector<Token *> LFCPAInstModel::extractToken(llvm::ReturnInst *Inst) {
  // The original pointer operand is returned for the
  // instruction example return *op1
  InstInfo *II = new InstInfo();
  II->setSkipInst();
  bool skipFlag = false;
  llvm::Instruction *I, *Ins;
  std::vector<Token *> TokenVec;
  llvm::Value *RetVal = Inst->getReturnValue();

  if (RetVal == NULL) {
	llvm::errs() << "\n ****Ignored: Return Value is Null\n "<<*Inst;
	InstInfoMap[Inst] = II;
	auto bit = II->isSkipInst();
  }
  else if (RetVal->getName() == "")  {
	llvm::errs() << "\n ****Ignored: Return Val name is empty stringn\n "<<*Inst;
	InstInfoMap[Inst] = II;
	auto bit = II->isSkipInst();
  }
  else if (RetVal->getType()->isPointerTy()) {
	llvm::errs() << "\n Return Value is Pointer Type ";
   	TokenVec.push_back(this->getTokenWrapper()->getToken(RetVal));
  }
  else if (RetVal && !llvm::isa<llvm::ConstantInt>(RetVal)) { 
     Ins = llvm::dyn_cast<llvm::Instruction>(Inst);
     while(!skipFlag) {  
	for (llvm::Use &U : Ins->operands()) { 
	    llvm::Value* v = U.get();  
	    I = llvm::dyn_cast<llvm::Instruction>(v); 
         if (I != nullptr) { 
	    if (llvm::isa<llvm::LoadInst>(I))	    { 
		if (llvm::isa<llvm::GlobalVariable>(I->getOperand(0)))	{
		  if (I->getOperand(0)->getType()->getContainedType(0)->isPointerTy())  {
		   	llvm::LoadInst *loadI = llvm::dyn_cast<llvm::LoadInst>(I);
		   	llvm::Value *OpVal = loadI->getOperand(0);
		   	
		   	TokenVec.push_back(this->getTokenWrapper()->getToken(OpVal));
			InstInfoMap[I]= II; //Load global instr is skipped
		   	skipFlag = true;
		    }//end if
		    else  { 
			llvm::errs() << "\n ****Return Instruction skipped OPD non-pointer: \n"<<*I;
  		  	InstInfoMap[I]= II;
			skipFlag = true;
			auto bit = II->isSkipInst();
			break;
		    }//end else 
		}//end if ptr
		else {
 		   InstInfoMap[I]= II;
		   Ins = I;
		}//end else
	    }//end if load
	    else {
		llvm::errs() << "\n NOT A LOAD INSTR"<<*I;
		skipFlag = true;
	    }	
	}//end if null ptr
	else {  
		skipFlag = true;
		break;
	   }//end else break
	}//end for
     }//end while	
  }//end if
  else 
	  InstInfoMap[Inst]= II;
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for BitCastInst \Inst
/// operands.
std::vector<Token *> LFCPAInstModel::extractToken(llvm::BitCastInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = bitcast op1
  std::vector<Token *> TokenVec;

  TokenVec.push_back(this->getTokenWrapper()->getToken(Inst)); 
 /* Commented following code as it gave segmentation fault if the operand is an LHS of call instruction (19.5.22)*/
  /*if (llvm::CallInst *CI =
          llvm::dyn_cast<llvm::CallInst>(Inst->getOperand(0))) {   
    if (CI->getCalledFunction()->getName().startswith("_Zn") ||
        CI->getCalledFunction()->getName().startswith("_zn"))
      TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getDestTy()));
  } else*/ if (llvm::BitCastInst *BI =
                 llvm::dyn_cast<llvm::BitCastInst>(Inst->getOperand(0)))  
  TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getOperand(0)));
  
  if (TokenVec.size() == 1) 
    TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getOperand(0)));
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for GetElementPointer
/// \Inst operands.
std::vector<Token *>
LFCPAInstModel::extractToken(llvm::GetElementPtrInst *Inst) {
  // Only provides partial support and returns {op1, op2[idx1]} for op1 = GEP
  // op2 0 idx1
  std::vector<Token *> TokenVec;
  llvm::Function *Func = Inst->getParent()->getParent();
  TokenVec.push_back(this->getTokenWrapper()->getToken(Inst));
  Token* opRhs = handleGEPUtil(Inst, this->getTokenWrapper()->getToken(Inst->getPointerOperand()));
  TokenVec.push_back(opRhs);
  return TokenVec;
}

/// extractToken - Returns a vector of alias objects for Argument \Arg of
/// Function \Func
std::vector<Token *> LFCPAInstModel::extractToken(llvm::Argument *Arg,
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
std::vector<Token *> LFCPAInstModel::extractToken(llvm::CallInst *CI) {
  InstInfo *II = new InstInfo();
  II->setSkipInst();
  bool skipFlag = false;
  llvm::Instruction *I, *Ins;
  std::vector<Token *> TokenVec;
 
  llvm::Function *FP = CI->getCalledFunction();
  if (FP == nullptr) { 
	//Indirect call
	if (!CI->doesNotReturn())
		TokenVec.push_back(this->getTokenWrapper()->getToken(CI));  //Return value
	TokenVec.push_back(this->getTokenWrapper()->getToken(CI->getCalledOperand()));	//Function name
	for(int i = 0;i < CI->arg_size(); i++) {	
 		TokenVec.push_back(this->getTokenWrapper()->getToken(CI->getArgOperand(i)));	//parameters
	}
	return TokenVec;
 }

 // Direct function call
  if (!CI->doesNotReturn()) 
    TokenVec.push_back(this->getTokenWrapper()->getToken(CI));//return value

   I = llvm::dyn_cast<llvm::Instruction>(CI);
   for(int i = 0;i < I->getNumOperands(); i++) {
       	    auto *Op = I->getOperand(i);
	 //   llvm::errs() << "\n OP: "<<*Op;
            while(llvm::isa<llvm::LoadInst>(Op)){
		  Ins = llvm::dyn_cast<llvm::LoadInst>(Op); 
        	  Op = llvm::cast<llvm::LoadInst>(Op)->getPointerOperand();
		 // InstInfoMap[Ins] = II;		  
            }
            Token* OpVal = new Token(Op);
	   // llvm::errs() << "\n OpVal: "<<OpVal->getName();
	    if (OpVal->isBasePointerType())
		TokenVec.push_back(this->getTokenWrapper()->getToken(OpVal));
	    else 
		llvm::errs() << "\n ****Operands of call Instruction non-pointer: \n"<<*I;
   }
  return TokenVec;
}


/// extractRedirections - Returns the relative level of redirection based of
/// LHS and RHS on the statement
std::vector<int>
LFCPAInstModel::extractRedirections(llvm::Instruction *Inst) {
  std::vector<int> load{1, 2}, store{2, 1}, copy{1, 1}, assign{1, 0}, temp{2, 0}, gep{1, 0};
  //std::vector<int> phi1{1, 1, 1}, phi2{1, 0, 0}, phi3{1, 0, 1}, phi4{1, 1, 0};
  if (llvm::isa<llvm::AllocaInst>(Inst) ||
      llvm::isa<llvm::GetElementPtrInst>(Inst))
      return gep;
  if (llvm::isa<llvm::PHINode>(Inst)) {
  	llvm::PHINode *PHI = llvm::dyn_cast<llvm::PHINode>(Inst);
 	std::vector<Token*> vecPhiIns = extractToken(PHI);
	std::vector<int> phiIndir;
	phiIndir.push_back(1); //indir for lhs
	if(vecPhiIns.size() > 1) {
		for (int i = 1; i < vecPhiIns.size(); i++) {
	  		Token *opRhs = vecPhiIns[i];
			if (opRhs->isGlobalVar())
				phiIndir.push_back(0);
			else 
				phiIndir.push_back(1);
		}//end for
  	}//end inner if
	return phiIndir;
  }//end if for phi

  if (llvm::isa<llvm::StoreInst>(Inst)) {
   llvm::StoreInst *SI = llvm::dyn_cast<llvm::StoreInst>(Inst);
   std::vector<Token*> vecStoreIns = extractToken(SI);
   Token* opLhs = vecStoreIns[0];
   Token* opRhs = vecStoreIns[1];
   if (opLhs->isGlobalVar() and (opRhs->isGlobalVar() and !opRhs->getIsFunArg()))
	return assign;
   else if (opLhs->isGlobalVar() and (opRhs->isGlobalVar() and opRhs->getIsFunArg()))
	return copy; 
   else if (!opLhs->isGlobalVar() and opRhs->isGlobalVar())
	return temp;
   else if (opLhs->isGlobalVar() and !opRhs->isGlobalVar())
	return copy;
   else if (!opLhs->isGlobalVar() and !opRhs->isGlobalVar())
    return store;
  }
  if (llvm::isa<llvm::LoadInst>(Inst)) {
     llvm::LoadInst *LI = llvm::dyn_cast<llvm::LoadInst>(Inst);
     std::vector<Token*> vecLoadIns = extractToken(LI);
     if (!vecLoadIns.empty()) {
       Token* opLhs = vecLoadIns[0];
       Token* opRhs = vecLoadIns[1];
       if (opRhs->isGlobalVar())
	 return copy;
       else if (!opRhs->isGlobalVar())
	 return load;
     }
 }
  return copy;
}

std::vector<int>
LFCPAInstModel::extractRedirections(llvm::GlobalVariable *G) {
  std::vector<int> load{1, 2}, store{2, 1}, copy{1, 1}, assign{1, 0};
  if (llvm::isa<llvm::GlobalVariable>(G))
    return assign;
}

/// handleGEPUtil - Returns the extended field value for a GEP
template <typename GEP>
Token *LFCPAInstModel::handleGEPUtil(GEP *G, Token *Ptr) { 
  if (!Ptr)
    return Ptr;
  Token *FieldVal = new Token(Ptr);
  FieldVal->setIndex(G); 
  FieldVal = this->getTokenWrapper()->getToken(FieldVal);  
  FieldVal->setIndex(G); 
  if (Ptr->getIsAlloca())
     FieldVal->setIsAlloca();  //Set Alloca for new token if prev token was alloca
  return FieldVal;
}

template Token *LFCPAInstModel::handleGEPUtil<llvm::GetElementPtrInst>(
    llvm::GetElementPtrInst *G, Token *Ptr);
template Token *
LFCPAInstModel::handleGEPUtil<llvm::GEPOperator>(llvm::GEPOperator *G,
                                                   Token *Ptr);

template <typename GOP>
bool LFCPAInstModel::isStructFieldPointerTy(GOP *G) { 
	
	llvm::Type *StructType = G->getOperand(0)->getType()->getContainedType(0);
	for (int i = 2; i < G->getNumOperands(); i++) { 
		llvm::Value *IdxV = G->getOperand(i); 
		llvm::ConstantInt *Idx = llvm::dyn_cast<llvm::ConstantInt>(IdxV);
		if (llvm::isa<llvm::StructType>(StructType)) 
			StructType = StructType->getStructElementType(Idx->getSExtValue());
		else if (llvm::isa<llvm::ArrayType>(StructType))
			StructType = StructType->getArrayElementType();		
	}
	 return StructType->isPointerTy();
}

/// Returns true if operand is of array type
template <typename GOP>
bool LFCPAInstModel::isArrayType(GOP *G) {

 llvm::Type *ArrayType = G->getOperand(0)->getType()->getContainedType(0);
 bool flgArr = false;
 
 if (ArrayType->isArrayTy()) {
	return true;
  }

  for (int i = 2; i < G->getNumOperands(); i++) { 
	llvm::Value *IdxV = G->getOperand(i); 
	llvm::ConstantInt *Idx = llvm::dyn_cast<llvm::ConstantInt>(IdxV);
	if (llvm::isa<llvm::StructType>(ArrayType)) {/*case: p->x[0] or ob.x[0]*/
		ArrayType = ArrayType->getStructElementType(Idx->getSExtValue());
  		if (ArrayType->isArrayTy()) 
			return true;
	}
  }
  return false;
}

template bool LFCPAInstModel::isStructFieldPointerTy<llvm::GetElementPtrInst>(llvm::GetElementPtrInst *G);
template bool LFCPAInstModel::isStructFieldPointerTy<llvm::GEPOperator>(llvm::GEPOperator *G);

template bool LFCPAInstModel::isArrayType<llvm::GetElementPtrInst>(llvm::GetElementPtrInst *G);
template bool LFCPAInstModel::isArrayType<llvm::GEPOperator>(llvm::GEPOperator *G);

Token* LFCPAInstModel::extractDummy(std::string S) {
	return (this->getTokenWrapper()->getToken(S, nullptr));
}


//LFCPAInstModel::LFCPAInstModel(){};
LFCPAInstModel::~LFCPAInstModel(){};

bool LFCPAInstModel::isInstSkip(llvm::Instruction *I) {

 for (auto it : InstInfoMap) {
     llvm::Instruction* Ins = it.first;
     if (Ins == I)  
	return  it.second->isSkipInst();
 }
  return false;
}

 void LFCPAInstModel::setSkipIns(llvm::Instruction* I) {
	InstInfo *II = new InstInfo();
        II->setSkipInst();  
	InstInfoMap[I] = II;
 }
} // namespace spatial

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
  	Token* opLhs = handleGEPUtil_1(GOP, this->getTokenWrapper()->getToken(Inst->getPointerOperand()));
	TokenVec.push_back(opLhs);
        llvm::Value *ValOp = Inst->getValueOperand();
	if (!llvm::isa<llvm::ConstantInt>(ValOp))
	    TokenVec.push_back(this->getTokenWrapper()->getToken(ValOp));
    }//end if
    else {
       InstInfo *II = new InstInfo();
       II->setSkipInst();
    }//end else
  }//end outer if
  else if (this->getTokenWrapper()->getToken(Inst->getPointerOperand())->isBasePointerType()) { /* Ignore Stores to non-pointers */
     TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getPointerOperand()));
     llvm::Value *ValOp = Inst->getValueOperand();
     if (!llvm::isa<llvm::ConstantInt>(ValOp))
     	 TokenVec.push_back(this->getTokenWrapper()->getToken(ValOp));
  }
  else {
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
       InstInfo *II = new InstInfo();
       II->setSkipInst();
    }//end else
}//end outer if
else if (this->getTokenWrapper()->getToken(Inst->getPointerOperand())->isBasePointerType()) { /* Ignore load of non-pointers */
     TokenVec.push_back(this->getTokenWrapper()->getToken(Inst));
     TokenVec.push_back(this->getTokenWrapper()->getToken(Inst->getPointerOperand()));     
}
else {
     InstInfo *II = new InstInfo();
     II->setSkipInst();   
}
return TokenVec;	
}

/// extractToken - Returns a vector of alias objects for AllocaInst \Inst
/// operands.
std::vector<Token *> LFCPAInstModel::extractToken(llvm::AllocaInst *Inst) {
  // The operands are returned in the same order as they are present in the
  // instruction example x = alloca op1
  std::vector<Token *> TokenVec;
  Token *Alloca = this->getTokenWrapper()->getToken(Inst);
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

/*   if (Ins->getOperand(0) == NULL)
	llvm::errs()<<"\n Op 0 is NULL";
		
   if (Ins->getOperand(1) == NULL)
	llvm::errs()<<"\n Op 1 is NULL";

//Check if operand value is NULL
  llvm::Constant *constOp0 = llvm::dyn_cast<llvm::Constant>(Ins->getOperand(0));
  llvm::Constant *constOp1 = llvm::cast<llvm::Constant>(Ins->getOperand(1));
  
//  if (constOp0->llvm::Constant::isNullValue())
//	llvm::errs()<<"\n Op 0 is NULL";

  if (constOp1->llvm::Constant::isNullValue())
	llvm::errs()<<"\n Op 1 is NULL";

	//if(constVal->llvm::Constant::isNullValue())
	//	llvm::errs()<<"\n INSTR operand is NULL";

//  if (!constVal->llvm::Constant::isNullValue()) {
  //  }

*/
   for (llvm::Use &U : Ins->operands())  {
	
 	llvm::Value* v = U.get();
//	llvm::errs()<<"\n VALUE= "<<*v;

	I = llvm::dyn_cast<llvm::Instruction>(v);
        q.push(I);

	
	while(!q.empty()) {
	        llvm::Instruction *I = q.front();
        	q.pop();
		 if (llvm::isa<llvm::LoadInst>(I)) {
		    if (llvm::isa<llvm::GlobalVariable>(I->getOperand(0)))    {
		       if (I->getOperand(0)->getType()->getContainedType(0)->isPointerTy())    {
			//Global + Ptr
			llvm::LoadInst *loadI = llvm::dyn_cast<llvm::LoadInst>(I);
		   	llvm::Value *OpVal = loadI->getOperand(0);
		   	TokenVec.push_back(this->getTokenWrapper()->getToken(OpVal));
			InstInfoMap[I]= II;
 	     	       }
	     	       else  {   
			//Global + not a ptr
			InstInfoMap[I]= II;
	               }
                   }//end if
		   else {
			for (llvm::Use &U : I->operands())  {
		 	   llvm::Value* v = U.get();
		//	   llvm::errs()<<"\n VALUE= "<<*v;
			   llvm::Instruction *I1 = llvm::dyn_cast<llvm::Instruction>(v);
		           q.push(I1);
			}
		   }
	    }//end if load
	}//end while	
   }
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
//  auto undef = llvm::UndefValue::get(RetVal->getType()); 

  if (RetVal->getName() == "")  {
	InstInfoMap[Inst] = II;
	auto bit = II->isSkipInst();
  }
  else if (RetVal && !llvm::isa<llvm::ConstantInt>(RetVal)) { 
     Ins = llvm::dyn_cast<llvm::Instruction>(Inst);
     while(!skipFlag) {  
	for (llvm::Use &U : Ins->operands()) { 
	    llvm::Value* v = U.get();
	    I = llvm::dyn_cast<llvm::Instruction>(v); 
	    if (llvm::isa<llvm::LoadInst>(I))
	    { 
		if (llvm::isa<llvm::GlobalVariable>(I->getOperand(0)))	{
		  if (I->getOperand(0)->getType()->getContainedType(0)->isPointerTy())  {
		   	llvm::LoadInst *loadI = llvm::dyn_cast<llvm::LoadInst>(I);
		   	llvm::Value *OpVal = loadI->getOperand(0);
		   	
		   	TokenVec.push_back(this->getTokenWrapper()->getToken(OpVal));
			InstInfoMap[I]= II; //Load global instr is skipped
		   	skipFlag = true;
		    }//end if
		    else  { 
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
LFCPAInstModel::extractToken(llvm::GetElementPtrInst *Inst) {
  // Only provides partial support and returns {op1, op2[idx1]} for op1 = GEP
  // op2 0 idx1

  std::vector<Token *> TokenVec;

  // Check if the operand is a pointer
  if (isStructFieldPointerTy(Inst)) {
	llvm::Function *Func = Inst->getParent()->getParent();
	TokenVec.push_back(this->getTokenWrapper()->getToken(Inst));
	Token* opRhs = handleGEPUtil(Inst, this->getTokenWrapper()->getToken(Inst->getPointerOperand()));
	TokenVec.push_back(opRhs);
   }
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
  std::vector<Token *> TokenVec;
  if (!CI->doesNotReturn()) {
    TokenVec.push_back(this->getTokenWrapper()->getToken(CI));
  }
  return TokenVec;
}

/// extractRedirections - Returns the relative level of redirection based of
/// LHS and RHS on the statement
std::vector<int>
LFCPAInstModel::extractRedirections(llvm::Instruction *Inst) {
  std::vector<int> load{1, 2}, store{2, 1}, copy{1, 1}, assign{1, 0}, temp{2, 0}, gep{1, 0};
  if (llvm::isa<llvm::AllocaInst>(Inst) ||
      llvm::isa<llvm::GetElementPtrInst>(Inst))
      return gep;
   // return assign;
  if (llvm::isa<llvm::StoreInst>(Inst)) {
   llvm::StoreInst *SI = llvm::dyn_cast<llvm::StoreInst>(Inst);
   std::vector<Token*> vecStoreIns = extractToken(SI);
   Token* opLhs = vecStoreIns[0];
   Token* opRhs = vecStoreIns[1];
   if (opLhs->isGlobalVar() and opRhs->isGlobalVar())
	return assign;
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
     Token* opLhs = vecLoadIns[0];
     Token* opRhs = vecLoadIns[1];
     if (opRhs->isGlobalVar())
	return copy;
     else if (!opRhs->isGlobalVar())
	return load;
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
  return FieldVal;
}

Token *LFCPAInstModel::handleGEPUtil_1(llvm::GEPOperator *G, Token *Ptr) {
  if (!Ptr)
    return Ptr;
  Token *FieldVal = new Token(Ptr);
  //FieldVal->setIndex(G);
  FieldVal = this->getTokenWrapper()->getToken(FieldVal);  
  return FieldVal;
}

template Token *LFCPAInstModel::handleGEPUtil<llvm::GetElementPtrInst>(
    llvm::GetElementPtrInst *G, Token *Ptr);
/*template Token *
LFCPAInstModel::handleGEPUtil<llvm::GEPOperator>(llvm::GEPOperator *G,
                                                   Token *Ptr);
*/
template <typename GOP>
bool LFCPAInstModel::isStructFieldPointerTy(GOP *G) {
	long int cntOp = G->getNumOperands();
	llvm::Type* BaseTy = G->getOperand(0)->getType()->getContainedType(0);
        llvm::ConstantInt *CI = llvm::dyn_cast<llvm::ConstantInt>(G->getOperand(cntOp-1));
        auto conVal = CI->getSExtValue();
    	return (BaseTy->getStructElementType(conVal)->isPointerTy());
}

template bool LFCPAInstModel::isStructFieldPointerTy<llvm::GetElementPtrInst>(llvm::GetElementPtrInst *G);
template bool LFCPAInstModel::isStructFieldPointerTy<llvm::GEPOperator>(llvm::GEPOperator *G);


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



















} // namespace spatial

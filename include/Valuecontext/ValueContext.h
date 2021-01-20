#ifndef VALUECONTEXT_H
#define VALUECONTEXT_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "map"
#include "vector"

namespace spatial {

using Context = int;

template <class DataflowValue>
class ValueContext {
   private:
    Context C;
    DataflowValue BI;
    DataflowValue Top;
    std::map<std::pair<llvm::Function*, DataflowValue>, Context>
        DataFlowToContext;
    std::map<Context, DataflowValue> Result;
    std::map<llvm::Function*, std::vector<Context>> FunctionToContexts;
    std::map<Context, std::vector<std::pair<Context, llvm::Instruction*>>>
        ContextGraph;

   public:
    std::map<Context, std::map<llvm::Instruction*, DataflowValue>>
        getDataFlowIn, getDataFlowOut;

    ValueContext(DataflowValue BI, DataflowValue Top);
    DataflowValue getBI();
    DataflowValue getTop();
    std::vector<std::pair<Context, llvm::Instruction*>> getContextChild(
        Context Src);
    int getSavedContext(llvm::Function* Func, DataflowValue BI);
    int initializeContext(llvm::Function* Func, DataflowValue BI);
    void setResult(Context C, DataflowValue Value);
    DataflowValue getResult(Context C);
    void updateContextGraph(Context Src, Context Dest,
                            llvm::Instruction* CallSite);
    std::vector<Context> getContexts(llvm::Function* Func);
};

template <class DataflowValue>
ValueContext<DataflowValue>::ValueContext(DataflowValue BI, DataflowValue Top) {
    this->BI = BI;
    this->Top = Top;
    this->C = 0;
}

template <class DataflowValue>
DataflowValue ValueContext<DataflowValue>::getBI() {
    return BI;
};

template <class DataflowValue>
DataflowValue ValueContext<DataflowValue>::getTop() {
    return Top;
};

template <class DataflowValue>
std::vector<std::pair<Context, llvm::Instruction*>>
ValueContext<DataflowValue>::getContextChild(Context Src) {
    return ContextGraph[Src];
}

template <class DataflowValue>
int ValueContext<DataflowValue>::getSavedContext(llvm::Function* Func,
                                                 DataflowValue BI) {
    if (this->DataFlowToContext.find(std::make_pair(Func, BI)) !=
        this->DataFlowToContext.end()) {
        return this->DataFlowToContext[std::make_pair(Func, BI)];
    }
    return -1;
}

template <class DataflowValue>
int ValueContext<DataflowValue>::initializeContext(llvm::Function* Func,
                                                   DataflowValue BI) {
    DataFlowToContext[std::make_pair(Func, BI)] = this->C;
    this->Result[this->C] = this->getTop();
    int temp = this->C;
    FunctionToContexts[Func].push_back(temp);
    this->C += 1;
    return temp;
}

template <class DataflowValue>
void ValueContext<DataflowValue>::setResult(Context C, DataflowValue Value) {
    this->Result[C] = Value;
}

template <class DataflowValue>
DataflowValue ValueContext<DataflowValue>::getResult(Context C) {
    return this->Result[C];
}

template <class DataflowValue>
void ValueContext<DataflowValue>::updateContextGraph(
    Context Src, Context Dest, llvm::Instruction* CallSite) {
    this->ContextGraph[Dest].push_back(std::make_pair(Src, CallSite));
}

template <class DataflowValue>
std::vector<Context> ValueContext<DataflowValue>::getContexts(
    llvm::Function* Func) {
    return FunctionToContexts[Func];
}

}  // namespace spatial

#endif

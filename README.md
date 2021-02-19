<h1 align="center">SPATIAL: Simple Static Analysis in LLVM</h1>


## Table of Contents

- [Getting Started](#getting-started)
  - [Building from source](#building-from-source)
  - [Using with opt](#using-with-opt)
- [Representing LLVM entities](#representing-llvm-entities)
  - [Representing LLVM instructions](#representing-llvm-instructions)
  - [Representing the operands](#representing-the-operands)
  - [Creating a new token](#creating-a-new-token)
  - [Creating a dummy token](#creating-a-dummy-token)
  - [Extracting directly from instruction](#extracting-directly-from-instruction)
- [Worklist support](#worklist-support)
  - [Creating a worklist](#creating-a-worklist)
  - [Manipulating the worklist](#manipulating-the-worklist)
- [Points-to graph support](#points-to-graph-support)
  - [Inserting based on token info](#inserting-based-on-token-info)
  - [Merging graphs](#merging-graphs)
  - [Retrieving pointee set](#retrieving-pointee-set)
- [Utilities](#utilities)
  - [Getting predecessors and successors](#getting-predecessors-and-successors)
  - [Can the function be analyzed](#can-the-function-be-analyzed)
- [Context sensitivity](#context-sensitivity)
  - [Initialize a value context object](#initialize-a-value-context-object)
  - [Initialize a context](#initialize-a-context)
  - [Manipulate dataflow values](#manipulate-dataflow-values)
  - [Update the context graph](#update-the-context-graph)
  - [Retrieve the saved contexts](#retrieve-the-saved-contexts)
  - [Iterate through the context graph](#iterate-through-the-context-graph)
- [Benchmarking](#benchmarking) 
  - [Initialization](#initialization)
  - [Abstracting information from LLVM IR instructions](#abstracting-information-from-llvm-ir-instructions)
  - [Evaluating the results](#evaluating-the-results)
  - [Printing the results](#printing-the-results)
- [Demo](#demo)
  - [Alias Analysis](#alias-analysis)
  - [Demand Driven Alias Analysis](#demand-driven-alias-analysis)
  
## Getting Started

Spatial is a framework to easily implement analysis over LLVM IR. 

### Building from source
```sh
$ git clone this_repository.git
$ cd this_repository
$ mkdir build; cd build
$ cmake .. && make
$ sudo make install
```

### Using with opt
* Path to shared libary and headers should be searchable by the compiler
* In your LLVM IR pass:
  * Include the required header file, for example, ```spatial/Token/AliasToken.h```
  * Use namespace ```spatial```
* Load libSpatial.so before your pass's shared library
  * ``` opt -load /usr/local/lib/libSpatial.so -load yourPass.so ... ```
  
## Representing LLVM entities

Spatial provides a common API to deal with all the LLVM's entities, for example, instructions, operands, arguments, global variables and etc.  

### Representing LLVM instructions

Spatial represents LLVM instructions by classifying them on the pointer redirection over its operands.   
For example, an instruction `X = *Y` can be represented as `{(X, 1), (Y, 2)}`  
`&X` is represented as `(X, 0)`   
`X` is represented as `(X, 1)`   
`*X` is represented as `(X, 2)`   
and so on  

The analysis writer only needs to think about the analysis at various premutations of the indirections for the operand. This way Spatial allow the analysis writer to only write for one instruction in each category.  

### Representing the operands

Spatial represets each entity as a token. It provides simple and consistent API calls to various utilities, for example,  
`getName()` returns the name of the token  
`isMem()` returns true if the token is a memory location  
more can be found at /lib/Token/Alias.h   

### Creating a new token

Directly creating new tokens from the entities is supported but not recommended until required as it requires to the token bank to avoid duplication of tokens. There are cases where we need to explicitly create a token example GEP instructions.  

```cpp
...
#include "spatial/Token/AliasToken.h"
...
using namespace spatial
...
for(llvm::StoreInst* SI = llvm::dyn_cast<llvm::StoreInst>(Inst)){
  Alias * X = new Alias(SI -> getPointerOperand());
  X = AT.getAliasToken(X);
}
```
AT is an object of AliasTokens class and should be unique to a module. It store all the tokens for a single module getAliasToken returns alias token from AliasTokens either by creating a new one or using the already existing one.  

### Creating a dummy token

Creating of dummy token can be useful in few use cases. Spatial supports generation of dummy token,

```cpp
...
#include "spatial/Token/AliasToken.h"
...
using namespace spatial
...
AT.getAliasToken("?", nullptr) // Creates a dummy alias token with name ? and with global scope
```

### Extracting directly from instruction

Spatial provides a clean way to extract information for an instruction. It will also log a warning for any instruction that are not supported right now.

```cpp
...
#include "spatial/Token/AliasToken.h"
...
using namespace spatial
...
auto AliasVec = AT.extractAliasToken(Inst);
// AT is the object of AliasTokens
// Inst is a pointer to llvm::Instruction
```

## Worklist support

Worklist remains the center of the dataflow analysis. Spatial provides basic support for creating and manipulating worklist at the instruction level. The design does not scale for complex situations, for example, bi-directional analysis; for such cases it is better to implement one on the fly to tailor your needs.  

### Creating a worklist

Now create instruction worklist with instructions, basicblock, module and even function.  

```cpp
...
#include "spatial/include/Worklist/Worklist.h"  
...
// M is a pointer to LLVM Module
spatial::Worklist W(M);
```

### Manipulating the worklist

Spatial allows you to push an instruction, basicblock, module and function into the worklist. It always pops out an instruction.  

## Points-to graph support

Spatial provides in built points-to graph supports and also provide features using other parts of the infrastructure.  

### Inserting based on token info

Spatial provides direct ways to add points-to information derived for each token. `insert(Op1, Op2, R1, R2)` takes `{(X, 1), (Y, 2)}` as `insert(X, Y, 1, 2)` and inserts the required edge. 

### Merging graphs

Flow-sensitive analysis generally merge values along the branch. Spatial's points-to graph implementation provide easy ways to merge points-to graph.  
More details at /spatial/include/AliasGraph.h 

### Retrieving pointee set

Spatial provides two methods to retrieve pointee set, `getPointee(X)` and `getUniquePointee(X)`  

## Utilities

Spatial has spacial utility functions that are frequently used by the analysis writers. More details at /spatial/lib/Utils.cpp

### Getting predecessors and successors

Spatial provides functions to get instruction successors and predecessors.
```cpp
...
#include "spatial/Utils/CFGUtils.h"
...
auto Pred = spatila::GetPred(I);
suto Succ = spatial::GetSucc(I);
```

### Can the function be analyzed

Not all functions are meant to be analyzed, for example, at least the one without a body. Use this utility to skip functions from your analysis.  
```cpp
...
#include "spatial/Utils/CFGUtils.h"
...
bool SkipFunction = spatial::SkipFunction(F);
...
```

## Context sensitivity

Make your analysis context sensitive at ease with Spatial. 

### Initialize a value context object
Initialize the ```ValueContext``` object with the datatype of your dataflow value  
```cpp
ValueContext<AliasMap> VC(BI, Top);
```

### Initialize a context
Initailize a context for a given ```llvm::Function F``` and initial dataflow value ```Initial``` as follows:  
```cpp
Context C = VC.initializeContext(F, Initial);
```

### Manipulate dataflow values
Manipulate data structures storing dataflow values directly through ```getDataFlowIn``` and ```getDataFlowOut```  
```cpp
auto DataflowValue = VC.getDataFlowIn[Context][Instruction];
```

### Update the context graph
You may want to update the context graph after initializing a new context.   
```cpp
VC.updateContextGraph(InitialContext, NewContext, CallSite);
```

### Retrieve the saved contexts
To get the previously saved context for a given ```llvm::Function F``` and initial dataflow value ```Initial``` do as follow:  
```cpp
auto SavedContext = VC.getSavedContext(F, Initial);
```
if the value of ```SavedContext``` is less than 0, implies that this context was not saved previously.   

### Set result for a saved context
When you reach the boundary instruction, you may want to update the result for the context ```C```
```cpp
VC.setResult(C, DataflowResutant);
```

### Iterate through the context graph 
To iterate over all the contexts which invoked this context using a function call
```cpp
for (auto T : VC.getContextChild(C)) {
    // For a context Child which called the context C though callsite Inst
    // T is the pair of Child and Inst
}
```

## Benchmarking

Spatial provides support for analysis benchmarking starting with alias analysis. The present implementation relies on trigger functions, for example, `MAY_ALIAS(a,b)`

### Initialization
Create an instance and use it for extracting benchmark data and evaluations
```cpp
...
#include "spatial/Benchmark/Benchmark.h"
...
using namespace spatial
...
BenchmarkRunner Bench;
```

* ```AT``` is an object of ```AliasTokens``` class and should be unique to a module. It store all the tokens for a single module
* ```getAliasToken``` returns alias token from ```AliasTokens``` either by creating a new one or using the already existing one.

### Abstracting information from LLVM IR instructions
It will react to specific function calls and will extract out information for its arguments.
```cpp
...
#include "spatial/Benchmark/Benchmark.h"
...
using namespace spatial
...
BenchmarkRunner Bench;
// Inst is the pointer to a LLVM Instruction 
auto BenchVars = Bench.extract(Inst); 

if(BenchVars.size() == 2) {
    // We found a specific call we care about
}
```

### Evaluating the results
Use the function evaluate for evaluating the results.
```cpp
...
#include "spatial/Benchmark/Benchmark.h"
...
using namespace spatial
...
BenchmarkRunner Bench;
// Inst is the pointer to a LLVM Instruction 
auto BenchVars = Bench.extract(Inst); 

if(BenchVars.size() == 2) {
    Bench.evaluate(Inst, PointeeSet(BenchVars[0]), PointeeSet(BenchVars[1]));
}
```

### Printing the results
```cpp
std::cout << Bench;
```

## Demo

Spatial stands on the shoulders of extensive experience gained from implementing alias analysis. To demonstrate its usefulness and robustness, we implemented a flow-sensitive and context-sensitive variant of alias analysis and also a demand demand driven variants. These implementations can also be used a reference. 

### Alias Analysis

[Github repo](https://github.com/reSHARMA/AliasAnalysis)

### Demand Driven Alias Analysis

[Github repo](https://github.com/reSHARMA/DemandDrivenAliasAnalysis/)

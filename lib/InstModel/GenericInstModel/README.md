# Generic Instruction Modeling

Tries to model LLVM IR instruction in a way front-end tried to emit them based on the source.  

## List of instructions and corresponding modeling

Instruction | Syntax | Modelling | Remarks
-|-|-|-
`alloca` | `a = alloca Ty` | `a = &a-orig` | a-orig represents the corresponding source variable 
`load` | `a = load b` | `a = *b` | 
`store` | `store a b` | `*b = a` |
`bitcast` | `a = bitcast b` | `a = b` |
`gep` | `a = gep b i1 i2` | `a = &(*b[i1][i2])` |
`ret` | `ret a` | `use a` | TODO: use needs to be implemented through Instruction Info
`br`  | `br a lables` | `use a` | TODO: use needs to be implemented through Instruction Info
`global decl` | `a = global Ty null` | `a = &a-orig` | constant initialized
`global decl` | `a = global Ty b` | `a = &a-orig; *a = b` | variable initialized

TODO: Binary instructions are not yet handled

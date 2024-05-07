## __中间表示__ 版本--CodeGen_llvm_IR
使用 IR 中间件——参见 example.cpp, Function.cpp
### 类继承关系
```
Value
    > Function
    > ConstValue
    > Instruction 
TypeBase
    > IntegerType
    > FloatType
```
*注： `>` 的含义，例如 `Value > Function` 表示 `Function is-a Value` 继承关系*

### 类设计解释
#### Instruction 类
含有 `TypeBase` 原因是在 SSA 中，每条指令实际上指代的是一个 __值__ 
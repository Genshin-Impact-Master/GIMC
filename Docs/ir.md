# 中间表示 版本--CodeGen_llvm_IR
同时编写了测试脚本 testIR.sh
使用 IR 中间件——参见 example.cpp
## 类继承关系
```
Value
    > Module
    > Function
    > ConstValue
    > Instruction 
        > BinaryInst (枚举类型)
            > Add
            > Sub
            > Div
            > Mul
            > Addf
            > Subf
            > Divf
            > Mulf
            > And
            > Or
        > Alloca
        > Store
        > Load
        > Call
        > Ret
        > Icmp
        > Fcmp
        > Br
        > Gep
        > Phi
    > BBlock
TypeBase
    > IntegerType
    > FloatType
    > VoidType
    > PointerType
```
*注： `>` 的含义，例如 `Value > Function` 表示 `Function is-a Value` 继承关系*

## 类设计解释
### Instruction 类
含有 `TypeBase` 原因是在 SSA 中，每条指令实际上指代的是一个 __值__ 
#### def-use 关系
Instruction 中的 `ops_`成员变量就是代表着该 Value Use 的 Value，而此条 Instruction 指代的 Value 就是被 define 的。

## LLVM IR
### LLVM IR Type 
[LLVM IR Type 参考链接](https://llvm.org/docs/LangRef.html#type-system)
*可用于 CodeGen 中的 Type*
#### Integer Type  
iN 表示有 N 个比特的整型
N 可以很大，超过 64，当 N 小于 64 时，采用大于 N 的最大的 Int 比特数对齐；超过 64 时采用 64 bits.
`eg. i7:对齐 = 8，i256:对齐 = 64`
#### Floating-Point Type

|类型 | 解释|
|----|----|
|half|16 bits 浮点类型，5 bits 指数位数，IEEE 754|
|bfloat|16 bits 浮点类型，8 bits 指数位数同 IEEE 单精度浮点数|
|float|32 bits 浮点数，IEEE 754|
|double|64 bits 浮点数，IEEE 754|
|fp128|128 bits 浮点数，IEEE 754|
#### Pointer Type
eg. `ptr addrspace(5)` 表示一个指向 地址 5 的指针
```
                                                                            
   LLVM Data Layout                                                         
 +-------------------------+                                                
 |+-----------------------+|                                                
 ||A：                     ||                                                
 ||存放被 'alloca' 创建的   ||                                                
 ||对象，从 0 开始          ||                                                
 |+-----------------------+|                                                
 |                         |                                                
 |                         |                                                
 |                         |                                                
 |+-----------------------+|                                                
 ||G:                     ||                                                
 ||内存用于存放全局变量     ||                                                
 ||从 0 开始               ||                                                
 |+-----------------------+|                                                
 |+-----------------------+|                                                
 ||P:                     ||                                                
 || 程序内存               ||                                                
 ++-----------------------++                                                 
```
#### Vector Type 用于 SIMD(Single Instruction Multiple Data)
内存中和 Array Type 一样的布局，而当向量的元素为非字节对齐时有一定差异
`<N x iM>` 被 `bitcast` 到一个 `N*M` bits 的 `Integer Type` 剩下的与 `Integer Type` 向内存中存储无差异

*语法*
```llvm
< <# elements> x <elementtype> >          ; Fixed-length vector
< vscale x <# elements> x <elementtype> > ; Scalable vector
```
```llvm
; 例子
<4 x i32> ; 4 个 32bits integer
<vscale x 4 x i32> ; vscale 表示可伸缩向量类型， 此例子可表示 128b 256b 等
```
#### Label Type
label
#### Array Type
```llvm
; Syntax
[<# elements> x <elementtype>]
```
```llvm
; 例子
[2 x [3 x [4 x i16]]] ; 16b int 的 2x3x4 array
```
#### 运行时抢占符
*作用不大...*
`dso_local` 表示在这个编译单元中（Module? 一个文件？）可以直接访问该变量或方程尽管没有在该编译单元里定义。
`dso_preemptable` 默认情况开启，表明方程或变量在运行时可能被外部的连接单元替代。

### LLVM IR Instruction
LLVM IR 指令 [参考链接](https://llvm.org/docs/LangRef.html#instruction-reference)
#### 部分二元操作
**and** 指令
为位运算 &
```llvm
<result> = and <ty> <op1>, <op2>   ; yields ty:result
```
注意 type 可以 i32
**or** 指令
为位运算 |
```llvm
<result> = or <ty> <op1>, <op2>   ; yields ty:result
```
注意 type 可以是 i32，不一定必须 i1
**srem** 指令
整数 符号求余操作
```llvm
<result> = srem <ty> <op1>, <op2>   ; yields ty:result
```
返回一个除法的 "remainder"（余数）
```llvm
;eg
<result> = srem i32 4, %var          ; yields i32:result = 4 % %var
```

**frem** 指令
```llvm
<result> = frem [fast-math flags]* <ty> <op1>, <op2>   ; yields ty:result
```
执行浮点数求余 fmod.(GIMC 中应该不用实现，浮点数进行 % 应当会发生类型转换)
```llvm
<result> = frem float 4.0, %var          ; yields float:result = 4.0 % %var
```
#### Terminator Instruction 终结指令（基本块的结尾）
终结指令产生的为 control flow 而非 value
__ret__ 指令
```llvm
ret <type> <value>       ; Return a value from a non-void function
ret void                 ; Return from void function
```
```llvm
; eg.
ret i32 5                       ; Return an integer value of 5
ret void                        ; Return from a void function
ret { i32, i8 } { i32 4, i8 2 } ; Return a struct of values 4 and 2
```
__br__ 指令
```llvm
br i1 <cond>, label <iftrue>, label <iffalse>
br label <dest>          ; Unconditional branch
```
```llvm
Test:
  %cond = icmp eq i32 %a, %b
  br i1 %cond, label %IfEqual, label %IfUnequal
IfEqual:
  ret i32 1
IfUnequal:
  ret i32 0
```
__callbr__ 指令
调用方程的指令，语法有删减
```llvm
<result> = callbr <ty>|<fnty> <fnptrval>(<function args>) [fn attrs]
              [operand bundles] to label <fallthrough label> [indirect labels]
```

#### Memory Access & Addressing Operations
__alloca__ 指令
```llvm
<result> = alloca [inalloca] <type> [, <ty> <NumElements>] [, align <alignment>] [, addrspace(<num>)]     ; yields type addrspace(num)*:result
```
分配（函数栈空间）内存，返回内存指针，内存并未被初始化。
```llvm
例子
%ptr = alloca i32                             ; yields ptr
%ptr = alloca i32, i32 4                      ; yields ptr i32 类型数组，长度为 4
%ptr = alloca i32, i32 4, align 1024          ; yields ptr 数组长度 4，内存地址需要为 1024 整数倍
%ptr = alloca i32, align 1024                 ; yields ptr
```
__load__ 指令
```llvm
例子
%ptr = alloca i32                               ; yields ptr
store i32 3, ptr %ptr                           ; yields void
%val = load i32, ptr %ptr                       ; yields i32:val = i32 3
```
__store__ 指令
删减后的语法
```llvm
store <ty> <value>, ptr <pointer>
``` 
__getelementptr__ 指令
用于获得数组某个子元素的地址。
```llvm
<result> = getelementptr inbounds <ty>, ptr <ptrval>{, <ty> <idx>}*
```
```llvm
; 例子
  %c = alloca [2 x [3 x [4 x i32]]], align 16
  %arrayidx1 = getelementptr inbounds [2 x [3 x [4 x i32]]], ptr %c, i64 0, i64 0
  %arrayidx2 = getelementptr inbounds [3 x [4 x i32]], ptr %arrayidx1, i64 0, i64 1
  %arrayidx3 = getelementptr inbounds [4 x i32], ptr %arrayidx2, i64 0, i64 2
```
第一个 i64 后面的数似乎必须取 0

#### 其他指令
__icmp__ 指令
```llvm
<result> = icmp <cond> <ty> <op1>, <op2>   ; yields i1 or <N x i1>:result
```
`<cond>` 表示进行哪种类型的比较
```llvm
eq: equal
ne: not equal
ugt: unsigned greater than
uge: unsigned greater or equal
ult: unsigned less than
ule: unsigned less or equal
sgt: signed greater than
sge: signed greater or equal
slt: signed less than
sle: signed less or equal
```
被比较的两个参数必须为同一个类型，整型 or 指针
例子：
```llvm
<result> = icmp eq i32 4, 5          ; yields: result=false
<result> = icmp ne ptr %X, %X        ; yields: result=false
<result> = icmp ult i16  4, 5        ; yields: result=true
<result> = icmp sgt i16  4, 5        ; yields: result=false
<result> = icmp ule i16 -4, 5        ; yields: result=false
<result> = icmp sge i16  4, 5        ; yields: result=false
```
**fcmp** 指令
```llvm
<result> = fcmp [fast-math flags]* <cond> <ty> <op1>, <op2>     ; yields i1 or <N x i1>:result
```
`cond` 类型（节选）
```llvm
oeq: ordered and equal

ogt: ordered and greater than

oge: ordered and greater than or equal

olt: ordered and less than

ole: ordered and less than or equal

one: ordered and not equal
```
ordered 的含义为 两个操作数均非 QNAN（Quiet NAN）和 SNAN（Singaling NAN）。QNAN 与 SNAN 的不同之处在于，QNAN 的尾数部分最高位定义为 1，SNAN 最高位定义为 0；QNAN 一般表示未定义的算术运算结果，最常见的莫过于除 0 运算；SNAN 一般被用于标记未初始化的值，以此来捕获异常。

**zext to** 指令
零拓展
```llvm
<result> = zext <ty> <value> to <ty2>             ; yields ty2
```
```llvm
; eg
%X = zext i32 257 to i64              ; yields i64:257
%Y = zext i1 true to i32              ; yields i32:1
```

**Phi** 指令
向 SSA 中插入 phi 结点，必须插入在基本块的所有其他指令前。
语法
```llvm
<result> = phi [fast-math-flags] <ty> [ <val0>, <label0>], ...
```
例子
```llvm
Loop:       ; Infinite loop that counts from 0 on up...
  %indvar = phi i32 [ 0, %LoopHeader ], [ %nextindvar, %Loop ]
  %nextindvar = add i32 %indvar, 1
  br label %Loop
```

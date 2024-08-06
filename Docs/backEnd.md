*说明：文档中没有加 LIR 前缀的均为中端数据结构*

#### LirModule
[LirModule](../include/LIR/visitor/LirModule.h)
`LirModule` 类，为中端 IR 的简单映射，同样包含 `GlobalVars`,`FunctionDefs`, 但是没有 `FunctionDeclares` ？其函数的定义与声明在汇编层面为何有此区别？
> 汇编中 Call 某个函数直接使用 bl + \<label\> 即可，即只需要 FunctionDeclares 的函数名，不需要带有其他信息（但其他信息在构建 LIR 中的 `LIRCall` 会用到）。

#### LirFunction
[LirFunction](../include/LIR/visitor/LirFunction.h)
`LirFunction` 类，包含参数（但是这里会考虑到实际的寄存器数量的限制）,局部变量的栈空间大小 `stackSize`。

##### LirFunction 重要变量
`stackSize`：函数的栈变量空间大小，只可能为 一部分 或 三部分 组成。（在没有溢出形参时只需考虑局部变量）
  1. 溢出到栈中的形参（超过了预留的形参寄存器上限）
  2. 局部变量
  3. 为 push {r7, lr} 预留的空间（其中，如果本 LirFunction 没有调用 call 指令，不必 push lr，但迫于时间，先统一 push）

`immMap<LirOperand, LirInstMove>` : todo
`stackOffsetMap<Value*, >`：临时变量，`alloca` 产生的局部变量对应的栈上偏移。


#### LirInst
Lir 中的指令，与中端 IR 类似，包含有：
  * 所属基本块： `LirBlock *parent`
  * 指令的类型： `LirInstKind lirKind`
  * 侵入式链表结点 `INode<LirInst>`

**LirBinary**

#### LirOperand
Lir 中的操作数，有如下的几种类型

**Addr**
arm 中的地址标签

**Reg**
arm 中实际会分配的寄存器
  * **IVReg**
    虚拟整数寄存器，由于无限寄存器假设，故从零开始编号.(不过是否是不同 Function 可以同号？)
  * **FVReg**
    虚拟浮点寄存器
  * **IPhyReg**
    未知
  * **FPhyReg**
    未知

**Imm**
float 立即数与 int 立即数
  * **IImm**
    int 立即数
  * **FImm**
    float 立即数

#### ToLir
实现了从 SSA IR 到 LIR 的转换。

以下变量为 ToLir 转换所需的工具
* `valMap` 包含 IR 值到 `LirOperand` 的映射，即将 IR reg 变到 LIR reg。
* `funcMap` IR 函数到 LIR 函数的映射
* `blockMap` IR 基本块到 LIR 基本块的映射
* `globalMap` IR 全局变量到 `LirOperand` 的映射

`operandResolve` 函数：
将 `operand` 解析为 `Imm` 或 `Reg`
  * 对于 `ConstValue`,解析为 `Imm`
  * 对于浮点类型的 `Value`，解析为 `FVReg`，（因为指针也使用通用寄存器的缘故）

##### moduleGen
`moduleGen` 函数：
  * 对于全局变量，新建一个地址（`Reg` 类型为 `Addr`）即可，例如一个全局变量 `a`，它被用到时直接用 `move` 放到寄存器即可。
  * 对于 `Function`
    * 函数形参的处理：可以考虑拿一部分整数和浮点寄存器出来（4,16 个为上限）存放形参，剩下的放入栈中。
    * 函数体的处理（即每条指令的处理）
  * 对于 `BBlock`
    * 每个基本块需要将其中的局部变量清空。（因为从数据流的哪一方来的不确定，不能严格地说某个虚拟寄存器中的值一定为栈中变量的值。*PS：引入 **Phi** 或许也是想根据数据流选择其他 BBLock 的寄存器*）

对于每类中端指令的处理：
**二元运算指令**
相应的 LIR 数据结构为 `LirBinary`

以 `Add` 指令为例子：
  * 判断左操作数是否为常数，否则左右换位（由于 armv7 要求左操作数必须为寄存器）【是否应该考虑左右两边均为常数的情况？】
  * 将左右 `Value` 解析为两个操作数，`Add` 指令本身作为目的操作数。
  * 最后创建二元运算指令，将指令加入 `LirBlock` 的侵入式链表中。

**Alloca**
LIR 实际上不需要这条指令了。

`alloca` 指令分配了一片内存空间，内存空间的首地址为其 `ptr` （实际上是通过 `alloca` 重建符号表的过程），它当然不属于一个会被分配寄存器的值。（只有 `load` 才能将内存空间的值取出来，实际分配为 `reg`）

如此一来，只需要在 `LirFunction` （因为栈偏移是函数的一个成员变量）中维护一个 `<Value*, IImm>` 的映射 [stackOffsetMap](#LirFunction-重要变量)，因为后续的 `store` 和 `load` 操作均为访存操作。只需要获得在栈上的位置即可。

**Store**
相应 LIR 数据结构为 `LirStore` 可以平滑翻译到 `ldr` 指令。即将 `Reg` 的值复制到栈内存。

**Load**
相应 LIR 数据结构为 `LirLoad` 平滑翻译到 `str` 指令，即将栈内存值复制到 `Reg`

**Call**
相应 LIR 数据结构为 `LirCall`

`Call` 的实际处理：中端中 `Call` 是对于函数的调用，需要处理参数的传递，根据所调用的 `Function` 的参数数目，将其存入参数寄存器或栈空间。
对于 arm 汇编，我们需要将参数存入预定好的几个寄存器中，参数超过寄存器上限时溢出到栈中。
那么在 LIR 中，一条中端 `Call` 指令会产生 n 个 `Reg`，其中 n 为形参个数，显然，在 `LirCall` 也必须包含调用的 `Function` 的名字（只需要函数名即可）。

**Ret**
arm 汇编中为函数的退出操作，考虑到可能有多个 Ret 的情况，遵循这样的原则：进入函数 push 了哪些，出函数就要 pop 哪些寄存器。
  * lr 除外，对于 lr 压栈的情况，需要将函数开始时 push 进 lr 的值 pop 到 pc
  * 如果没有 push lr，则说明本函数中途没有用到 `Call` 指令，lr 寄存器一般为保留，故而 lr 为上一个函数的值。（现在默认会 push lr，不考虑这种情况）

在中端 IR 中，`Ret` 语句还会具有返回值，在 arm 汇编中返回值被放在 r0 寄存器，故 LIR 只需要记录返回值的 `Reg` 即可。

**Icmp** 与 **Fcmp**
在 arm 汇编中，`cmp r, op2` 语句是将 `r` - `op2` 的结果存到 CSPR 状态寄存器中。
则 LIR 需要的即为两个输入 `Reg`。无输出 `Reg`。（实际上为状态寄存器）

**Br**
中端中的 `Br` 包含了有条件跳转与无条件跳转，相应的 LIR 数据结构为 `LirBr`.

对不同的 CMP KIND（均为有符号相比）有相应状态 `<cond>` :EQ，GT，GE，LT，LE，NE.

在 arm 汇编中，有条件跳转是两条 arm 指令 `b<cond> + <label>(false)` 和 `b + <label>(true)`。无条件跳转即为 `b + <label>`

在 LIR 中，我们只需要将 Br 加入指令集，且保证使用 Br 的有条件跳转之前的那条指令，一定是一条 `cmp` 指令（这个在 IR 中也应当保证，优化时不能改变其顺序）

**GEP**
中端 IR 中的 GEP 指令就是将数组降低维数，放在 arm 汇编中就是 `offset * 该维度 length`. llvm 中的 GEP 指令让人摸不着头脑。现在考察我们的 GEP 指令。
* `is_param` 参数表示是否为形参。
  * `true`: GEP 指令对应的 `baseTypePtr` 是其所取数组，// todo
  * `false`: GEP 指令对应的 `baseTypePtr` 是其所取数组的基类，在 [example.cpp](../IR/example.cpp) 中的 eg.6 中，局部变量 eg6_c_ptr 是指向 4 * 2 个 int 区域大小的指针。（则它 getType().getSize() 返回的大小为 8 * 4 B）
实践中出真知，等开始测验时再 debug 看看到底如何偏移。

在 LIR 中，假设我们在 GEP 指令中得到了
  1. **形参** 的指针 `ptr` 及其偏移量 `offset`
    * 容易得知此 `ptr` 由于其指向的内存不是在本函数内生成的（区别于局部变量），所以便没有一个映射表，而是要将此 `ptr` 的实际值存入 `Reg` 中，将其与 `offset` 相加，则又得到一个最终的 `Reg`
  2. **局部变量** 的指针 `ptr` 及其偏移量 `offset`
    * 根据 `LirFunction` 中的 `stackOffsetMap` 获得变量在函数中的栈偏移值 `varOffset`，存入 `Reg`，并与 `offset` 值相加存入最终 `Reg`。
  3. **全局变量** 的指针 `ptr` 及其偏移量 `offset`
    * 首先将标签值 `ptr` 存入 `Reg`,将其与 `offset` 相加得到最终的 `Reg`

**Fp2Int** 与 **Int2Fp** 与 **Zext**
// todo

**InitMem**
此条是为了方便转换使用的将数组置为零的指令，

### Arm 汇编
`vldr` 指令，从文本池中加载任何 64 位整数、单精度或双精度浮点值。
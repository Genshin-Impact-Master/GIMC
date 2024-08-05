#### LirModule
[LirModule]((../include/LIR/visitor/LirModule.h))
`LirModule` 类，为中端 IR 的简单映射，同样包含 `GlobalVars`,`FunctionDefs`, 但是没有 `FunctionDeclares` ？其函数的定义与声明在汇编层面为何有此区别？
> 汇编中 Call 某个函数直接使用 bl 即可，不需要带有其他信息。故而 FunctionDeclares 可以直接忽略

#### LirFunction
[LirFunction](../include/LIR/visitor/LirFunction.h)
`LirFunction` 类，包含参数（但是这里会考虑到实际的寄存器数量的限制）,局部变量的栈空间大小 `stackSize`。

##### LirFunction 重要变量
`immMap<LirOperand, LirInstMove>` : todo
`stackOffsetMap<Value*, >`：临时变量，`alloca` 产生的局部变量对应的栈上偏移


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
* `valMap` 包含 IR 值到 `LirOperand` 的映射
* `funcMap` IR 函数到 LIR 函数的映射
* `blockMap` IR 基本块到 LIR 基本块的映射
* `globalMap` IR 全局变量到 `LirOperand` 的映射

`operandResolve` 函数：
将 `operand` 解析为 `Imm` 或 `Reg`
  * 对于 `ConstValue`,解析为 `Imm`
  * 对于浮点类型的 `Value`，解析为 `FVReg`，（因为指针也使用通用寄存器的缘故）

`moduleGen` 函数：
  * 对于全局变量，新建一个地址（`Reg` 类型为 `Addr`）即可，例如一个全局变量 `a`，它被用到时直接用 `move` 放到寄存器即可。
  * 对于 `Function`
    * 函数形参的处理：可以考虑拿一部分整数和浮点寄存器出来（4,16 个为上限）存放形参。
    * 函数体的处理（即每条指令的处理）

对于每类中端指令的处理：
**二元运算指令**
相应的 LIR 数据结构为 `LirBinary`

以 `Add` 指令为例子：
  * 判断左操作数是否为常数，否则左右换位（由于 armv7 要求左操作数必须为寄存器）【是否应该考虑左右两边均为常数的情况？】
  * 将左右 `Value` 解析为两个操作数，`Add` 指令本身作为目的操作数。
  * 最后创建二元运算指令，将指令加入 `LirBlock` 的侵入式链表中。

**Alloca**
相应的 LIR 数据结构为 `LirAlloca`

`alloca` 指令分配了一片内存空间，内存空间的首地址为其 `ptr` （实际上是通过 `alloca` 重建符号表的过程），它当然不属于一个会被分配寄存器的值。（只有 `load` 才能将内存空间的值取出来，实际分配为 `reg`）

如此一来，只需要在 `LirFunction` （因为栈偏移是函数的一个成员变量）中维护一个 `<Value*, IImm>` 的映射 [stackOffsetMap](#LirFunction-重要变量)，因为后续的 `store` 和 `load` 操作均为访存操作。只需要获得在栈上的位置即可。

**Store**
相应 LIR 数据结构为 `LirStore`

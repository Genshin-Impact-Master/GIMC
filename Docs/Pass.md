## 优化相关
### mem2reg & phi 指令
[优化参考阅读](https://buaa-se-compiling.github.io/miniSysY-tutorial/challenge/mem2reg/help.html)

SSA Value 中 def-use,use-def 通过双向引用来维护，维护该双向引用的数据结构叫 "Use"

#### 求 CFG 的支配树
* **前驱后继结点**[(Pres_Succs_Calculate.h)](../include/Pass/Pres_Succs_Calculate.h)
为 BBlock 类型添加 pres 向量与 succs 向量（表示其前驱和后继）
为每个基本块额外添加一个 exit 结点。（？需要吗？）
* **每个结点支配集计算**
  * 直白算法：
    > dom = {}
    while dom is changing:
    $\quad$for vertex in CFG:
    $\quad\quad$$dom[vertex]$ $=$ ${vertex}$ $\;\cup\;\cdot\cap(dom[p]\;|\;for\; p \;in\; vertex.pres)$
  * [Lengauer-Tarjan 算法原文](https://dl.acm.org/doi/pdf/10.1145/357062.357071)
  [算法解读](https://www.cnblogs.com/meowww/p/6475952.html)

#### mem2reg 算法
参考 [北航编译原理实验](https://buaa-se-compiling.github.io/miniSysY-tutorial/challenge/mem2reg/help.html)
注意：由于 mem2reg 优化删除了 alloca,load,store 指令，（考虑到后续优化一定有对 Instruction 删除的情况），在 Value 中设置一 bool 值表示其是否有效。

### GVN(Global Value Numbering) 全局值编号
[预测全局值编号的稀疏算法](https://dl.acm.org/doi/10.1145/543552.512536)
我们果断选择 Brutal Force.


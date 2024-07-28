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

### 公共子表达式消除

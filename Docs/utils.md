## Utilities 工具包
### ErrorConfig.h 差错处理头文件
@todo 负责一些差错处理
### 侵入式链表
**为什么要采用侵入式链表？**

// 借鉴 22 年萝杨空队解释
* 在对于 Instructions 进行迭代时，因为需要进行删减操作，如果直接使用 vector，其内置迭代器对修改敏感。(但似乎普通的链表也能做到)
* 还有一个好处是，可以直接通过 Instruction，就可以得到在链表中的位置

**侵入式链表简述**
[参考链接](http://t.csdnimg.cn/pScaX)
简单而言，就是将链接域的指针所存放的数据，从**整个结构体**的地址，转换为存放**链接域**地址
```c
// 存放链接域的结点
struct INode {
  struct INode *next;
  Node *owner;
};

// 整个结构体
typedef struct Node {
  Data data;            // 数据信息
  struct INode iNode;   // 链接域结点 
} Node;

// 侵入式链表
struct IList {
  struct INode *rear;   // 链表尾部
  struct INode head;    // 头结点
};
```
如此一来，迭代的就是链接域结点，那么如何通过结点得到整个数据结构的地址呢？
* 解决方案：通过向链接域结点中添加 `struct Node` 的地址，作为其变量来获得。

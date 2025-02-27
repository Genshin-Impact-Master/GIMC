#include "../include/IR/Function.h"
#include "../include/IR/BBlock.h"     // @C++_Learn 由于 Function，BBlock 类中均使用了对方的函数，include 两个头文件
USING_GIMC_NAMESPACE

//@C++_Learn 会隐式地调用没有指定初始化值的变量（bBlocks）的默认构造函数
Function::Function(const std::string &fName, baseTypePtr funcType, std::vector<baseTypePtr> &arguTypes)
                  : Value(fName, funcType), arguTypes_(arguTypes), blkList_(IList<Function, BBlock>(this)) , exit_(new BBlock("exit_", voidType, this)) {
                    this->setFunctionPrefix();
                    for (auto ty : arguTypes_) {
                      Value val = Value(std::to_string(getCnt()), ty);
                      argus_.push_back(val);
                    }
                  }

void Function::clearFunc() { 
  INode<BBlock> *blkNode = blkList_.getHeadPtr();
  while (!blkNode->isEnd()) {
    blkNode = blkNode->getNext();
    BBlock *blk = blkNode->getOwner();
    blk->clearBBlock();
  }
  blkList_.clear();
}

void Function::addBBlock(BBlock* bBlk) {
  if (blkList_.getSize() == 0) {
    setEntry(bBlk);
  }
  blkList_.append(bBlk->getNode());
}

#ifdef PRINT_CFG
void Function::drawCFG() {
  GVC_t *gvc;
  // 建立 graphviz 上下文
  gvc = gvContext();

  Agraph_t *funcGraph;
  // 参数为 图的名称，图的类型 (Agdriected 有向图，Agundirected 无向图...)，第三个参数为修改 Cgraph 默认表现，可填 null
  // Agstrictdirected 表示为没有重复边的有向图
  funcGraph = agopen(getName().data(), Agstrictdirected, nullptr);
  INode<BBlock> *nodeBBlk = getBBlockList().getHeadPtr();

  // 首先创立所有结点，包括 exit_，不要 exit_ 也可
  while (!nodeBBlk->isEnd()) {
    nodeBBlk = nodeBBlk->getNext();
    BBlock *bBlk = nodeBBlk->getOwner();
    Agnode_t *n;
    n = agnode(funcGraph, bBlk->getName().data(), true);             // true 表示若结点不存在则新建（按照名字查找）
  }
  // Agnode_t *n = agnode(funcGraph, getExitBBlock()->getName().data(), true);

  nodeBBlk = getBBlockList().getHeadPtr();

  // 对每个结点，将其后继结点边画出
  while (!nodeBBlk->isEnd()) {
    nodeBBlk = nodeBBlk->getNext();
    BBlock *bBlk = nodeBBlk->getOwner();
    Agnode_t *n = agnode(funcGraph, bBlk->getName().data(), false);  // false 表示找不到结点则返回 null
    std::unordered_set<BBlock*> &pres = bBlk->getPres();
    std::set<BBlock*> &succs = bBlk->getSuccs();
    if (!succs.empty()) {
      for (const auto &succ : succs) {
        Agnode_t *m = agnode(funcGraph, succ->getName().data(), false);
        Agedge_t *e;
        e = agedge(funcGraph, n, m, nullptr, true);
      }
    }

    // 实际上只用把所有 BBlock 的 succs 画出来，就将整个图画出来了
    // if (!pres.empty()) {
    //   for (const auto &pre : pres) {
    //     Agnode_t *m = agnode(funcGraph, pre->getName().data(), false);
    //     Agedge_t *e;
    //     e = agedge(funcGraph, m, n, nullptr, true);
    //   }
    // }
  } 
    // 利用 layout engine 计算布局
  gvLayout(gvc, funcGraph, "dot");

  // 渲染图并保存到文件
  gvRenderFilename(gvc, funcGraph, "png", (getName() + ".png").c_str());

  // 释放资源
  gvFreeLayout(gvc, funcGraph);
  agclose(funcGraph);
  gvFreeContext(gvc);
}
#endif

void Function::correctCheck() {
  INode<BBlock> *node = blkList_.getHeadPtr();
  if (blkList_.isEmpty()) {
    error("一个函数中至少含有一个基本块");
  }
  if (entry_->getName().compare("entry") != 0 || node->getNext()->getOwner() != entry_) {
    error("函数的入口基本块名称必须是 entry 且需要在侵入式链表的第一个结点");
  }
  // 首先将每个 BBlock 的 pres 和 succs 清空
  while (!node->isEnd()) {
    node = node->getNext();
    BBlock *bBlk = node->getOwner();
    bBlk->getSuccs().clear();
    bBlk->getPres().clear();
  }
  node = blkList_.getHeadPtr();
  while (!node->isEnd()) {
    node = node->getNext();
    BBlock *bBlk = node->getOwner();
    bBlk->correctCheck();
  }
}
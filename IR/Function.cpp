#include "../include/IR/Function.h"
#include "../include/IR/BBlock.h"     // @C++_Learn 由于 Function，BBlock 类中均使用了对方的函数，include 两个头文件
USING_GIMC_NAMESPACE

//@C++_Learn 会隐式地调用没有指定初始化值的变量（bBlocks）的默认构造函数
Function::Function(const std::string &fName, baseTypePtr funcType, std::vector<baseTypePtr> &arguTypes)
                  : Value(fName, funcType), arguTypes_(arguTypes), blkList_(IList<Function, BBlock>(this)) {
                    this->setLocalPrefix(false);
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
  blkList_.append(bBlk->getNode());
}
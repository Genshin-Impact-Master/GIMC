#include "../include/IR/BBlock.h"
#include "../include/IR/Inst.h"
#include <iostream>

USING_GIMC_NAMESPACE


BBlock::BBlock(const std::string &name, baseTypePtr type, Function *parent) :
                Value(name, type), parent_(parent), instList_(IList<BBlock, Instruction>(this)), blkNode_(INode<BBlock>(nullptr, nullptr, this)) {}
 
BBlock::BBlock(Function *parent) 
              : BBlock(std::to_string(parent->getCnt()), voidType, parent){}

void BBlock::clearBBlock() {
  instList_.clear();
}


void BBlock::addInst(Instruction* inst) {
  instList_.append(inst->getNode());
}

void BBlock::addHeadInst(Instruction *inst) {
  instList_.add2Head(inst->getNode());
}

void BBlock::rmInst(Instruction *inst) {
  instList_.remove(inst->getNode());
  inst->setValid(false);
}

void BBlock::coutBBlock() {
  std::cout << this->getName() << ":" << std::endl;
  INode<Instruction> *node = instList_.getHeadPtr(); 
  while (!node->isEnd()) {
    node = node->getNext();
    Instruction *inst = node->getOwner();
    std::cout << ST_Insts[static_cast<int>(inst->getKind())] << " " << inst->getFullName() << " and it's ops:";
    for (auto v : inst->getDefs()) {
      std::cout << v->getFullName();
    }
    std::cout << std::endl;
  }
}

void BBlock::correctCheck() {
  INode<Instruction> *node = instList_.getHeadPtr();
  node = instList_.getRearPtr();
  if (instList_.isEmpty()) {
    addInst(new Ret(std::to_string(parent_->getCnt()), voidType, this, &voidValue));
    std::cout << "BBlock 至少包含一条跳转指令 Ret || Br，已自动添加 ret void\n";
  }
  Instruction *terminator = instList_.getRearPtr()->getOwner();
  // 基本块末尾必须是 ret 或 br 指令
  Br *branch = dynamic_cast<Br*>(terminator);
  if (branch) {
    // 说明为 Br 指令
    // 判断是否为无条件跳转指令
    if (branch->isUnconditional()) {
      BBlock *ifTrue = branch->getTrueBBlk();
      BBlock::addEdge(this, ifTrue);
    }
    else {
      BBlock *ifTrue = branch->getTrueBBlk();
      BBlock *ifFalse = branch->getFalseBBlk();
      BBlock::addEdge(this, ifTrue);
      BBlock::addEdge(this, ifFalse);
    }
  }
  else {
    // 说明为 Ret 指令
    Ret *ret = dynamic_cast<Ret*>(terminator);
    if (!ret) {
      addInst(new Ret(std::to_string(parent_->getCnt()), voidType, this, &voidValue));
      std::cout << "Warning : BBlock 最后一条指令只能为跳转指令 Ret || Br，默认处理为添加 ret void" << std::endl;
    }
    // ret 指令没有 succs
  }
  while (!node->isEnd()) {
    node = node->getNext();
    Instruction *inst = node->getOwner();
    inst->correctCheck();    
  }
}
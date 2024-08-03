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
  if (instList_.isEmpty())
    error("BBlock 至少包含一条跳转指令 Ret || Br");
  Instruction *inst = node->getOwner();
  // 基本块末尾必须是 ret 或 br 指令
  if (!dynamic_cast<Br*>(inst) && !dynamic_cast<Ret*>(inst))
    error("BBlock 最后一条指令只能为跳转指令 Ret || Br");
  while (!node->isEnd()) {
    node = node->getNext();
    Instruction *inst = node->getOwner();
    inst->correctCheck();    
  }
}
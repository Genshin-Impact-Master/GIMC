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
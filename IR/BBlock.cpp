#include "../include/IR/BBlock.h"
#include "../include/IR/Inst.h"

USING_GIMC_NAMESPACE


BBlock::BBlock(const std::string &name, baseTypePtr type, Function *parent) :
                Value(name, type), parent_(parent), instList_(IList<BBlock, Instruction>(this)), blkNode_(INode<BBlock>(nullptr, this)) {}
 
BBlock::BBlock(Function *parent) 
              : BBlock(std::to_string(parent->getCnt()), voidType, parent){}

void BBlock::clearBBlock() {
  instList_.clear();
}


void BBlock::addInst(Instruction* inst) {
  instList_.append(inst->getNode());
}
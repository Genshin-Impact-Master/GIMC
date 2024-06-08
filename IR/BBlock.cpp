#include "../include/IR/BBlock.h"
#include "../include/IR/Inst.h"

USING_GIMC_NAMESPACE


BBlock::BBlock(const std::string &name, baseTypePtr type, Function *parent) :
                Value(name, type), parent_(parent) {}
 
BBlock::BBlock(Function *parent) 
              : BBlock(std::to_string(parent->getCnt()), voidTyPtr, parent){}

void BBlock::clearBBlock() {
  for (auto inst : instructions_) {
    delete inst;
  }
  instructions_.clear();
}
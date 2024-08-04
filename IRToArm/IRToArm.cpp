#include "../include/IRToArm/IRToArm.h"
#include "../include/IR/Inst.h"

USING_GIMC_NAMESPACE

void IRToArm::genModule() {
  // 准备工作
  smartOut(".arch", "armv7");
  smartOut(".fpu", "softvfp");
  smartOut(".text");
  smartOut(".align", 1);


}

void IRToArm::genFunction(Function *func) {

}

void IRToArm::genBBlock(BBlock *bBlk) {
  
}

int getStackSize(Function *func) {
  int cnt = 0;
  INode<BBlock> *bBlkNode = func->getBBlockList().getHeadPtr();
  while (!bBlkNode->isEnd()) {
    bBlkNode = bBlkNode->getNext();
    BBlock *bBlk = bBlkNode->getOwner();
    INode<Instruction> *instNode = bBlk->getInstList();
    while (!instNode->isEnd()) {
      instNode = instNode->getNext();
      Instruction *inst = instNode->getOwner();
      if (inst->getKind() == InstKind::Alloca) {
        baseTypePtr ty = inst->getType();
        // 由于 Alloca 指令创建的一定为指针，故其取到的为所指空间大小
        cnt += alignsTo(space, STACK_ALIGN);
      }
    }
  }
}
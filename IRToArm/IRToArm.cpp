#include "../include/IRToArm/IRToArm.h"
#include "../include/IR/Inst.h"

USING_GIMC_NAMESPACE

void IRToArm::genModule() {
  // 准备工作
  smartOut(".arch", "armv7");
  smartOut(".fpu", "softvfp");
}

void IRToArm::genFunction(Function *func) {
  std::string &name = func->getName();
  smartOut(".text");
  smartOut(".align", 3);
  smartOut(".global", name);
  smartOut(".syntax", "unified");
  smartOut(".thumb");
  smartOut(".thumb_func");
  smartOut(".type", name, "\%function");
  
  // @C++_Learn 两字符串比较
  if (name.compare("main") == 0) {

  }
}

void IRToArm::genBBlock(BBlock *bBlk) {
  
}

int IRToArm::getStackSize(Function *func) {
  int cnt = 0;
  INode<BBlock> *bBlkNode = func->getBBlockList().getHeadPtr();

  // 处理指令偏移
  while (!bBlkNode->isEnd()) {
    bBlkNode = bBlkNode->getNext();
    BBlock *bBlk = bBlkNode->getOwner();
    INode<Instruction> *instNode = bBlk->getInstList();
    while (!instNode->isEnd()) {
      instNode = instNode->getNext();
      Instruction *inst = instNode->getOwner();
      if (inst->getKind() == InstKind::Alloca) {
        baseTypePtr ty = inst->getType();
        // 规定：a_ptr 一定存储在 a 的下方，a_ptr.offset + STACK_ALIGN 即为 a 的地址
        stackOffset[inst] = cnt;
        cnt = alignsTo(cnt + 4, STACK_ALIGN);
        // 由于 Alloca 指令创建的一定为指针，故其取到的为所指空间大小
        cnt += alignsTo(ty->getSize(), STACK_ALIGN);
      }
    }
  }

  // 处理形参偏移，思考下，如若每次均是 alloca 则已经包含在上面
}
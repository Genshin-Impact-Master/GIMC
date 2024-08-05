#include "../include/IRToArm/IRToArm.h"
#include "../include/IR/Inst.h"
#define IMM(v) "#" + std::to_string(v)

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
  armOut << name << ":" << std::endl;

  // 预备的栈处理工作，fp 设为 r7
  smartOut("/* ******** 函数预处理 ******** */");
  smartOut("@ 将 fp 压栈");
  push(FP_REG);
  smartOut("@ 将 lr 压栈");
  push("lr");
  int offset = getStackSize(func);
  sub("sp", "sp", IMM(offset));
  add(FP_REG, sp, IMM(0));
  
  // 处理基本块
  INode<BBlock> *node = func->getBBlockList().getHeadPtr();
  while (!node->isEnd()) {
    node = node->getNext();
    BBlock *bBlk = node->getOwner();
    genBBlock(bBlk);
  }
}

void IRToArm::genBBlock(BBlock *bBlk) {
  if (bBlk->getName().compare("entry") != 0) {
    // 非起始基本块则直接输出标签
    armOut << "." << bBlk->getName() << "_" << bBlk->getParent()->getName() << ":" << std::endl;
  }
  // 处理 Instruction
  INode<Instruction> *node = bBlk->getInstList().getHeadPtr();
  while (!node->isEnd()) {
    node = node->getNext();
    Instruction *inst = node->getOwner();
    genInst(inst);
  }
}

void IRToArm::genInst(Instruction *inst) {
  InstKind kind = inst->getKind();
  switch (kind) {
    case InstKind::Add: {
      
    }
      break;
    case InstKind::Sub: {
      sub("r0", "r0", "r1");
    }
      break;
    case InstKind::Mul: {
      mul("");
    }
      break;
    case InstKind::Div: {
      
    }
      break;
    default:
      break;
  }
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
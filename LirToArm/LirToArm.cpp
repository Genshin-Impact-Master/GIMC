#include "../include/LirToArm/LirToArm.h"
#include <list>

USING_GIMC_NAMESPACE

void LirToArm::genModule() {
  // 准备工作
  smartOut(".arch", "armv7");
  smartOut(".fpu", "softvfp");
  
  std::list<LirFunction*> funcs = lirModule_.getFunctions();
  for (auto func : funcs) {
    genFunction(func);
  }

  // 输出全局变量以及常量池
  Output_Arm_global();
}


void LirToArm::genFunction(LirFunction *func) {
  std::string &name = func->getFuncName();
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
  LirBlock *entry = func->getEntry();
  genBlock(entry);

  INode<LirBlock> blkNode = entry->getNode();
  while (!blkNode.isEnd()) {
    // 除了入口基本块外，均需要输出其标签（实际上入口基本块标签输出也行）类似下方
    // Func:
    // entry_Func:
    blkNode = blkNode.getNext();
    LirBlock *blk = blkNode.getOwner();
    armOut << blk->getLabel() << ":" << std::endl;
    genBlock(blk);
  }  
}

void LirToArm::genBlock(LirBlock *blk) {
  
}

void LirToArm::Output_Arm_global() {
  for (auto iter : lirModule_.getGlobalOperands()) // iter 迭代所有的全局变量
    {
      std::cout << iter.first << ":"
                << "\n";
      armOut << iter.first << ":"
              << "\n";
      std::vector<Value *> &s = iter.second->getGlobalVarValues();

      if (TypeBase::isInteger(iter.second->getValueType())) {
        for (auto iter_value : s) {
          std::cout << "\t";
          std::cout << ".long"
                    << "\t";
          std::cout << iter_value->getName();
          std::cout << "\n";
          smartOut(".long", iter_value->getName());
        }
      }

      if (TypeBase::isFloat(iter.second->getValueType())) {
        for (auto iter_value : s) {
          std::cout << "\t";
          std::cout << ".long"
                    << "\t";
          std::cout << iter_value->getName();
          std::cout << "\n";
          smartOut(".long", iter_value->getName());
        }
      }
}
}
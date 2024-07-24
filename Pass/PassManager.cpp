#include "../include/Pass/PassManager.h"
#include "../include/IR/BBlock.h"
#include "../include/IR/Inst.h"

void PassManager::calDefUse() {
  if (do_def_use) {
    return;
  }
  do_def_use = true;
  // INode<BBlock> *node = func_->getBBlockList().getHeadPtr();
  // while (!node->isEnd()) {
  //   node = node->getNext();
  //   BBlock *bBlk = node->getOwner();
  //   INode<Instruction> *insNode = bBlk->getInstList().getHeadPtr();
  //   while (!insNode->isEnd()) {
  //     insNode = insNode->getNext();
  //     Instruction *inst = insNode->getOwner();
  //     inst->calculateDef_Uses();
  //   }
  // }
}

void PassManager::pres_succs() {
  if (do_pres_succs)
    return;
  Pres_Succs_Calculate::calculate_Func(func_);
  do_pres_succs = true;
#ifdef PRINT_CFG
  // 使用 graphviz 画 main 的数据流图
  func_->drawCFG();
#endif
}

void PassManager::domination() {
  if (do_domination)
    return;
  if (!do_pres_succs)
    pres_succs();
  do_domination = true;
  dom.initialize(func_);
  dom.calculate();
  dom.getDomSuccs();
}

void PassManager::mem2reg() {
  if (do_mem2reg)
    return;
  if (!do_domination)
    domination();
  if (!do_def_use)
    calDefUse();
  do_mem2reg = true;
  // mem2reg 需要在支配树计算后计算
  if (!do_domination) {
      domination();
  }
  Mem2reg(func_, dom); 
}
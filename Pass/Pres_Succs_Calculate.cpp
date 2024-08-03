#include "../include/Pass/Pres_Succs_Calculate.h"
#include "../include/IR/BBlock.h"
#include "../include/IR/Inst.h"

void Pres_Succs_Calculate::calculate_Module(Module *module) {
  for (auto func : *(module->getFuncDefs())) {
    calculate_Func(func);
  }
}

void Pres_Succs_Calculate::calculate_Func(Function *func) {
  // 计算前驱与后继结点。br 指令与 ret 指令作为基本块的结尾
  INode<BBlock> *bBlkNode = func->getBBlockList().getHeadPtr();
  while (!bBlkNode->isEnd()) {
    bBlkNode = bBlkNode->getNext();
    BBlock *chosenBBlk = bBlkNode->getOwner();
    // fprintf(stdout, "The chosen BBlock is %s \n", chosenBBlk->getName().c_str());
    Instruction *terminator = chosenBBlk->getInstList().getRearPtr()->getOwner(); 
    Br *branch = dynamic_cast<Br*>(terminator);
    if (branch) {
      // 说明为 Br 指令
      
      // 判断是否为无条件跳转指令
      if (branch->isUnconditional()) {
        BBlock *ifTrue = branch->getTrueBBlk();
        chosenBBlk->addSuccBBlock(ifTrue);
        ifTrue->addPreBBlock(chosenBBlk);
      }
      else {
        BBlock *ifTrue = branch->getTrueBBlk();
        BBlock *ifFalse = branch->getFalseBBlk();
        chosenBBlk->addSuccBBlock(ifTrue);
        chosenBBlk->addSuccBBlock(ifFalse);
        ifTrue->addPreBBlock(chosenBBlk);
        ifFalse->addPreBBlock(chosenBBlk);
      }
    }
    else {
      // 说明为 Ret 指令
      Ret *ret = dynamic_cast<Ret*>(terminator);
      if (!ret) {
        error( "请检查基本块结尾是否为有效的终结符指令：Br 或 Ret");
        exit(1);
      }
      
      // 将 Function 中虚拟的 BBlock exit 作为结束结点
      // chosenBBlk->addSuccBBlock(func->getExitBBlock());
      // func->getExitBBlock()->addPreBBlock(chosenBBlk);
    }
  }
}

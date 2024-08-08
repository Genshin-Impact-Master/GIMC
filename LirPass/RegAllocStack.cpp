#include "../include/LirPass/RegAllocStack.h"

USING_GIMC_NAMESPACE

void RegAllocStack::alloc(LirModule &lirModule) {
  for (auto func : lirModule.getFunctions()) {
    LirBlock *entry = func->getEntry();
    INode<LirBlock> *blkNode = entry->getNode();
    // 第一遍遍历，先进行栈空间初始化，将 reg 分配到栈空间
    while (!blkNode->isEnd()) {
      blkNode = blkNode->getNext();
      LirBlock *blk = blkNode->getOwner();
      INode<LirInst> *instNode = blk->getInst().getHeadPtr();
      while (!instNode->isEnd()) {
        instNode = instNode->getNext();
        LirInst *inst = instNode->getOwner();
        if (inst->isBinary() || inst->isIFChange()) {
          putLocal(inst->getOpd1(), func); 
        }
      }
    }

    // 第二遍遍历，进行栈分配，将 reg 从栈中取出
    blkNode = entry->getNode();
    while (!blkNode->isEnd()) {
      blkNode = blkNode->getNext();
      LirBlock *blk = blkNode->getOwner();
      INode<LirInst> *instNode = blk->getInst().getHeadPtr();
      while (!instNode->isEnd()) {
        instNode = instNode->getNext();
        LirInst *inst = instNode->getOwner();
        allocInst(inst, blk);
      }
    }
  }
}

void RegAllocStack::allocInst(LirInst *inst) {
  LirBlock *blk = inst->getParent();
  LirInstKind kind = inst->getKind();
  if (inst->isBinary()) {
    
  }
  else if (kind == LirInstKind::Store) {
    
  }
  else if (kind == LirInstKind::Load) {
    
  }
  else if (kind == LirInstKind::Call) {
    
  }
  else if (kind == LirInstKind::Ret) {
    
  }
  else if (kind == LirInstKind::cmp) {
    
  }
  else if (kind == LirInstKind::Br) {
    
  }
  else if (kind == LirInstKind::Fp2Int) {
    
  }
  else if (kind == LirInstKind::Int2Fp) {
    
  }
  else if (kind == LirInstKind::Move) {
    
  }
}

IImm RegAllocStack::putLocal(LirOperand *reg, LirFunction *lirFunc) {
  auto map = lirFunc->getImmMap();
  // 需要放入栈空间的条件为：
  // 1. 虚拟寄存器
  // 2. 并非与立即数绑定（因为在栈分配中，直接 mov 到所需寄存器即可）
  if (reg->isVirtual() && map.find(reg) == map.end()) {
    size -= STACK_ALIGN;
    IImm yes(size);     // 先减后添加，因为第一个栈分配的局部变量在 sp - align 位置
    regsOffset.insert(std::pair<LirOperand *reg, IImm>(reg, yes)); 
  }
}
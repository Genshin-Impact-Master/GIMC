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

    // 再在起始位置加一条 sp += size 的命令
    LirBlock *blk = entry->getNode().getOwner();
    LirInst *fistInst = blk->getNode().getOwner();
    LirBinary bin = new LirBinary(LirInstKind::Add, blk, IPhyReg::SP, ToLir::loadImmToIVReg(size, func, blk), IPhyReg::SP);
    bin.addBefore(fistInst);

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
  LirFunction *lirFunk = blk->getParent();
  LirInstKind kind = inst->getKind();
  std::vector<LirOperand*> &opds = inst->getOpds();
  // 立即数 map，可直接移入寄存器
  std::map<LirOperand*, LirInstMove*> map = lirFunc->getImmMap();
  // opd1 一定为目的寄存器，创建 store 指令
  LirOperand *opd1 = inst->getOpd1();
  if (regsOffset.find(opd1) != regsOffset.end()) {
    // 为栈分配中新增变量，新增取值指令
    resolveStack(opd1);
    LirStore *store = new LirStore();
  }
  for (auto opd : opds) {
    // 若为虚拟寄存器
      // 则在该指令前加入取栈指令（ldr）
      if (opd->isFloat()) {
        
      }
    }
    else if (opd->isImm()) {
      error("LIR 构建中所有 Imm 都会转换为 Virtual Reg");
    }
}
//   if (inst->isBinary()) {
    
//   }
//   else if (kind == LirInstKind::Store) {
    
//   }
//   else if (kind == LirInstKind::Load) {
    
//   }
//   else if (kind == LirInstKind::Call) {
    
//   }
//   else if (kind == LirInstKind::Ret) {
    
//   }
//   else if (kind == LirInstKind::cmp) {
    
//   }
//   else if (kind == LirInstKind::Br) {
    
//   }
//   else if (kind == LirInstKind::Fp2Int) {
    
//   }
//   else if (kind == LirInstKind::Int2Fp) {
    
//   }
//   else if (kind == LirInstKind::Move) {
    
//   }
// }

void RegAllocStack::resolveStack(LirOperand *reg, LirInst *inst) {
  LirBlock *blk = inst->getParent();
  LirFunction *lirFunc = blk->getParent();
  int offset = regsOffset.at(opd1).getImm();
  // 将 offset 移入 r4 中
  LirInstMove *move = new LirInstMove(blk, IPhyReg::getRegR(4), new IImm(offset), LirArmStatus::NO_Cond);
  
  // 生成的 add 指令的目的虚拟寄存器，todo：应该有一个统一的 Value*，有助于生成一个虚拟寄存器
  LirOperand *addDst = operandResolve(val, lirFunc, blk);
  LirBinary *realAddr = new LirBinary(LirInstKind::Add, blk, IPhyReg::getRegR(FP_REG), off, addDst);
}

IImm RegAllocStack::putLocal(LirOperand *reg, LirFunction *lirFunc) {
  std::map<LirOperand*, LirInstMove*> map = lirFunc->getImmMap();
  // 需要放入栈空间的条件为：
  // 1. 虚拟寄存器
  // 2. 并非与立即数绑定（因为在栈分配中，直接 mov 到所需寄存器即可）
  if (reg->isVirtual() && map.find(reg) == map.end()) {
    size -= STACK_ALIGN;
    IImm yes(size);     // 先减后添加，因为第一个栈分配的局部变量在 sp - align 位置
    regsOffset.insert(std::pair<LirOperand *reg, IImm>(reg, yes)); 

  }
}
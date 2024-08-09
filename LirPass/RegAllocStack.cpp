#include "../include/LirPass/RegAllocStack.h"
#define IReg(r) IPhyReg::getRegR(r)

USING_GIMC_NAMESPACE

void RegAllocStack::alloc(LirModule &lirModule) {
  for (auto func : lirModule.getFunctions()) {
    LirBlock *entry = func->getEntry();
    INode<LirBlock> *blkNode = &entry->getNode();
    // 第一遍遍历，先进行栈空间初始化，将 reg 分配到栈空间
    while (!blkNode->isEnd()) {
      blkNode = blkNode->getNext();
      LirBlock *blk = blkNode->getOwner();
      INode<LirInst> *instNode = blk->getInst().getHeadPtr();
      while (!instNode->isEnd()) {
        instNode = instNode->getNext();
        LirInst *inst = instNode->getOwner();
        if (inst->isBinary() || inst->isIFChange() || (inst->getKind() == LirInstKind::Load) || inst->getKind() == LirInstKind::Move) {
          putLocal(inst->getOpd1(), func); 
        }
      }
    }

    // 再在起始位置加一条 sp += size 的命令
    LirBlock *blk = entry->getNode().getOwner();
    LirInst *fistInst = blk->getInst().getHeadPtr()->getOwner();
    IVReg *tmpReg = new IVReg();
    IImm *iImm = new IImm(size);
    LirInstMove *move = new LirInstMove(blk, tmpReg, iImm, LirArmStatus::NO_Cond);
    func->getImmMap().insert(std::pair<LirOperand*, LirInstMove*>(tmpReg, move));
    LirBinary *bin = new LirBinary(LirInstKind::Add, blk, IPhyReg::SP, tmpReg, IPhyReg::SP);
    bin->addBefore(fistInst);
    move->addBefore(bin);

    // 第二遍遍历，进行栈分配，将 reg 从栈中取出
    blkNode = &entry->getNode();
    while (!blkNode->isEnd()) {
      blkNode = blkNode->getNext();
      LirBlock *blk = blkNode->getOwner();
      INode<LirInst> *instNode = blk->getInst().getHeadPtr();
      while (!instNode->isEnd()) {
        instNode = instNode->getNext();
        LirInst *inst = instNode->getOwner();
        allocInst(inst);
        LirOperand *opd1 = inst->getOpd1();
        LirOperand *opd2 = inst->getOpd2();
        LirOperand *opd3 = inst->getOpd3();
        if (opd1 && opd1->isVirtual()) {
          inst->setOpd1(IReg(4));
        }
        if (opd2 && opd2->isVirtual()) {
          inst->setOpd2(IReg(4));
        }
        if (opd3 && opd3->isVirtual()) {
          inst->setOpd3(IReg(5));
        }
      }
    }
  }
}

void RegAllocStack::allocInst(LirInst *inst) {
  LirBlock *blk = inst->getParent();
  LirFunction *lirFunc = blk->getParent();
  LirInstKind kind = inst->getKind();
  std::vector<LirOperand*> &opds = inst->getOpds();
  // 立即数 map，可直接移入寄存器
  std::map<LirOperand*, LirInstMove*> map = lirFunc->getImmMap();
  // opd1 一定为目的寄存器，创建 store 指令
  LirOperand *opd1 = inst->getOpd1();
  if (regsOffset.find(opd1) != regsOffset.end()) {
    // 为栈分配中新增变量，新增 Store 存值指令。在指令执行后添加
    LirInst *nextInst = inst->getNextInst();
    resolveStack(opd1, nextInst, IReg(5));
    // r4 中保存刚刚计算完的值
    LirStore *store = new LirStore(blk, IReg(5), IReg(4));
    store->addBefore(nextInst);
  }
  LirOperand *opd2 = inst->getOpd2();
  if (regsOffset.find(opd2) != regsOffset.end()) {
    // lhs 放在 r4 中
    resolveStack(opd2, inst, IReg(4));
    LirLoad *load = new LirLoad(blk, IReg(4), IReg(4));
    load->addBefore(inst);
  }
  LirOperand *opd3 = inst->getOpd3();
  if (regsOffset.find(opd3) != regsOffset.end()) {
    // rhs 放在 r5 中
    resolveStack(opd3, inst, IReg(5));
    LirLoad *load = new LirLoad(blk, IReg(5), IReg(5));
    load->addBefore(inst);
  }
}

void RegAllocStack::resolveStack(LirOperand *reg, LirInst *inst, LirOperand *saveTo) {
  if (!reg) {
    error("resoveStack: 做梦都没想到这里会错，因为能绑定到 map 的一定是");
  }
  LirBlock *blk = inst->getParent();
  LirFunction *lirFunc = blk->getParent();
  int offset = regsOffset.at(reg).getImm();
  // 将 offset 移入 saveTo 中
  LirInstMove *move = new LirInstMove(blk, saveTo, new IImm(offset), LirArmStatus::NO_Cond);
  // saveTo <- offset + saveTo
  LirBinary *realAddr = new LirBinary(LirInstKind::Add, blk, IPhyReg::getRegR(FP_REG), saveTo, saveTo);
  realAddr->addBefore(inst);
}

void RegAllocStack::putLocal(LirOperand *reg, LirFunction *lirFunc) {
  std::map<LirOperand*, LirInstMove*> map = lirFunc->getImmMap();
  // 需要放入栈空间的条件为：
  // 1. 虚拟寄存器
  // 2. 并非与立即数绑定（因为在栈分配中，直接 mov 到所需寄存器即可）
  if (reg->isVirtual() && map.find(reg) == map.end()) {
    size -= STACK_ALIGN;
    IImm yes(size);     // 先减后添加，因为第一个栈分配的局部变量在 sp - align 位置
    regsOffset.insert(std::pair<LirOperand*, IImm>(reg, yes));
  }
}
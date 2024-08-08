#include "../../include/LIR/lirInst/LirInst.h"
#include "../../include/LIR/visitor/LirBlock.h"

USING_GIMC_NAMESPACE

LirInst::LirInst(LirInstKind kind, LirBlock *parent_)
    : lirInstNode(nullptr, nullptr, this), parent(parent_), lirKind(kind) {}

LirStore::LirStore(LirBlock *parent, LirOperand *addr, LirOperand *input)
    : LirInst(LirInstKind::Store, parent) {
  opd2 = addr;
  opd3 = input;
}

LirLoad::LirLoad(LirBlock *parent, LirOperand *dst, LirOperand *ptr)
    : LirInst(LirInstKind::Load, parent) {
  opd1 = dst;
  opd2 = ptr;
}

LirRet::LirRet(LirBlock *parent)
    : LirInst(LirInstKind::Ret, parent) {}

LirBr::LirBr(LirBlock *parent, LirOperand *addr, LirArmStatus status_)
    : LirInst(LirInstKind::Br, parent) {
  opd2 = addr;
  status = status_;
}

LirCmp::LirCmp(LirBlock * parent, LirOperand * opd2, LirOperand * opd3)
    : LirInst(LirInstKind::cmp, parent) {
  this->opd2 = opd2;
  this->opd3 = opd3;
}

LirFp2Int::LirFp2Int(LirBlock * parent, LirOperand * dst, LirOperand * proto)
    : LirInst(LirInstKind::Fp2Int, parent) {
  this->opd1 = dst;
  this->opd2 = proto;
}

LirInt2Fp::LirInt2Fp(LirBlock * parent, LirOperand * dst, LirOperand * proto)
    : LirInst(LirInstKind::Int2Fp, parent) {
  opd1 = dst;
  opd2 = proto;
}

LirCall::LirCall(LirBlock *parent, LirOperand *func)
    : LirInst(LirInstKind::Call, parent) {
  opd2 = func;
}

LirPush::LirPush(LirBlock *parent, LirOperand *reg)
    : LirInst(LirInstKind::Push, parent) {
  opd2 = reg;
}

LirPop::LirPop(LirBlock *parent, LirOperand *reg)
    : LirInst(LirInstKind::Pop, parent) {
  opd2 = reg;
}
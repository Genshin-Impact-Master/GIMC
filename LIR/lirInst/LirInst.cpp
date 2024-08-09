#include "../../include/LIR/lirInst/LirInst.h"
#include "../../include/LIR/visitor/LirBlock.h"

USING_GIMC_NAMESPACE

LirInst::LirInst(LirInstKind kind, LirBlock *parent_)
    : lirInstNode(nullptr, nullptr, this), parent(parent_), lirKind(kind) {}

LirStore::LirStore(LirBlock *parent, LirOperand *addr, LirOperand *input)
    : LirInst(LirInstKind::Store, parent) {
  opds[1] = addr;
  opds[2] = input;
}

LirLoad::LirLoad(LirBlock *parent, LirOperand *dst, LirOperand *ptr)
    : LirInst(LirInstKind::Load, parent) {
  opds[0] = dst;
  opds[1] = ptr;
}

LirRet::LirRet(LirBlock *parent)
    : LirInst(LirInstKind::Ret, parent) {}

LirBr::LirBr(LirBlock *parent, LirOperand *addr, LirArmStatus status_)
    : LirInst(LirInstKind::Br, parent) {
  opds[1] = addr;
  status = status_;
}

LirCmp::LirCmp(LirBlock * parent, LirOperand * opd2, LirOperand * opd3)
    : LirInst(LirInstKind::cmp, parent) {
  this->opds[1] = opd2;
  this->opds[2] = opd3;
}

LirFp2Int::LirFp2Int(LirBlock * parent, LirOperand * dst, LirOperand * proto)
    : LirInst(LirInstKind::Fp2Int, parent) {
  this->opds[0] = dst;
  this->opds[1] = proto;
}

LirInt2Fp::LirInt2Fp(LirBlock * parent, LirOperand * dst, LirOperand * proto)
    : LirInst(LirInstKind::Int2Fp, parent) {
  opds[0] = dst;
  opds[1] = proto;
}

LirCall::LirCall(LirBlock *parent, LirOperand *func)
    : LirInst(LirInstKind::Call, parent) {
  opds[1] = func;
}

LirPush::LirPush(LirBlock *parent, LirOperand *reg)
    : LirInst(LirInstKind::Push, parent) {
  opds[1] = reg;
}

LirPop::LirPop(LirBlock *parent, LirOperand *reg)
    : LirInst(LirInstKind::Pop, parent) {
  opds[1] = reg;
}
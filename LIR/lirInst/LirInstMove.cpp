#include "../../include/LIR/lirInst/LirInstMove.h"

USING_GIMC_NAMESPACE

LirInstMove::LirInstMove(LirBlock *parent, LirOperand *dst, LirOperand *src, LirArmStatus status_) : LirInst(LirInstKind::Move, parent) {
  opds[0] = dst;
  opds[1] = src;
  status = status_;
}
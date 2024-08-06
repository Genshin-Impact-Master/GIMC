#include "../../include/LIR/lirInst/LirInstMove.h"

USING_GIMC_NAMESPACE

LirInstMove::LirInstMove(LirBlock *parent, LirOperand *dst, LirOperand *src) : LirInst(LirInstKind::Move, parent) {
  opd1 = dst;
  opd2 = src;
}
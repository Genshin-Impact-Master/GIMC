#include "../../include/LIR/lirInst/LirInstMove.h"

USING_GIMC_NAMESPACE

LirInstMove::LirInstMove(LirBlock *parent, LirOperand *dst, LirOperand *src) : LirInst(LirInstKind::Move, parent) {
  lirOpds.push_back(dst);
  lirOpds.push_back(src);
}
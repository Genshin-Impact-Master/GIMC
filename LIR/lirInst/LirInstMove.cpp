#include "../../include/LIR/lirInst/LirInstMove.h"

USING_GIMC_NAMESPACE

LirInstMove::LirInstMove(LirBlock &lirBlock, LirOperand &dst, LirOperand &src) {
    this->lirBlock = lirBlock;
    this->dst = dst;
    this->src = src;
}
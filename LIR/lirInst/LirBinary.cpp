#include "../../include/LIR/lirInst/LirBinary.h"

USING_GIMC_NAMESPACE

LirBinary::LirBinary(LirInstKind kind, LirBlock* parent, LirOperand &lhs, LirOperand &rhs, LirOperand &dst) {
    setKind(kind);
    setParent(parent);
    this->lhs = lhs;
    this->rhs = rhs;
    this->dst = dst;
}
#include "../../include/LIR/lirInst/LirBinary.h"

USING_GIMC_NAMESPACE

LirBinary::LirBinary(LirInstKind kind, LirBlock* parent, LirOperand *lhs, LirOperand *rhs, LirOperand *dst) : LirInst(kind, parent) {
    // 目的寄存器总是放在第一个
    opds[0] = dst;
    opds[1] = lhs;
    opds[2] = rhs;
}
#include "../../include/LIR/lirInst/LirBinary.h"

USING_GIMC_NAMESPACE

LirBinary::LirBinary(LirInstKind kind, LirBlock* parent, LirOperand *lhs, LirOperand *rhs, LirOperand *dst) : LirInst(kind, parent) {
    // 目的寄存器总是放在第一个
    opd1 = dst;
    opd2 = lhs;
    opd3 = rhs;
    parent->addInst(this);
}
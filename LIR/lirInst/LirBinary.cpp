#include "../../include/LIR/lirInst/LirBinary.h"

USING_GIMC_NAMESPACE

LirBinary::LirBinary(LirInstKind kind, LirBlock* parent, LirOperand *lhs, LirOperand *rhs, LirOperand *dst) : LirInst(kind, parent) {
    // 目的寄存器总是放在第一个
    lirOpds.push_back(dst);
    lirOpds.push_back(lhs);
    lirOpds.push_back(rhs);
}
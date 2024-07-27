#ifndef LIR_INST_H
#define LIR_INST_H
#include "Config.h"
#include "lirOperand.h"

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

enum class LirInstKind {
    Add,
    Sub,
    Mul,
    Div,
    SRem,
    Addf,
    Subf,
    Mulf,
    Divf,
    Store,
    Load,
    Call,
    Ret,
    cmp,
    Br,
    Fp2Int,
    Int2Fp
};



GIMC_NAMESPACE_END


#endif
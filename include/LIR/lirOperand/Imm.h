#ifndef LIR_IMM_H
#define LIR_IMM_H
#include "../../Config.h"
#include "lirOperand.h"
GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class Imm : public LirOperand {
    public: 
        Imm(LirOperandKind ImmKind) : LirOperand(ImmKind) {};

        virtual std::string toHexString() = 0;
};



GIMC_NAMESPACE_END
#endif
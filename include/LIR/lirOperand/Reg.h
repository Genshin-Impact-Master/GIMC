#ifndef LIR_REG_H
#define LIR_REG_H
#include "../../Config.h"
#include "lirOperand.h"
#include <set>
GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class Reg : public LirOperand {
    public:
        Reg(LirOperandKind RegKind);
        static std::set<Reg*>* getAllocatableRegs();
        static int getAllocatableRegsCnt(bool isinteger);
};

GIMC_NAMESPACE_END
#endif
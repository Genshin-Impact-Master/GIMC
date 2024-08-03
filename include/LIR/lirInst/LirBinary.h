#ifndef LIR_BINARY_H
#define LIR_BINARY_H
#include "../../Config.h"
#include "LirBlock.h"
#include "lirOperand.h"
#include "LirInst.h"
GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class LirBinary : public LirInst {
    private:
        LirOperand lhs;
        LirOperand rhs;
        LirOperand dst;

    public:
        LirBinary(LirInstKind kind, LirBlock* parent, LirOperand &lhs, LirOperand &rhs, LirOperand &dst);
};

GIMC_NAMESPACE_END


#endif
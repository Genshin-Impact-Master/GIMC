#ifndef LIR_INST_MOVE_H
#define LIR_INST_MOVE_H
#include "../../Config.h"
#include "../lirOperand/lirOperand.h"
#include "../../IR/Inst.h"
#include "../visitor/LirBlock.h"
GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class LirInstMove {
    private:
        LirBlock lirBlock;
        LirOperand dst;
        LirOperand src;

    public:
        LirInstMove(LirBlock &lirBlock, LirOperand &dst, LirOperand &src);

};

GIMC_NAMESPACE_END
#endif

#ifndef LIR_INST_MOVE_H
#define LIR_INST_MOVE_H
#include "../../Config.h"
#include "../lirOperand/lirOperand.h"
#include "../../IR/Inst.h"
#include "../visitor/LirBlock.h"
#include "LirInst.h"
GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class LirInstMove : public LirInst {
    public:
        LirInstMove(LirBlock *parent, LirOperand *dst, LirOperand *src, LirArmStatus status_);

};

GIMC_NAMESPACE_END
#endif

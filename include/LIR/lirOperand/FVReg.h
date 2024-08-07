#ifndef LIR_FVREG_H
#define LIR_FVREG_H
#include "../../Config.h"
#include "lirOperand.h"
#include "Reg.h"

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class FVReg : public Reg {
    private:
        static int count;
        int id;
    
    public:
        FVReg() : Reg(LirOperandKind::FVirtual), id(){count++;};

        FVReg(int id) : Reg(LirOperandKind::FVirtual), id(id){};

        std::string toString() override;
};

GIMC_NAMESPACE_END

#endif
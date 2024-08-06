#ifndef LIR_FIMM_H
#define LIR_FIMM_H
#include "../../Config.h"
#include "lirOperand.h"
#include "Imm.h"
#include <iostream>
#include <sstream>

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class FImm : public Imm {
    private:
        float imm;
    public:
        FImm(float imm) : Imm(LirOperandKind::FImm) {
            this->imm = imm;
        }

        float getImm() {
            return imm;
        }

        std::string toString() override;

        std::string toHexString() override;

};

GIMC_NAMESPACE_END
#endif
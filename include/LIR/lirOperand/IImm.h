#ifndef LIR_IIMM_H
#define LIR_IIMM_H
#include "../../Config.h"
#include "lirOperand.h"
#include "Imm.h"
#include <iostream>
#include <sstream>
GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class IImm : public Imm {
    private: 
        int imm;

    public:
        IImm(int imm_) : Imm(LirOperandKind::IImm), imm(imm_) {}

        int getImm() {
            return imm;
        }

        std::string toString() override;

        std::string toHexString() override;
        
};

GIMC_NAMESPACE_END
#endif
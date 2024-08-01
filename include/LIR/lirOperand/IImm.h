#ifndef LIR_IIMM_H
#define LIR_IIMM_H
#include "Config.h"
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
        IImm(int imm) : Imm(LirOperandKind::IImm) {
            this->imm = imm;
        }

        int getImm() {
            return imm;
        }

        std::string toString();

        std::string toHexString();
        
};

GIMC_NAMESPACE_END
#endif
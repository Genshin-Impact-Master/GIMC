#include "../../include/LIR/lirOperand/FImm.h"

USING_GIMC_NAMESPACE

std::string FImm::toString() {
    return std::to_string(imm);
}

std::string FImm::toHexString() {
            std::ostringstream oss;
            oss << std::hexfloat << imm; 
            return oss.str();
}
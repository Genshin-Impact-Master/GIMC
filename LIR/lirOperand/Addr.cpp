#include "../../include/LIR/lirOperand/Addr.h"

USING_GIMC_NAMESPACE

Addr::Addr(std::string label) : LirOperand(LirOperandKind::Addr) {
            this->label = label;
        }

std::string Addr::toString() {
    return label;
}
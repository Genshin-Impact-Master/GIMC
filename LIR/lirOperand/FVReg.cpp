#include "../../include/LIR/lirOperand/FVReg.h"

USING_GIMC_NAMESPACE

std::string FVReg::toString() { return "@FV" + std::to_string(id);}

int FVReg::count = 0;
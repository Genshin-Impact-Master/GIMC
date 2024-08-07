#include "../../include/LIR/lirOperand/IVReg.h"

USING_GIMC_NAMESPACE

std::string IVReg::toString() { return "@IV" + std::to_string(id);}

int IVReg::count = 0;
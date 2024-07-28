#include "../../include/LIR/visitor/LirBlock.h"
#include "LirFunction.h"

USING_GIMC_NAMESPACE

LirBlock::LirBlock(LirFunction* lirFunction, const std::string &label) : lirFunction(lirFunction), label(label) {};

void LirBlock::addPres(LirBlock* lirPre) {
    lirPres.insert(lirPre);
}


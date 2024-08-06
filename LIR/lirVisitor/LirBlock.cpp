#include "../../include/LIR/visitor/LirBlock.h"
#include "LirFunction.h"

USING_GIMC_NAMESPACE

LirBlock::LirBlock(LirFunction* lirFunction, const std::string &label) : 
                  lirFunction(lirFunction), 
                  label(label),
                  node(nullptr, nullptr, this),
                  lirInstLists(this) {};

void LirBlock::addPres(LirBlock* lirPre) {
    lirPres.insert(lirPre);
}

void LirBlock::setTrueLirSucc(LirBlock* trueLirSucc) {
    this->trueLirSucc = trueLirSucc;
}

void LirBlock::setFalseLirSucc(LirBlock* falseLirSucc) {
    this->falseLirSucc = falseLirSucc;
}

void LirBlock::addInst(LirInst* lirInst) {
    lirInstLists.append(lirInst->getNode());
}


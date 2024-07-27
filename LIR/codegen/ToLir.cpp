#include "../../include/LIR/codegen/ToLir.h"

USING_GIMC_NAMESPACE

ToLir::ToLir(Module irModule) : irModule(irModule) {};

LirModule ToLir::moduleGen() {
    for(GlobalVar* globalVar : *irModule.getGlobalVars()) {
        lirModule.getGlobalvars()[globalVar->getName()] = globalVar;
        valMap[globalVar] = &Addr(globalVar->getName());
    }





    
}
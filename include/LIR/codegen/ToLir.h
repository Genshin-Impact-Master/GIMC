#ifndef LIR_TOLIR_H
#define LIR_TOLIR_H
#include "Config.h"
#include "lirOperand.h"
#include <map>
#include <set>
#include "Value.h"
#include "LirBlock.h"
#include "LirFunction.h"
#include "LirModule.h"
#include "Function.h"
#include "BBlock.h"
#include "Module.h"
#include "Addr.h"
#include "Inst.h"
#include "FVReg.h"
#include "IVReg.h"
#include "Imm.h"
#include "FImm.h"
#include "IImm.h"
#include "LirInst.h"
#include "LirInstMove.h"
#include "LirBinary.h"

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class ToLir {
    private:
        std::map<Value*, LirOperand*> valMap;
        std::map<Function*, LirFunction*> funcMap;
        std::map<BBlock*, LirBlock*> blockMap;
        std::map<GlobalVar*, LirOperand*> globalMap;

        Module irModule;
        LirModule lirModule;

    public:
        ToLir(Module irModule);
        LirModule moduleGen();
        void instResolve(Function *func, BBlock *block);
        LirOperand operandResolve(Value* val, LirFunction* lirFunc, LirBlock* lirBlock);
        LirOperand immResolve(Value* val, LirFunction* lirFunc, LirBlock* lirBlock) ;
        FVReg& loadImmToFVReg(float val, LirFunction* lirFunc, LirBlock* lirBlock);
        IVReg& ToLir::loadImmToIVReg(int val, LirFunction* lirFunc, LirBlock* lirBlock);

        

        

};


GIMC_NAMESPACE_END



#endif
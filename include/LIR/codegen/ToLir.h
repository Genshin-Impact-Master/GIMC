#ifndef LIR_TOLIR_H
#define LIR_TOLIR_H
#include "../../Config.h"
#include "../lirOperand/lirOperand.h"
#include <map>
#include <set>
#include "../../IR/Value.h"
#include "../visitor/LirBlock.h"
#include "../visitor/LirFunction.h"
#include "../visitor/LirModule.h"
#include "../../IR/Function.h"
#include "../../IR/BBlock.h"
#include "../../IR/Module.h"
#include "../lirOperand/Addr.h"
#include "../../IR/Inst.h"
#include "../lirOperand/FVReg.h"
#include "../lirOperand/IVReg.h"
#include "../lirOperand/Imm.h"
#include "../lirOperand/FImm.h"
#include "../lirOperand/IImm.h"
#include "../lirInst/LirInst.h"
#include "../lirInst/LirInstMove.h"
#include "../lirInst/LirBinary.h"

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
        IVReg& loadImmToIVReg(int val, LirFunction* lirFunc, LirBlock* lirBlock);

        

        

};


GIMC_NAMESPACE_END



#endif
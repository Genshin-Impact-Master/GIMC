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
        std::map<Value*, LirOperand*> valMap;           // 局部变量（包括形参）map
        std::map<Function*, LirFunction*> funcMap;
        std::map<BBlock*, LirBlock*> blockMap;
        std::map<Value*, Addr*> globalMap;              // 全局的 map，包括全局变量，函数以及所有基本块

        Module irModule;
        LirModule lirModule;

    public:
        ToLir(Module irModule);
        LirModule& moduleGen();
        void instResolve(BBlock *block);
        LirOperand* operandResolve(Value* val, LirFunction* lirFunc, LirBlock* lirBlock);
        LirOperand* immResolve(Value* val, LirFunction* lirFunc, LirBlock* lirBlock) ;
        FVReg* loadImmToFVReg(float val, LirFunction* lirFunc, LirBlock* lirBlock);
        IVReg* loadImmToIVReg(int val, LirFunction* lirFunc, LirBlock* lirBlock);

        // 将 Value* 和 LirOperand* 映射建立起来
        void bindValue(Value *val, LirOperand *reg) {
          // 因为只有初始化阶段会将 globalMap 中添加，后续 LIR 指令构建时只会构建 valMap
          valMap[val] = reg;
        }

        // 对于全局变量，一定为 <label> 标签，即 addr
        void bindGlobal(Value *val, Addr *addr) {
          globalMap[val] = addr;
        }

        // 遍历基本块时，需要将 valMap 中的局部变量清空（因为不知道从其他基本块跳转过来时的寄存器状态）
        void clearLocal() {valMap.clear()}

        /**
         * 根据 Value 获取 LirOperand
         * 若为全局符号则从 globalMap 中获得标签
         **/ 
        LirOperand *getBindOperand(Value *val) {
          if (valMap.find(val) != valMap.end())
            return valMap[val];
          if (globalMap.find(val) != globalMap.end())
            return globalMap[val];
          error("getBindOperand: val 还未与 LirOperand 绑定");
        }

        

        

};


GIMC_NAMESPACE_END



#endif
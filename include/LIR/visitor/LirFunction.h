#ifndef LIR_FUNC_H
#define LIR_FUNC_H
#include "../../Config.h"
#include "../lirOperand/lirOperand.h"
#include "../lirOperand/IImm.h"
#include "../lirInst/LirInstMove.h"
#include "../../IR/Type.h"
#include "../../IR/Inst.h"
#include <map>


GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class LirFunction {
    private:
        std::string lirFuncName;
        int paramsCnt; //全体参数数量
        int fparamsCnt; //浮点参数数量
        int iparamsCnt; //整型参数数量
        baseTypePtr returnType;

        LirBlock *prologue;    // 即开始的基本块 entry
        IList<LirFunction, LirBlock> blkList;

        std::vector<Value> paramter;
        int stackSize = 0;

        /* @C++_Learn std::map<LirOperand&, LirInstMove&> 这样的声明在 C++ 中是不允许的。
         标准库容器（例如 std::map、std::vector 等）不能直接包含引用类型，
         因为它们要求元素类型必须是可复制的，而引用本身不是一个对象，它只是一个别名。
        */
        std::map<LirOperand*, LirInstMove*> immMap;

        /*******************中间变量，即为了辅助 Lir 的生成****************/
        // 中端 alloca 出的局部变量到 IImm 的映射表
        std::map<Value*, IImm> stackOffsetMap;

    public:
        LirFunction(std::string name, int paramsCnt);
        void setLirFuncParams(std::vector<Value> &lirFuncParams);
        void setIParamsCnt(int intcnt);
        void setFParamsCnt(int floatcnt);
        void setReturnType(baseTypePtr returnType);
        std::map<LirOperand, LirInstMove>& getImmMap();
        std::map<Value*, IImm>& getStackOffsetMap() {return stackOffsetMap;}
        int getStackSize() {return stackSize;}

        void appendBlk(LirBlock *blk) {
          blkList.append(blk->getNode());
        }
        
        // 将 IR 中 alloca 指令生成的变量分配到函数栈空间
        IImm putLocalVar(Value *alloca);

        // 获取函数名
        std::string &getFuncName() {return lirFuncName();}

        // 获取 entry 基本块
        LirBlock* getEntry() {return prologue;}
        



};


GIMC_NAMESPACE_END


#endif
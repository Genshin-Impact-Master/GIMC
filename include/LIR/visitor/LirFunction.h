#ifndef LIR_FUNC_H
#define LIR_FUNC_H
#include "../../Config.h"
#include "../lirOperand/lirOperand.h"
#include "../lirInst/LirInstMove.h"
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
        LirBlock prologue;
        std::vector<Value> paramter;

        /* @C++_Learn std::map<LirOperand&, LirInstMove&> 这样的声明在 C++ 中是不允许的。
         标准库容器（例如 std::map、std::vector 等）不能直接包含引用类型，
         因为它们要求元素类型必须是可复制的，而引用本身不是一个对象，它只是一个别名。
        */
        std::map<LirOperand, LirInstMove> immMap;


    public:
        LirFunction(std::string name, int paramsCnt);
        void setLirFuncParams(std::vector<Value> &lirFuncParams);
        void setIParamsCnt(int intcnt);
        void setFParamsCnt(int floatcnt);
        void setReturnType(baseTypePtr returnType);
        std::map<LirOperand, LirInstMove>& getImmMap();


        



};


GIMC_NAMESPACE_END


#endif
#ifndef LIR_FUNC_H
#define LIR_FUNC_H
#include "Config.h"
#include "lirOperand.h"


GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class LirFunction {
    private:
        int fparamsCnt; //浮点参数数量
        int iparamsCnt; //整型参数数量
        LirBlock prologue;
        



};


GIMC_NAMESPACE_END


#endif
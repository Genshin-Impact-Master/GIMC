#include "../../include/LIR/visitor/LirFunction.h"

USING_GIMC_NAMESPACE

LirFunction::LirFunction(std::string name, int paramsCnt) : lirFuncName(name), paramsCnt(paramsCnt) {};

void LirFunction::setLirFuncParams(std::vector<Value> &lirFuncParams) {this->paramter = lirFuncParams;} 

void LirFunction::setIParamsCnt(int intcnt) {this->iparamsCnt = intcnt;}

void LirFunction::setFParamsCnt(int floatcnt) {this->fparamsCnt = floatcnt;}

void LirFunction::setReturnType(baseTypePtr returnType) {this->returnType = returnType;}

std::map<LirOperand*, LirInstMove*>& LirFunction::getImmMap() {
    return immMap;
}

IImm LirFunction::putLocalVar(Value *alloca) {
  baseTypePtr ty = alloca->getType();
  // 获取局部变量的大小
  int size = ty->getSize();
  IImm yes = IImm(stackSize);
  stackSize += size;
  return yes;
}
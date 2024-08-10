#include "../../include/LIR/visitor/LirFunction.h"

USING_GIMC_NAMESPACE

LirFunction::LirFunction(std::string name, int paramsCnt) : lirFuncName(name), paramsCnt(paramsCnt), blkList(this) {};

void LirFunction::setLirFuncParams(std::vector<Value*> &lirFuncParams) {this->parameters = lirFuncParams;} 

void LirFunction::setIParamsCnt(int intcnt) {this->iparamsCnt = intcnt;}

void LirFunction::setFParamsCnt(int floatcnt) {this->fparamsCnt = floatcnt;}

void LirFunction::setReturnType(baseTypePtr returnType) {this->returnType = returnType;}

std::map<LirOperand*, LirInstMove*>& LirFunction::getImmMap() {
    return immMap;
}

IImm LirFunction::putLocalVar(Value *alloca) {
  baseTypePtr ty = alloca->getType();
  // 获取局部变量的大小
  int size = alignsTo(ty->getSize(), 8);    // 8 字节对齐
  IImm yes(stackSize);
  stackSize += size;
  stackOffsetMap.insert(std::pair<Value*, IImm>(alloca, yes));
#ifdef DEBUG_MODE
  std::cout << "put Local Var " << alloca->getFullName() << " with stackoffset " << yes.getImm() << std::endl; 
#endif
  return yes;
}

IImm LirFunction::putParam(Value *param) {
  // 这里的 param 只能是 int，float，pointer，即只占 32 位，但用 8 字节对齐一下
  IImm yes(paramSize);
  paramSize -= STACK_ALIGN;
  stackOffsetMap.insert(std::pair<Value*, IImm>(param, yes));
  return yes;
}

void LirFunction::updateParamStack() {
  for (auto param : parameters) {
    int right = stackOffsetMap.at(param).getImm();
    // putParam 是减去，故 stackSize - right 即形参在栈上的实际偏移量
    right = stackSize - right;
    stackOffsetMap.insert(std::pair<Value*, IImm>(param, right));
  }
}
#include "../include/IR/Module.h"
#include "../include/IR/GlobalVar.h"

USING_GIMC_NAMESPACE

void Module::clearModule() {
  for (auto func : funcDefs_) {
    func->clearFunc();
    delete func;
  }
  funcDefs_.clear();
  for (auto globalVar : globalVars_) {
    delete globalVar;
  }
  globalVars_.clear();
  // 函数声明不需要清空其中基本块，因为其不含基本块
  funcDeclares_.clear();
}

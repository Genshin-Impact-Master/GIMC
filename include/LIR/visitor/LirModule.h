#ifndef LIR_MODULE_H
#define LIR_MODULE_H
#include "../../Config.h"
#include "../../IR/GlobalVar.h"
#include "../../IR/Function.h"
#include "LirFunction.h"
#include "../lirOperand/Addr.h"
#include <map>
#include <list>



GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class LirModule {
private :
  std::map<std::string, GlobalVar*> globalvars;
  // 维护一个双向 map 映射，因为 armCodegen 时，需要根据类型来赋值
  // std::list<Addr*> globalOperands;
  std::map<Value*, Addr*> globalMap;
  // 考虑到优化可能会做内联函数？（假设，在中端做 >__<）
  std::list<LirFunction*> lirfunctions;
  std::string name_;
public:
  LirModule() {}
  std::map<std::string, GlobalVar*> &getGlobalvars() {return globalvars;}
  std::list<LirFunction*> &getFunctions() {return lirfunctions;}
  // std::list<Addr*> &getGlobalOperands() {return globalOperands;}
  
  std::map<Value*, Addr*> &getGlobalMap() {return globalMap;}

  void setName(std::string &name) {name_ = name;}
};



GIMC_NAMESPACE_END


#endif
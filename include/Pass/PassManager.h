#ifndef PASS_H
#define PASS_H

#include "../Config.h"
#include "../IR/Module.h"
#include "../IR/Function.h"
#include "../Utils/IList.h"
#include "Mem2reg.h"
#include "Domination.h"
#include "Pres_Succs_Calculate.h"

USING_GIMC_NAMESPACE
GIMC_NAMESPACE_BEGIN

class PassManager {
private:
  // 针对函数的优化
  // 模板方法模式：钩子函数
  Function *func_;
  Domination dom;
  bool do_pres_succs = false;
  bool do_domination = false;
  bool do_mem2reg = false;
  bool do_def_use = false;
public:
  PassManager(Function *func) : func_(func) {}
  void calDefUse();
  void pres_succs();
  void mem2reg();
  void domination();
};

GIMC_NAMESPACE_END

#endif // PASS_H
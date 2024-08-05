#ifndef PASS_H
#define PASS_H

#include "../Config.h"
#include "../IR/Module.h"
#include "../IR/Function.h"
#include "../Utils/IList.h"
#include "Mem2reg.h"
#include "Domination.h"
// #include "Pres_Succs_Calculate.h"    // 无效了，已在 IR 中实现
#include "../IR/Inst.h"

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
  std::unordered_map<std::size_t, Instruction*> insts;  // 结合 std::hash 和异或计算 hash 值
public:
  PassManager(Function *func) : func_(func) {}
  // 计算 def-use
  void calDefUse();
  // 计算前驱后继
  void pres_succs();

  void mem2reg();
  //计算支配树 
  void domination();
  // 公共子表达式消除
  void GVN();
  void dfs_GVN(BBlock *v);
};

GIMC_NAMESPACE_END

#endif // PASS_H
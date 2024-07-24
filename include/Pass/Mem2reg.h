#ifndef MEM2REG_H
#define MEM2REG_H

#include "../Config.h"
#include "../IR/Module.h"
#include "../IR/Function.h"
#include "../Utils/IList.h"
#include "Domination.h"
#include <vector>
#include <unordered_map>

class Mem2reg {
private:
  // 启动 mem2reg 的前提是计算支配树 
  Domination &dom_;
  // 进行 mem2reg 函数所定义的变量集合
  std::unordered_map<Value*, std::vector<Value*>> allocaStacks;
public:
  Mem2reg(Function *func, Domination &dom);

  // 递归进行变量重命名
  void varRenameDFS(BBlock *bBlk);
};

#endif // MEM2REG_H
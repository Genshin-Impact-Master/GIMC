#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "../Config.h"
#include "Type.h"
#include "Value.h"
#include "ConstValue.h"
#include "../Utils/IList.h"
#include <string>
#include <vector>

#ifdef PRINT_CFG
#include <graphviz/gvc.h>
#endif

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class IRBuilder;
class BBlock;

class Function : public Value {
// @C++_Learn 引入友类，可以访问 private 变量
friend class IRBuilder;
private:
  int cnt = 0;                                            // function 中的递增命名计数器 
  std::vector<baseTypePtr> &arguTypes_;                   // 参数类型链表，注意是引用不是新的一个
  IList<Function, BBlock> blkList_;                       // 侵入式链表，结点全为 BBlock

  // 构建 CFG
  BBlock *exit_;                                           // 虚拟的 BBlock，作为函数的出口
public:
  Function(const std::string &fName, baseTypePtr funcType, std::vector<baseTypePtr> &arguTypes);

  // 添加 BBlock 到侵入式链表末端
  void addBBlock(BBlock* bBlk);

  int getCnt() {return cnt++;}

  // 清空 Function 中的基本块，包括基本块中的指令 
  void clearFunc();

  // 获取 BBlock List
  IList<Function, BBlock> &getBBlockList() {return blkList_;}

  // 获取 Function 出口 BBlock
  BBlock *getExitBBlock() {return exit_;}

#ifdef PRINT_CFG
  // 利用 graphviz 绘制 CFG
  void drawCFG();
#endif
};

GIMC_NAMESPACE_END

#endif // FUNCTION_H_
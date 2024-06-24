#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "../Config.h"
#include "Type.h"
#include "Value.h"
#include "ConstValue.h"
#include <string>
#include <vector>

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class IRBuilder;
class BBlock;

class Function : public Value {
// @C++_Learn 引入友类，可以访问 private 变量
friend class IRBuilder;
private:
  int cnt = 0;                                // function 中的递增命名计数器 
  std::vector<baseTypePtr> &arguTypes_;        // 参数类型链表，注意是引用不是新的一个
  std::vector<BBlock*> bBlocks_;               // BasicBlock 指针链表
public:
  Function(const std::string &fName, baseTypePtr funcType, std::vector<baseTypePtr> &arguTypes);

  void addBBlock(BBlock* bBlk) { bBlocks_.push_back(bBlk);}

  int getCnt() {return cnt++;}

  // 清空 Function 中的基本块，包括基本块中的指令 
  void clearFunc();
};

GIMC_NAMESPACE_END

#endif // FUNCTION_H_
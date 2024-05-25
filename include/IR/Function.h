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

class Function : Value {
// @C++_Learn 引入友类，可以访问 private 变量
friend class IRBuilder;
private:
  int cnt = 0;                                // function 中的递增命名计数器 
  std::vector<baseTypePtr> arguTypes_;        // 参数类型链表
  std::vector<BBlock*> bBlocks;               // BasicBlock 指针链表
public:
  Function(const std::string &fName, baseTypePtr funcType, std::vector<baseTypePtr> &arguTypes);

  void addBBlock(BBlock* bBlk) { bBlocks.push_back(bBlk);}

  int getCnt() {return cnt++;}
};

GIMC_NAMESPACE_END

#endif // FUNCTION_H_
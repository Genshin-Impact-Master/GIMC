#ifndef BLOCK_H_
#define BLOCK_H_

#include "../Config.h"
#include "Function.h"
#include "Value.h"
#include <string>
#include <vector>

GIMC_NAMESPACE_BEGIN

class Instruction;
class IRBuilder;

/**
 * 基本块 BasicBlock 类
 */  
class BBlock : public Value {
friend class IRBuilder;
private:
  std::vector<Instruction*> instructions; // 包含的 Instruction 指针链表
  Function *parent_;  // 指向所属的 Function
public:
  BBlock(const std::string &name, baseTypePtr type, Function *parent);
  
  // 默认名称建造基本块，其名称采用方程中默认递增名称一致
  BBlock(Function *parent);

  // 获取在方程中的计数
  int getCnt() {return parent_->getCnt();}
  
  // 插入指令到 Instruction 列表末尾
  void addInst(Instruction* inst) {instructions.push_back(inst);}
};


GIMC_NAMESPACE_END

#endif //BLOCK_H_
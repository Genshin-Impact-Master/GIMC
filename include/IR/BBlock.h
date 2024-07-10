#ifndef BLOCK_H_
#define BLOCK_H_

#include "../Config.h"
#include "Value.h"
#include "Function.h"
#include <string>
#include <vector>
#include "../Utils/IList.h"

USING_GIMC_NAMESPACE
GIMC_NAMESPACE_BEGIN

class Instruction;
class IRBuilder;
class Function;
/**
 * 基本块 BasicBlock 类
 */  
class BBlock : public Value {
friend class IRBuilder;
private:
  Function *parent_;                                          // 指向所属的 Function
  IList<BBlock, Instruction> instList_;                       // 侵入式链表，结点全为 instruction  
  INode<BBlock> blkNode_;                                     // 自身对应一个 BBlock 的结点
public:
  BBlock(const std::string &name, baseTypePtr type, Function *parent);
  
  // 默认名称建造基本块，其名称采用方程中默认递增名称一致
  BBlock(Function *parent);

  // 获取在方程中的计数
  int getCnt() {return parent_->getCnt();}
  
  // 插入指令到侵入式链表末端
  void addInst(Instruction* inst);

  // 清空基本块中的指令，注意是删除
  void clearBBlock();

  // 获取自身结点
  INode<BBlock> &getNode() {return blkNode_;}

  // 获取 Instruction List
  IList<BBlock, Instruction> &getInstList() {return instList_;}
};


GIMC_NAMESPACE_END

#endif //BLOCK_H_
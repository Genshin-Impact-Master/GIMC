#ifndef BLOCK_H_
#define BLOCK_H_

#include "../Config.h"
#include "Value.h"
#include "Function.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
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
  INode<BBlock> blkNode_;                                     // 自身对应一个 BBlock 的侵入式链表结点

  // CFG 组件
  std::unordered_set<BBlock*> pres_;                                   // 该基本块的前驱结点
  std::set<BBlock*> succs_;                                  // 该基本块的后继结点
public:
  BBlock(const std::string &name, baseTypePtr type, Function *parent);
  
  // 默认名称建造基本块，其名称采用方程中默认递增名称一致
  BBlock(Function *parent);

  // 获取在方程中的计数
  int getCnt() {return parent_->getCnt();}
  
  // 插入指令到侵入式链表末端
  void addInst(Instruction* inst);

  // 插入指定到侵入式链表头部
  void addHeadInst(Instruction *inst);

  // 删除某条指令
  void rmInst(Instruction *inst);

  // 清空基本块中的指令，注意是删除
  void clearBBlock();

  // 获取自身结点
  INode<BBlock> &getNode() {return blkNode_;}

  // 获取 Instruction List
  IList<BBlock, Instruction> &getInstList() {return instList_;}

  // 获取前驱结点链表
  std::unordered_set<BBlock*>& getPres() {return pres_;}

  // 获取后继结点链表
  std::set<BBlock*>& getSuccs() {return succs_;}

  // 向前驱结点链表中添加结点
  void addPreBBlock(BBlock *bBlk) {pres_.insert(bBlk);}

  // 向后继结点链表中添加结点
  void addSuccBBlock(BBlock *bBlk) {succs_.insert(bBlk);}

  // 向涉及到的两个 BBlock 分别添加到彼此的前驱或后继链表
  static void addEdge(BBlock *head, BBlock *rear) {head->addSuccBBlock(rear); rear->addPreBBlock(head);}

  // 获得 BBLock 中的指令条数
  int getInstCnt() {return instList_.getSize();}

  // 输出 BBLock 到 中端
  void coutBBlock();
};


GIMC_NAMESPACE_END

#endif //BLOCK_H_
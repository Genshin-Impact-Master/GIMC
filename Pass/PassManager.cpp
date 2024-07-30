#include "../include/Pass/PassManager.h"
#include "../include/IR/BBlock.h"
#include "../include/IR/Inst.h"
#include <functional>
#include <unordered_map>

void PassManager::calDefUse() {
  if (do_def_use) {
    return;
  }
  do_def_use = true;
  // INode<BBlock> *node = func_->getBBlockList().getHeadPtr();
  // while (!node->isEnd()) {
  //   node = node->getNext();
  //   BBlock *bBlk = node->getOwner();
  //   INode<Instruction> *insNode = bBlk->getInstList().getHeadPtr();
  //   while (!insNode->isEnd()) {
  //     insNode = insNode->getNext();
  //     Instruction *inst = insNode->getOwner();
  //     inst->calculateDef_Uses();
  //   }
  // }
}

void PassManager::pres_succs() {
  if (do_pres_succs)
    return;
  Pres_Succs_Calculate::calculate_Func(func_);
  do_pres_succs = true;
#ifdef PRINT_CFG
  // 使用 graphviz 画 main 的数据流图
  func_->drawCFG();
#endif
}

void PassManager::domination() {
  if (do_domination)
    return;
  if (!do_pres_succs)
    pres_succs();
  do_domination = true;
  dom.initialize(func_);
  dom.calculate();
  dom.getDomSuccs();
}

void PassManager::mem2reg() {
  if (do_mem2reg)
    return;
  if (!do_domination)
    domination();
  if (!do_def_use)
    calDefUse();
  do_mem2reg = true;
  // mem2reg 需要在支配树计算后计算
  if (!do_domination) {
      domination();
  }
  Mem2reg(func_, dom); 
}

// 为 Value* 和 Kind 添加计算的 hash code
// namespace std {
//   template<>
//   struct hash<std::vector<Value*>> {
//     std::size_t operator()(const std::vector<Value*> &ops) const {
//       std::size_t seed = 0;
//       for (const auto &op : ops) {
//         // 注意这里计算 hash 值时需要是有效数据才行
//         if (op != nullptr && op->isValid()) {
//           seed ^= std::hash<Value*>{}(op) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//         }
//       }
//       return seed;
//     }
//   }
//   template<>
//   struct hash<Value*> {
//     std::size_t operator()(const Value* op) const {
//       std::size_t seed = 0;
//       uint64_t tmp = static_cast<uint64_t>(op);
//       seed ^= static_cast<uint32_t>(tmp >> 32) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//       seed ^= static_cast<uint32_t>(tmp) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//     }
//   }
// };

void PassManager::GVN() {
  if (!do_domination)
    domination();
  // 检测是否为同一条指令，判断方法：Instruction 的 kind,ops_均相同。
  // 注意应当按照 支配树的 DFS 顺序进行基本块的遍历。
  
}

void PassManager::dfs_GVN(BBlock *v) {
  INode<Instruction> *instNode = v->getInstList().getHeadPtr();
  std::size_t hash = 0;
  while (!instNode->isEnd()) {
    instNode = instNode->getNext();
    Instruction *inst = instNode->getOwner();
    hash = inst->getHash();
    if (insts.find(hash) != insts.end()) {
      // 找到 inst，表明极可能为含义相同的 Instruction.保险起见再对比一次
      Instruction *find = insts[hash];

      /* @保险 */
      // if (!inst->isEqual(find)) continue;
      /*保险，再对比*/ 

            
    }
  }
  // for (auto u : dom.getDomSuccs(v)) {
  // }
}
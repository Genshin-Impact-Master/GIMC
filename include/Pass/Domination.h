#ifndef DOMINATION_H
#define DOMINATION_H

#include "Pass.h"
#include <unordered_map>
#include <unordered_set>
#include "../IR/Function.h"

USING_GIMC_NAMESPACE
GIMC_NAMESPACE_BEGIN

class Domination : public Pass {
private:
  //一个函数中总的支配集合，map 中键为基本块 vertex，值为 vertex 对应支配集。   
  std::unordered_map<BBlock*, std::unordered_set<BBlock*>> doms_;
  BBlock* root;

  // int size;                                                          // 待计算 function 中的 BBlock 结点个数
  std::unordered_map<BBlock*, int> semi;                                // 映射到半支配结点序号
  std::unordered_map<BBlock*, BBlock*> label;                           // 
  std::unordered_map<BBlock*, BBlock*> dom;                             // 映射到支配结点序号
  std::unordered_map<BBlock*, BBlock*> parent;                          // 映射到结点在生成树中的父结点
  std::unordered_map<BBlock*, BBlock*> ancestor;                        // 
  std::vector<BBlock*> vertex;                                          // 按 DFS 遍历顺序保存 BBlock* 结点 
  std::unordered_map<BBlock*, std::unordered_set<BBlock*>> bucket;      // 提供映射：结点->该结点所半支配的结点集合
  int cnt;                                                              // DFS 遍历时为各个结点编号
public:
  // Domination 的构造函数
  Domination(Function *func);

  // 支配集合的计算过程
  void calculate();

  // 深度优先遍历，构建生成树，并为结点编号
  void dfs(BBlock *v);

  // 将树边加入 "辅助森林"
  void link(BBlock *parent, BBlock *w);

  /** 
   * 论文中 EVAL 函数
   * 选出(v,w) 为 f->b 边（小编号到大编号的边）中最小的起始结点 v_min
   * 或选出(v,w) 为 b->f 边时，生成树中介于 v,m 间的具有最小半支配结点的结点 u.（其实为当前包括结点 v 森林中的树的 root 的子结点）
   */
  BBlock* eval(BBlock *node);

  void compress(BBlock *v);
  
};

GIMC_NAMESPACE_END
#endif // DOMINATION_H
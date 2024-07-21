#include "../include/Pass/Domination.h"
#include "../include/IR/BBlock.h"
#include "../include/Pass/Pres_Succs_Calculate.h"
#include "vector"

Domination::Domination(Function *func) : cnt(0), root(func->getEntryBBlock()) {
  // bool change = true;
  // while (change) {
  //   change = false;
  //   INode<BBlock> *bBlkNode = func->getBBlockList().getHeadPtr();
  //   while (!bBlkNode->isEnd()) {
  //     bBlkNode = bBlkNode->getNext();
  //     BBlock *bBlk = bBlkNode->getOwner();

  //     if (bBlk->getSuccs().empty() && bBlk->getPres().empty()) {
  //       // 说明没有进行前驱和后继结点的计算，因为添加了 exit_结点，
  //       // 所以即使只有一个基本块（一个函数必须包含 entry 块），也必然会有前驱或后继结点

  //       // 重新计算前驱与后继
  //       Pres_Succs_Calculate::calculate_Func(func);
  //     }

  //     if (doms_.find(bBlk) != doms_.end()) {
  //       // 找到结点
        
  //     }
  //   }
  // }

  // 将 semi, dom, parent 等初始化
  INode<BBlock> *iterator = func->getBBlockList().getHeadPtr();
  while (iterator->getNext()) {
    iterator = iterator->getNext();
    BBlock *bBlk = iterator->getOwner();
    semi[bBlk] = -1;                       // semi 初始值为 -1，表示 unvisited
    dom[bBlk] = nullptr;
    parent[bBlk] = nullptr;
    ancestor[bBlk] = nullptr;
  }

}

void Domination::calculate() {
  dfs(root);
  // 注意为从 0 开始
  for (int i = cnt - 1; i > 1; i--) {
    BBlock *w = vertex[i];
  // step 2
    for (auto v : w->getPres()) {
      BBlock *u = eval(v);
      if (semi[u] < semi[w]) {
        semi[w] = semi[u];
      }
    }
    if (bucket.find(vertex[semi[w]]) == bucket.end()) {
      // 未找到 semi[w] 的 bucket（即 semi[w] 的支配结点集合），需要新建
      std::unordered_set<BBlock*> vec;
      vec.insert(w);
      bucket[vertex[semi[w]]] = vec;        // @C++_Learn 虽然这里的局部变量 vec 被销毁了，但是 bucket 中加入的是 vec 的副本
    }
    bucket[vertex[semi[w]]].insert(w);      // w 加入 semi[w] 的半支配结点集合中
    link(parent[w], w);                     // parent[w],w 加入森林
  // step 3
    for (auto v : bucket[parent[w]]) {
      BBlock *u = eval(v);
      dom[v] = semi[u] < semi[v] ? u : parent[w];   // parent[w] 即 sdom[v]
    }
    bucket[parent[w]].clear();
  }

  // step 4
  for (int i = 1; i < cnt; i++) {
    BBlock *w = vertex[i];
    if (dom[w] != vertex[semi[w]]) {
      dom[w] = dom[dom[w]];
    }
  }
  dom[root] = root;
  for (int i = 0; i < cnt; i++) {
    fprintf(stdout, "the idom for %s is %s", vertex[i]->getName().c_str(), dom[vertex[i]]->getName().c_str());
  }
}

void Domination::dfs(BBlock *v) {
  semi[v] = cnt++;                 // 将结点表示为 visited
  label[v] = v;
  vertex.push_back(v);           // 将结点插入 vertex 中（按照 DFS 顺序可随机访问）
  for (auto w : v->getSuccs()) {
    if (semi[w] == -1) {
      parent[w] = v;
      dfs(w);
    }
  }
}

void Domination::compress(BBlock *v) {
  if (ancestor[ancestor[v]] != nullptr) {
    compress(ancestor[v]);
    if (semi[label[ancestor[v]]] < semi[label[v]]) {
      label[v] = label[ancestor[v]];
    }
    ancestor[v] = ancestor[ancestor[v]];
  }
}

void Domination::link(BBlock *parent, BBlock *w) {
  ancestor[w] = parent;
}

GIMC::BBlock* Domination::eval(BBlock *node) {
  if (ancestor[node] == nullptr)
    return node;
  compress(node);
  return label[node];
}

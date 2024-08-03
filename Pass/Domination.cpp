#include "../include/Pass/Domination.h"
#include "../include/IR/BBlock.h"
#include "../include/Pass/Pres_Succs_Calculate.h"
#include <vector>
#include <iostream>

void Domination::initialize(Function *func) {
  isInitialize = true;
  root = func->getEntryBBlock();
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
  if (!isInitialize) {
    error( "请先调用初始化函数");
    exit(1);
  }
  dfs(root);
  // 注意为从 0 开始
  for (int i = cnt - 1; i >= 1; i--) {
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

  // 打印查看
  // for (int i = 0; i < cnt; i++) {
  //   fprintf(stdout, "the idom for %s is %s\n", vertex[i]->getName().c_str(), dom[vertex[i]]->getName().c_str());
  // }
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

std::unordered_map<GIMC::BBlock*, std::vector<GIMC::BBlock*>>& Domination::getDomSuccs() {
  // 根据获取支配树信息 DFS 顺序
  if (!succs.empty()) {
    return succs;
  }
  for (int i = 1; i < cnt; i++) {
    if (succs.find(dom[vertex[i]]) == succs.end()) {
      std::vector<BBlock*> succ;
      succs[dom[vertex[i]]] = succ;
    }
    succs[dom[vertex[i]]].push_back(vertex[i]);
  }
  // domDFS(domDFS, root); 
  return succs;
}

std::unordered_map<BBlock*, std::unordered_set<BBlock*>> Domination::getFrontier(){
  if (domFrontier.size() != 0) {
    return domFrontier;
  }
  // 计算每个结点的直接支配边
  getDomSuccs();
  for (auto v : vertex) {
    // v 的直接支配 BBlock
    for (auto BBlk : succs[v]) {
      std::unordered_set<BBlock*> set;
      // 将 BBlock 的后继结点加入 v 的支配边界
      for (auto frontier : BBlk->getSuccs()) {
        set.insert(frontier);
      }
      domFrontier[v] = set;
    }
    // 如果没有直接支配的结点，则将其后继结点加入支配边界
    if (succs[v].size() == 0) {
      std::unordered_set<BBlock*> set;
      for (auto frontier : v->getSuccs()) {
        set.insert(frontier);
      }
      domFrontier[v] = set;
    }
  }

  // 打印检验
  for (auto v : vertex) {
    for (auto frontier : domFrontier[v]) {
      std::cout << "the frontier for " << v->getFullName() << " is " << frontier->getFullName() << std::endl;
    }
  }

  return domFrontier;
}

// void Domination::domDFS(std::vector<BBlock*> &domTree, BBlock *v) {
//   // 由于支配树特性，如此遍历不会重复
//   domTree.push_back(v);
//   for (auto succ : succs[v]) {
//     domDFS(domTree, succ);
//   }
// }
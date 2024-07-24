#include "../include/Pass/Mem2reg.h"
#include "../include/IR/Inst.h"
#include "iostream"
#include "../include/IR/IRBuilder.h"

Mem2reg::Mem2reg(Function *func, Domination &dom) : dom_(dom) {

  // 查找 alloca 指令
  
  // step 1 插入 phi
  INode<BBlock> *bBlkNode = func->getBBlockList().getHeadPtr();
  while (!bBlkNode->isEnd()) {
    bBlkNode = bBlkNode->getNext();
    BBlock *bBlk = bBlkNode->getOwner();
    INode<Instruction> *instNode = bBlk->getInstList().getHeadPtr();
    while (!instNode->isEnd()) {
      instNode = instNode->getNext();
      Instruction *inst = instNode->getOwner();
      // defBBlk 表示 alloca 指令 inst 的定义基本块
      // find 表示已经遍历过（插入 phi）的 BBlock
      std::unordered_set<BBlock*> find, defBBlk;    
      if (inst->isAllocaInst()) {
        // 若是 alloca 指令
        std::vector<Value*>& usesInst = inst->getUses();
        for (auto d : usesInst) {
          Instruction *i = dynamic_cast<Instruction*>(d);
          if (i->getKind() == InstKind::Store) {
            //  表明此条 Instruction 为变量定义
            BBlock *parent = i->getParent();
            defBBlk.insert(parent); 
          }
        }
        while (defBBlk.size() != 0) {
          BBlock *x = *defBBlk.begin();      // 找到定义的基本块
          defBBlk.erase(x);
          auto frontier = dom.getFrontier()[x];
          for (auto y : frontier) {
            if (find.find(y) == find.end()) {
              // 若 y 不属于 find
              // 在 y 的最前面插入 phi 结点
              std::vector<Value*> maps;
              maps.push_back(inst);         // 用于暂存记录 phi 指令所指代变量
              std::shared_ptr<PointerType> ptr = std::dynamic_pointer_cast<PointerType>(inst->getType());
              Phi *phi = new Phi(inst->getName(), ptr->getBaseType(), y, maps);
              // 此时插入的 phi 指令还没有参数
              y->addHeadInst(phi);
              find.insert(y);
              if (defBBlk.find(y) == find.end()) {
                // 需要进行迭代支配边界 即 DF(DF(y))
                defBBlk.insert(y);
              }
            }
          }
        }
      }
    }
  }  

  // step 2 变量重命名，基于栈的到达定义分析，按照支配树 DFS 顺序
  varRenameDFS(dom_.getRoot());
}

void Mem2reg::varRenameDFS(BBlock *bBlk) {
  // bBlk->coutBBlock();
  std::unordered_map<GIMC::BBlock*, std::vector<GIMC::BBlock*>> &domSuccs = dom_.getDomSuccs();
  INode<Instruction> *instNode = bBlk->getInstList().getHeadPtr();
  std::vector<Value*> allocaUpdates;                         // 记录发生改变的变量名称即 alloca，注意可以多次改变故使用 vector
  while (!instNode->isEnd()) {
    instNode = instNode->getNext();
    Instruction *inst = instNode->getOwner();
    InstKind kind = inst->getKind();
    if (kind == InstKind::Alloca) {
      // 若是 alloca 指令，直接删除，并建立相关变量栈
      bBlk->rmInst(inst);
      std::vector<Value*> stack;
      allocaStacks[inst] = stack;
    }
    else if (kind == InstKind::Store) {
      bBlk->rmInst(inst);
      // 若是 store 指令，将需要 store 的值入栈
      Store *store = dynamic_cast<Store*>(inst);
      Value *varPtr = store->getPtr();
      Value *input = store->getInput();
      allocaStacks[varPtr].push_back(input);
      std::cout << "将 " << varPtr->getName() << " 的新值 " << input->getFullName() << " 加入栈中" << std::endl;
      allocaUpdates.push_back(varPtr);
      // std::cout << "当前的更新值有" << allocaUpdates.size() << " 个" << std::endl;
    }
    else if (kind == InstKind::Load) {
      bBlk->rmInst(inst);
      // bBlk->coutBBlock();
      // 将使用了此 load 值的变量用当前栈顶元素替换
      // 可想而知，这是对于 %load 的 uses 进行替换
      Value *varPtr = dynamic_cast<Load*>(inst)->getPtr();
      auto uses = inst->getUses();                          // 注意使用了此 load 的指令可能在其他基本块中
      for (int k = 0; k < static_cast<int>(uses.size()); k++) {
        Instruction *v = dynamic_cast<Instruction*>(uses[k]);
        // 在使用了该 load 的 Instruction *v 的 ops_ 中
        std::vector<Value*> &v_defs = v->getDefs(); 
        for (int j = 0; j < static_cast<int>(v_defs.size()); j++) {
          if (v_defs[j] == inst) {
            // 若两者是同一个指针，则用 allocaStacks[varPtr] 的栈顶元素替换
            std::vector<Value*> &stack = allocaStacks[varPtr]; 
            Value *newest  = stack[stack.size() - 1];
            // for (auto man : allocaStacks[varPtr]) {
            //   std::cout << varPtr->getFullName() << " 还剩 " << man->getFullName() <<std::endl;
            // }
            std::cout << "使用 " << newest->getFullName() << " 替换 " << v_defs[j]->getFullName() << std::endl;
            v_defs[j] = newest;
            break;
          }
        }
      }
    }
    else if (kind == InstKind::Phi) {
      // 对于 phi 指令，同样需要更新栈
      Phi *phi = dynamic_cast<Phi*>(inst);
      Value *varPtr = phi->getAllocaPtr();
      allocaStacks[varPtr].push_back(phi);
      std::cout << "将 " << varPtr->getName() << " 的新值 " << phi->getFullName() << " 加入栈中" << std::endl;
      allocaUpdates.push_back(varPtr);
    }
  }

  // 对该基本块的后继基本块中的 phi 指令进行更新维护
  for (auto v : bBlk->getSuccs()) {
    INode<Instruction> *instNode = v->getInstList().getHeadPtr();
    while (!instNode->isEnd()) {
      instNode = instNode->getNext();
      Phi *inst = dynamic_cast<Phi*>(instNode->getOwner());
      // 因为 phi 都是插入链表头部，故只要有一个非 phi 函数则 break
      if (!inst) {
        break;
      }
      Value *varPtr = inst->getAllocaPtr();
      Value *newest = allocaStacks[varPtr].back();
      std::vector<Value*> &phiOps = inst->getOps();
      phiOps.push_back(newest);
      phiOps.push_back(bBlk);
      inst->calculateDef_Uses();
    }
  }

  // 递归遍历
  for (auto v : domSuccs[bBlk]) {
    varRenameDFS(v);
  }

  // 退栈
  for (auto varPtr : allocaUpdates) {
    Value *right = allocaStacks[varPtr].back();
    allocaStacks[varPtr].pop_back();
    std::cout << "将 " << varPtr->getName() << " " << right->getFullName() << " 弹出栈中" << std::endl;
  }
}
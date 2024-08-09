#include "../include/LirToArm/LirToArm.h"
#include <list>

USING_GIMC_NAMESPACE

void LirToArm::genModule() {
  // 准备工作
  smartOut(".arch", "armv7");
  smartOut(".fpu", "softvfp");

  std::list<LirFunction *> funcs = lirModule_.getFunctions();
  for (auto func : funcs) {
    genFunction(func);
  }

  // 输出全局变量以及常量池
  Output_Arm_global();
}

void LirToArm::genFunction(LirFunction *func) {
  std::string &name = func->getFuncName();
  smartOut(".text");
  smartOut(".align", 3);
  smartOut(".global", name);
  smartOut(".syntax", "unified");
  smartOut(".thumb");
  smartOut(".thumb_func");
  smartOut(".type", name, "\%function");
  armOut << name << ":" << std::endl;

  // 预备的栈处理工作，fp 设为 r7
  smartOut("/* ******** 函数预处理 ******** */");
  smartOut("@ 将 fp 压栈");
  push(ARM_REGS[FP_REG]);
  smartOut("@ 将 lr 压栈");
  push("lr");
  int offset = func->getStackSize();
  sub("sp", "sp", "#" + std::to_string(offset));
  add(ARM_REGS[FP_REG], IPhyReg::SP->toString(), "#0");

  // 处理基本块
  LirBlock *entry = func->getEntry();
  genBlock(entry);

  INode<LirBlock> *blkNode = &entry->getNode();
  while (!blkNode->isEnd()) {
    // 除了入口基本块外，均需要输出其标签（实际上入口基本块标签输出也行）类似下方
    // Func:
    // entry_Func:
    blkNode = blkNode->getNext();
    LirBlock *blk = blkNode->getOwner();
    armOut << blk->getLabel() << ":" << std::endl;
    genBlock(blk);
  }
}

void LirToArm::genInst(LirInst *lir_inst) {
  LirBlock *blk = lir_inst->getParent();
  LirFunction *func = blk->getParent();
  LirOperand *opd1 = lir_inst->getOpd1();
  LirOperand *opd2 = lir_inst->getOpd2();
  LirOperand *opd3 = lir_inst->getOpd3();
  switch (lir_inst->getKind()) {
  case LirInstKind::Add: {
    add(lir_inst->getOperandName(opd1),
        lir_inst->getOperandName(opd2),
        lir_inst->getOperandName(opd3));
    break;
  }

  case LirInstKind::Sub: {
    sub(lir_inst->getOperandName(opd1),
        lir_inst->getOperandName(opd2),
        lir_inst->getOperandName(opd3));
    break;
  }

  case LirInstKind::Mul: {
    mul(lir_inst->getOperandName(opd1),
        lir_inst->getOperandName(opd2),
        lir_inst->getOperandName(opd3));
    break;
  }

  case LirInstKind::Div: {
    div(lir_inst->getOperandName(opd1),
        lir_inst->getOperandName(opd2),
        lir_inst->getOperandName(opd3));
    break;
  }

  case LirInstKind::Addf: {
    addf(lir_inst->getOperandName(opd1),
         lir_inst->getOperandName(opd2),
         lir_inst->getOperandName(opd3));
    break;
  }

  case LirInstKind::Subf: {
    subf(lir_inst->getOperandName(opd1),
         lir_inst->getOperandName(opd2),
         lir_inst->getOperandName(opd3));
    break;
  }

  case LirInstKind::Mulf: {
    mulf(lir_inst->getOperandName(opd1),
         lir_inst->getOperandName(opd2),
         lir_inst->getOperandName(opd3));
    break;
  }

  case LirInstKind::Divf: {
    divf(lir_inst->getOperandName(opd1),
         lir_inst->getOperandName(opd2),
         lir_inst->getOperandName(opd3));
    break;
  }

  case LirInstKind::Rsb: {
    rsb(lir_inst->getOperandName(opd1),
        lir_inst->getOperandName(opd2),
        lir_inst->getOperandName(opd3));
    break;
  }

  case LirInstKind::Fp2Int: {
    int2fp(lir_inst->getOperandName(opd1),
           lir_inst->getOperandName(opd2));
    break;
  }

  case LirInstKind::Int2Fp: {
    fp2int(lir_inst->getOperandName(opd1),
           lir_inst->getOperandName(opd2));
    break;
  }

  case LirInstKind::Store: {
    armOut << "str"
           << "\t" << opd2->toString() << ","
           << "[" << opd3->toString() << "]";
    armOut << "\n";
    break;
  }

  case LirInstKind::Load: {
    if (opd1->isInt()) {
      armOut << "ldr"
             << "\t" << opd1->toString() << ","
             << "[" << opd2->toString() << "]";
      armOut << "\n";
      break;
    } else {
      armOut << "vldr.32"
             << "\t" << opd1->toString() << ","
             << "[" << opd2->toString() << "]";
      armOut << "\n";
      break;
    }
  }

  case LirInstKind::Call: {
    armOut << "bl"
           << "\t" << opd2->toString();
    armOut << "\n";
    break;
  }

  case LirInstKind::Ret: {
    smartOut("add", ARM_REGS[FP_REG], ARM_REGS[FP_REG], func->getStackSize());
    armOut << " mov     sp, r7\npop     {r7, pc}\n";
    break;
  }
  // todo 条件执行
  case LirInstKind::Move: {
    std::string s = opd2->toString();
    LirArmStatus st = lir_inst->getStatus();
    int status = static_cast<int>(st);
    std::string cond = ST_ARM_STATUS[status];
    if (opd2->isFloat() && opd2->isImm()) {
      float f = atof(s.c_str());
      int i = *(int *)&f;
      armOut << "movw" << cond
             << "\t" << opd1->toString() << ", #" << i % 65536
             << "\n";
      armOut << "movt"
             << "\t" << opd1->toString() << "," << i / 65536
             << "\n";
      break;
    }
    if (opd2->isInt() && opd2->isImm()) {
      int i = atoi(s.c_str());
      armOut << "movw" << cond
             << "\t" << opd1->toString() << ", #" << i % 65536
             << "\n";
      armOut << "movt"
             << "\t" << opd1->toString() << "," << i / 65536
             << "\n";
      break;
    }
    else {
      smartOut("mov", opd1->toString(), opd2->toString());
    }
  }

  case LirInstKind::cmp: {
    smartOut("cmp", opd2->toString(), opd3->toString());
    break;
  }

  case LirInstKind::Br: {
    armOut << "b" << ST_ARM_STATUS[static_cast<int>(lir_inst->getStatus())] << opd2->toString() << std::endl;
    break;
  }

  case LirInstKind::Push: {
    smartOut("push", opd2->toString());
    break;
  }

  case LirInstKind::Pop: {
    smartOut("pop", opd2->toString());
    break;
  }
  default:
    break;
  }
}

void LirToArm::genBlock(LirBlock *blk) {

  armOut << blk->getLabel() << ":"
         << "\n"; // 输出 Block 的标签

  IList<LirBlock, LirInst> &Inst_List = blk->getInst();
  INode<LirInst> *node = Inst_List.getHeadPtr();

  while (!node->isEnd()) {
    node = node->getNext();
    genInst(node->getOwner());
  }
}

void LirToArm::Output_Arm_global() {
  for (auto iter : lirModule_.getGlobalMap()) {
    GlobalVar *var = dynamic_cast<GlobalVar*>(iter.first);
    armOut << iter.second->toString() << ":"
           << "\n";
    if (var) {
      // 说明为全局变量
      armOut << var->getName() << ":" << std::endl;
      cycleGlobal(var);
    }
  }

  //   if (TypeBase::isInteger(iter.second->getValueType())) {
  //     for (auto iter_value : s) {
  //       std::cout << "\t";
  //       std::cout << ".long"
  //                 << "\t";
  //       std::cout << iter_value->getName();
  //       std::cout << "\n";
  //       smartOut(".long", iter_value->getName());
  //     }
  //   }

  //   if (TypeBase::isFloat(iter.second->getValueType())) {
  //     for (auto iter_value : s) {
  //       std::cout << "\t";
  //       std::cout << ".long"
  //                 << "\t";
  //       std::cout << iter_value->getName();
  //       std::cout << "\n";
  //       smartOut(".long", iter_value->getName());
  //     }
  //   }
  // }
}

void LirToArm::cycleGlobal(GlobalVar* var) {
  std::shared_ptr<PointerType> ptr = std::dynamic_pointer_cast<PointerType>(var->getType());
  baseTypePtr base = ptr->getBaseType();
  if (ptr == nullptr) {
    error("LirToArm:cycleGlobal: 全局变量必须为指针类型");
  }
  std::vector<Value*> &values = var->getGlobalVarValues();
  if (values.size() == 0) {
    smartOut(".space", base->getSize());
  }
  else {
    if (TypeBase::isPointer(base)) {
      // 如果仍然为指针类型，那么仍可以递归下降
      for (auto g : values) {
        GlobalVar *subG = dynamic_cast<GlobalVar*>(g);
        if (subG)
          cycleGlobal(subG);   
        error("LirToArm:cycleGlobal: 全局变量数组类型除了第一维为 ConstValue* 外均需要为 GlobalVar*");
      }
    }
    else {
      // 非数组类型，直接输出
      if (dynamic_cast<ConstValue*>(var) == nullptr) {
        error("LirToArm:cycleGlobal: 全局变量必须使用常量初始化");
      }
      smartOut(".word", var->getName());
    }
  }
}
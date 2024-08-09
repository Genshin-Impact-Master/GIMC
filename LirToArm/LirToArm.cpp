#include "../include/LirToArm/LirToArm.h"
#include <list>

USING_GIMC_NAMESPACE

void LirToArm::genModule() {
  // 准备工作
  smartOut(".arch", "armv7");
  smartOut(".fpu", "softvfp");
  
  std::list<LirFunction*> funcs = lirModule_.getFunctions();
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
  push(FP_REG);
  smartOut("@ 将 lr 压栈");
  push("lr");
  int offset = getStackSize(func);
  sub("sp", "sp", IMM(offset));
  add(FP_REG, sp, IMM(0));

  // 处理基本块
  LirBlock *entry = func->getEntry();
  genBlock(entry);

  INode<LirBlock> blkNode = entry->getNode();
  while (!blkNode.isEnd()) {
    // 除了入口基本块外，均需要输出其标签（实际上入口基本块标签输出也行）类似下方
    // Func:
    // entry_Func:
    blkNode = blkNode.getNext();
    LirBlock *blk = blkNode.getOwner();
    armOut << blk->getLabel() << ":" << std::endl;
    genBlock(blk);
  }  
}

void LirToArm::genInst(LirInst *lir_inst)
{
    LirBlock *blk = lir_inst->getParent();
    LirFunction *func = blk->getParent();
    switch(lir_inst->getKind())
    {
      case LirInstKind::Add:
      {
        add(lir_inst->getOperandName(lir_inst->getOpd1()),lir_inst->getOperandName(lir_inst->getOpd2()),lir_inst->getOperandName(lir_inst->getOpd3()));
        break;
      }
      
      case LirInstKind::Sub:
      {
        sub(lir_inst->getOperandName(lir_inst->getOpd1()),lir_inst->getOperandName(lir_inst->getOpd2()),lir_inst->getOperandName(lir_inst->getOpd3()));
        break;
      }

      case LirInstKind::Mul:
      {
        mul(lir_inst->getOperandName(lir_inst->getOpd1()),lir_inst->getOperandName(lir_inst->getOpd2()),lir_inst->getOperandName(lir_inst->getOpd3()));
        break;
      }

      case LirInstKind::Div:
      {
        div(lir_inst->getOperandName(lir_inst->getOpd1()),lir_inst->getOperandName(lir_inst->getOpd2()),lir_inst->getOperandName(lir_inst->getOpd3()));
        break;
      }

      case LirInstKind::Addf:
      {
        addf(lir_inst->getOperandName(lir_inst->getOpd1()),lir_inst->getOperandName(lir_inst->getOpd2()),lir_inst->getOperandName(lir_inst->getOpd3()));
        break;
      }

      case LirInstKind::Subf:
      {
        subf(lir_inst->getOperandName(lir_inst->getOpd1()),lir_inst->getOperandName(lir_inst->getOpd2()),lir_inst->getOperandName(lir_inst->getOpd3()));
        break;
      }

      case LirInstKind::Mulf:
      {
        mulf(lir_inst->getOperandName(lir_inst->getOpd1()),lir_inst->getOperandName(lir_inst->getOpd2()),lir_inst->getOperandName(lir_inst->getOpd3()));
        break;
      }

      case LirInstKind::Divf:
      {
        divf(lir_inst->getOperandName(lir_inst->getOpd1()),lir_inst->getOperandName(lir_inst->getOpd2()),lir_inst->getOperandName(lir_inst->getOpd3()));
        break;
      }

      case LirInstKind::Rsb:
      {
        rsb(lir_inst->getOperandName(lir_inst->getOpd1()),lir_inst->getOperandName(lir_inst->getOpd2()),lir_inst->getOperandName(lir_inst->getOpd3()));
        break;
      }

      case LirInstKind::Fp2Int:
      {
        int2fp(lir_inst->getOperandName(lir_inst->getOpd1()),lir_inst->getOperandName(lir_inst->getOpd2()));
        break;
      }

      case LirInstKind::Int2Fp:
      {
        fp2int(lir_inst->getOperandName(lir_inst->getOpd1()),lir_inst->getOperandName(lir_inst->getOpd2()));
        break;
      }

      case LirInstKind::Store:
      {
        armOut<<"str"<<"\t"<<lir_inst->getOpd2()->toString()<<","<<"["<<lir_inst->getOpd3()->toString()<<"]";
        armOut<<"\n";
        break;
      }

      case LirInstKind::Load:
      {
        if (lir_inst->getOpd1()->isInt())
        {
          armOut<<"ldr"<<"\t"<<lir_inst->getOpd1()->toString()<<","<<"["<<lir_inst->getOpd2()->toString()<<"]";
          armOut<<"\n";
          break;
        }
        else
        {
          armOut<<"vldr.32"<<"\t"<<lir_inst->getOpd1()->toString()<<","<<"["<<lir_inst->getOpd2()->toString()<<"]";
          armOut<<"\n";
          break;
        }
        
      }

      case LirInstKind::Call:
      {
        armOut<<"bl"<<"\t"<<lir_inst->getOpd2()->toString();
        armOut<<"\n";
        break;
      }

      case LirInstKind::Ret:
      {
        smartOut("add", ARM_REGS[FP_REG],ARM_REGS[FP_REG],func->getStackSize()); 
        armOut<<" mov     sp, r7\npop     {r7, pc}\n";
        break;
      }

      case LirInstKind::Move:
      {
         std::string s =lir_inst->getOpd2()->toString();
         if(lir_inst->getOpd2()->isFloat() && lir_inst->getOpd2()->isImm())
         {
            float f = atof(s.c_str());
            int i = *(int*)&f;
            armOut << "movw"<<"\t"<<lir_inst->getOpd1()->toString()<<", #"<<i%65536<<"\n";
            armOut << "movt"<<"\t"<<lir_inst->getOpd1()->toString()<<","<<i/65536<<"\n";
            break;
         }
         if(lir_inst->getOpd2()->isInt() && lir_inst->getOpd2()->isImm())
         {
            int i = atoi(s.c_str());
            armOut << "movw"<<"\t"<<lir_inst->getOpd1()->toString()<<", #"<<i%65536<<"\n";
            armOut << "movt"<<"\t"<<lir_inst->getOpd1()->toString()<<","<<i/65536<<"\n";
            break;
         }

      }
    }
}

void LirToArm::genBlock(LirBlock *blk) {

  armOut<<blk->getLabel()
        <<":"
        <<"\n";   //输出 Block 的标签

  IList<LirBlock, LirInst> &Inst_List = blk->getInst();
  INode<LirInst> *node = Inst_List.getHeadPtr();

  while (!node->isEnd())
  {
    node=node->getNext();
    genInst(node->getOwner()); 
  }
}



void LirToArm::Output_Arm_global() {
  for (auto iter : lirModule_.getGlobalOperands()) // iter 迭代所有的全局变量
    {
      std::cout << iter.first << ":"
                << "\n";
      armOut << iter.first << ":"
              << "\n";
      std::vector<Value *> &s = iter.second->getGlobalVarValues();

      if (TypeBase::isInteger(iter.second->getValueType())) {
        for (auto iter_value : s) {
          std::cout << "\t";
          std::cout << ".long"
                    << "\t";
          std::cout << iter_value->getName();
          std::cout << "\n";
          smartOut(".long", iter_value->getName());
        }
      }

      if (TypeBase::isFloat(iter.second->getValueType())) {
        for (auto iter_value : s) {
          std::cout << "\t";
          std::cout << ".long"
                    << "\t";
          std::cout << iter_value->getName();
          std::cout << "\n";
          smartOut(".long", iter_value->getName());
        }
      }
}
}
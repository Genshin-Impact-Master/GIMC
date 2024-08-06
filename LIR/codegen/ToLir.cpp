#include "../../include/LIR/codegen/ToLir.h"
#include <set>

USING_GIMC_NAMESPACE

ToLir::ToLir(Module irModule) : irModule(irModule) {
  lirModule.setName(irModule.getName());
};

LirModule& ToLir::moduleGen() {
    // 全局变量将 <label> 加入 map
    for(GlobalVar* globalVar : *irModule.getGlobalVars()) {
        lirModule.getGlobalvars()[globalVar->getName()] = globalVar;
        Addr *addr = new Addr(globalVar->getName());
        bindGlobal(globalVar, addr);
    }

    // 将 Function 的 <label> (名字) 加入 map 
    for (Function *func : irModule.getFuncDeclares()) {
      bindGlobal(func, new Addr(func->getName()));
    }

    for(Function* func : *(irModule.getFuncDefs())) {
        baseTypePtr funcType = func->getType();
        std::vector<baseTypePtr> paramTypes = func->getArguTypes();
        std::vector<Value> funcParams = func->getArgus();
        int paramsCnt = paramTypes.size();
        std::vector<Value> lirFuncParams = std::vector<Value>();
        int intcnt = 0;
        int floatcnt = 0;

        LirFunction *lirFunc = new LirFunction(func->getName(), paramsCnt);
        std::set<int> idx = std::set<int>();
        
        //  处理 Function 参数
        for(int i = 0; i < paramsCnt; i++) {
            Value param = funcParams[i];
            if(!TypeBase::isFloat(param.getType())) {
                intcnt++;
                idx.insert(i);
                lirFuncParams.push_back(param);
            }
            if(intcnt >= 4) {
                break;
            }
        }
        
        for(int i = 0; i < paramsCnt; i++) {
            Value param = funcParams[i];
            if(TypeBase::isFloat(param.getType())) {
                floatcnt++;
                idx.insert(i);
                lirFuncParams.push_back(param);
            }
            if(floatcnt >= 16) {
                break;
            }
        }

        for(int i = 0; i < paramsCnt; i++) {
            Value param = funcParams[i];
            if(idx.count(i) == 0) {
                lirFuncParams.push_back(param);
            }
        }

        lirFunc.setLirFuncParams(lirFuncParams);
        lirFunc.setIParamsCnt(intcnt);
        lirFunc.setFParamsCnt(floatcnt);
        lirFunc.setReturnType(func->getType());
        lirModule.getFunctions().push_back(lirFunc);
        funcMap[func] = lirFunc;

        // 先为 BBLock 分配标签，生成 LirBlock 并加入 LirFunction 中
        if(func->getBBlockList().getSize() > 0) {
            INode<BBlock> *blockNode = func->getBBlockList().getHeadPtr();
            // 由于 IR 中的 correctCheck 每个函数一定有 entry 块
            func->setEntry(blockNode->getNext()->getOwner());
            while(!blockNode->isEnd()) {
                blockNode = blockNode->getNext();
                BBlock *block = blockNode->getOwner();
                std::string lirBlkName = block->getName() + "_" + func->getName();
                LirBlock *lirBlock = new LirBlock(&lirFunc, lirBlkName);

                // 将 LIR 基本块加入 LIRFunction
                lirFunc->appendBlk(lirBlock);
                // 构建 IR 基本块到 LIR 基本块映射
                blockMap[block] = lirBlock;
                // 为 LIR 基本块分配全局标签
                bindGlobal(block, new Addr(lirBlkName));
            }
        }

        INode<BBlock> *blockNode = func->getBBlockList().getHeadPtr();
        while(!blockNode->isEnd()) {
            blockNode = blockNode->getNext();
            BBlock *block = blockNode->getOwner();
            LirBlock *lirBlock = blockMap[block];
            for(BBlock* preBlock : block->getPres()) {
                lirBlock->addPres(blockMap[preBlock]);
            }

            std::set<BBlock*> lirSuccs = block->getSuccs();
            if(lirSuccs.size() == 1) {
                lirBlock->setTrueLirSucc(blockMap[*lirSuccs.begin()]);
            }else if(lirSuccs.size() == 2) {
                lirBlock->setTrueLirSucc(blockMap[*lirSuccs.begin()]);
                lirBlock->setFalseLirSucc(blockMap[*lirSuccs.end()]);
            }
        }

        
    
    }

    for(Function* func : *(irModule.getFuncDefs())) {
        LirFunction* lirFunc = funcMap[func];
        INode<BBlock> *blockNode = func->getBBlockList().getHeadPtr();
        while(!blockNode->isEnd()) {
            blockNode = blockNode->getNext();
            BBlock *bBLk = blockNode->getOwner();

            // globalMap 无优化阶段用不到，对于每个 BBlock，每次需要清空 valMap 中的局部变量
            // globalMap.clear();

            instResolve(bBLk);   
        }
    }
    return lirModule;
}

void ToLir::instResolve(BBlock *block) {
    // 清除局部变量
    clearLocal();

    LirFunction* lirFunc = funcMap[block->getParent()];
    LirBlock* lirBlock = blockMap[block];
    INode<Instruction> *instNode = block->getInstList().getHeadPtr();
    while(!instNode->isEnd()) {
        instNode = instNode->getNext();
        Instruction* inst = instNode->getOwner();
        InstKind kind = inst->getKind();

        //TODO:已经实现了整除加减乘除，需要实现其他二元指令
        if(kind > InstKind::BinaryOPBegin && kind < InstKind::BinaryOpEnd) {
            BinaryInst* i = dynamic_cast<BinaryInst*>(inst);
            Value *lhs = i->getLhs();
            Value *rhs = i->getRhs();
            LirOperand *lhsReg, *rhsReg, *dstReg;
            LirInstKind lirInstKind;
            switch (i->getKind())
            {
                
            case InstKind::Add:
                if(dynamic_cast<ConstValue*>(lhs)) {
                    rhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    lhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                }
                else {
                    lhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    rhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                }
                dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
                lirInstKind = LirInstKind::Add;
                LirBinary *lirBin = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(lirBin);
                break;

            case InstKind::Sub:
                if(dynamic_cast<ConstValue*>(lhs)) {
                    rhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    lhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                    lirInstKind = LirInstKind::Rsb;//逆向减法
                }else {
                    lhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    rhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                    lirInstKind =LirInstKind::Sub;
                }
                dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
                LirBinary *lirBin = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(lirBin);
                break;

            case InstKind::Mul:
                if(dynamic_cast<ConstValue*>(lhs)) {
                    rhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    lhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                }
                else {
                    lhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    rhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                }
                dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
                lirInstKind = LirInstKind::Mul;
                LirBinary *lirBin = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(lirBin);
                break;

            case InstKind::Div:
            //除法不可以交换
                lhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                rhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
                lirInstKind = LirInstKind::Div;
                LirBinary *lirBin = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(lirBin);
                break;
            
            case InstKind::Addf:     
                if(dynamic_cast<ConstValue*>(lhs)) {
                    rhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    lhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                }
                else {
                    lhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    rhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                }
                dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
                lirInstKind = LirInstKind::Addf;
                LirBinary *lirBin = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(lirBin);
                break;
            
            case InstKind::Subf:
                if(dynamic_cast<ConstValue*>(lhs)) {
                    rhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    lhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                    lirInstKind = LirInstKind::Rsbf;//逆向减法
                }else {
                    lhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    rhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                    lirInstKind =LirInstKind::Subf;
                }
                dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
                LirBinary *lirBin = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(lirBin);
                break;
            
            case InstKind::Mulf:
                if(dynamic_cast<ConstValue*>(lhs)) {
                    rhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    lhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                }
                else {
                    lhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                    rhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                }
                dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
                lirInstKind = LirInstKind::Mulf;
                LirBinary *lirBin = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(lirBin);
                break;
            
            case InstKind::Divf:
                lhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                rhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
                lirInstKind = LirInstKind::Divf;
                LirBinary *lirBin = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(lirBin);
                break;
            
            // @todo 通过除法乘法减法来做 
            case InstKind::SRem:
                lhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                rhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
                lirInstKind = LirInstKind::Divf;
                LirBinary *lirBin = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(lirBin);
                break;
            default:
                break;
            }

            // 接下来将解析出的三个 reg 放入 <Value*, LirOperand*> map 中

        }

        else if(kind == InstKind::Alloca) {
          // 本身就是 ptr，放入 stackOffsetMap 中
          lirFunc->putLocalVar(inst);
        }

        else if (kind == InstKind::Store) {
          Store *i = dynamic_cast<Store*>(inst);
          Value *input = i->getInput();
          Value *ptr = i->getPtr();       // 注意这个 ptr 可能是形参，全局变量，局部变量
          LirOperand *data = getBindOperand(input);    // 获取输入的 operand
          LirOperand *offset = getBindOperand(ptr);
          LirStore *lirStore = new LirStore(lirBlock, offset, data);
          lirBlock->addInst(lirStore);
        }

        else if (kind == InstKind::Load) {
          Load *i = dynamic_cast<Load*>(inst);
          Value *ptr = i->getPtr();
          LirOperand *dst = operandResolve(inst, lirFunc, lirBlock);  // load 进的寄存器
          LirOperand *from = getBindOperand(ptr);
          LirLoad *lirLoad = new LirLoad(lirBlock, dst, from);
          lirBlock->addInst(lirLoad);
        }

        else if (kind == InstKind::Call) {
          
        }

        else if (kind == InstKind::Ret) {
          Ret *i = dynamic_cast<Ret*>(inst);
          Value *ret = i->getRetValue();
          LirOperand *retVal = getBindOperand(ret);
          LirRet *lirRet = new LirRet(lirBlock, retVal);
          lirBlock->addInst(lirRet);
        }

        else if (kind == InstKind::Icmp) {
          Icmp *i = dynamic_cast<Icmp*>(inst);
          Value *first = i->getFirst();
          Value *second = i->getSecond();
          LirOperand *opd1 = getBindOperand(first);
          LirOperand *opd2 = getBindOperand(second);
          LirCmp lirCmp = new LirCmp(lirBlock, opd1, opd2);
          lirBlock->addInst(lirCmp);
        }

        else if (kind == InstKind::Fcmp) {
          Fcmp *i = dynamic_cast<Fcmp*>(inst);
          Value *first = i->getFirst();
          Value *second = i->getSecond();
          LirOperand *opd1 = getBindOperand(first);
          LirOperand *opd2 = getBindOperand(second);
          LirCmp lirCmp = new LirCmp(lirBlock, opd1, opd2);
          lirBlock->addInst(lirCmp);
        }

        else if (kind == InstKind::Br) {
          // 根据是否是无条件跳转
          Br *i = dynamic_cast<Br*>(inst);
          Value *bBlkTrue = i->getTrueBBlk();
          LirOperand *addr = getBindOperand(bBlkTrue);
          if (i->isUnconditional()) {
            LirBr lirBr = new LirBr(lirBlock, addr, LirArmStatus::NO_Cond);
            lirBlock->addInst(lirBr);
          }
          else {
            // 加入两条 LirBr 指令
            Value *bBlkFalse = i->getFalseBBlk();
            Instruction *cond = dynamic_cast<Instruction*>(i->getCond());
            CondKind ckind = cond->getCondKind();
            LirOperand *falseAddr = getBindOperand(bBlkTrue);
            LirArmStatus status;
            if (cond->getKind() == InstKind::Fcmp) {
              switch (ckind.fCond) {
                case FCondKind::Oeq:
                  status = LirArmStatus::EQ;
                  break;
                case FCondKind::Oge:
                  status = LirArmStatus::GE;
                  break;
                case FCondKind::Ogt:
                  status = LirArmStatus::GT;
                  break;
                case FCondKind::Ole:
                  status = LirArmStatus::LE;
                  break;
                case FCondKind::Olt:
                  status = LirArmStatus::LT;
                  break;
                case FCondKind::One:
                  status = LirArmStatus::NE;
                  break;
                default:
                  break;
              }
            }
            else {
              switch (ckind.iCond) {
                case ICondKind::Eq:
                  status = LirArmStatus::EQ;
                  break;
                case ICondKind::Sge:
                  status = LirArmStatus::GE;
                  break;
                case ICondKind::Sgt:
                  status = LirArmStatus::GT;
                  break;
                case ICondKind::Sle:
                  status = LirArmStatus::LE;
                  break;
                case ICondKind::Slt:
                  status = LirArmStatus::LT;
                  break;
                case ICondKind::Ne:
                  status = LirArmStatus::NE;
                  break;
                default:
                  break;
              }
            }
            LirBr trueBr = new LirBr(lirBlock, addr, status);
            LirBr falseBr = new LirBr(lirBlock, falseAddr, LirArmStatus::NO_Cond);
          }
        }

        else if (kind == InstKind::GEP) {
          
        }
    }
}

// OperandResolve 即为申请一个 Operand
LirOperand* ToLir::operandResolve(Value* val, LirFunction* lirFunc, LirBlock* lirBlock) {
    if(dynamic_cast<ConstValue*>(val)) {
        return immResolve(val, lirFunc, lirBlock);
    }
    else {
        //  这里 TypeBase 的检验需要用 isFloat，因为指针类型也在通用寄存器中
        if(TypeBase::isFloat(val->getType())) {
            return new FVReg();
        }
        else 
            return new IVReg();
    }
}

LirOperand* ToLir::immResolve(Value* val, LirFunction* lirFunc, LirBlock* lirBlock) {
    if(dynamic_cast<ConstFloatValue*>(val)) {
        return loadImmToFVReg(dynamic_cast<ConstFloatValue*>(val)->getFloat(), lirFunc, lirBlock);
    } else {
        return loadImmToIVReg(dynamic_cast<ConstIntValue*>(val)->getInt(), lirFunc, lirBlock);
    }
}

// 此处如果传递的是引用，那么局部变量会被销毁
// 将立即数移入 Float Reg
FVReg* ToLir::loadImmToFVReg(float val, LirFunction* lirFunc, LirBlock* lirBlock) {
    FVReg *reg = new FVReg();
    FImm fImm = FImm(val);
    LirInstMove *move = new LirInstMove(*lirBlock, reg, fImm);
    lirFunc->getImmMap().emplace(reg, move);
    return reg;
}

// 将立即数移入 Integer Reg
IVReg* ToLir::loadImmToIVReg(int val, LirFunction* lirFunc, LirBlock* lirBlock) {
    IVReg *reg = new IVReg();
    IImm iImm = IImm(val);
    LirInstMove move = new LirInstMove(*lirBlock, reg, iImm);
    lirFunc->getImmMap().emplace(reg, move);
    return reg;
}
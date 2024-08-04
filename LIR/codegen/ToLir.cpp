#include "../../include/LIR/codegen/ToLir.h"
#include <set>

USING_GIMC_NAMESPACE

ToLir::ToLir(Module irModule) : irModule(irModule) {};

LirModule ToLir::moduleGen() {
    for(GlobalVar* globalVar : *irModule.getGlobalVars()) {
        lirModule.getGlobalvars()[globalVar->getName()] = globalVar;
        valMap[globalVar] = &Addr(globalVar->getName());
    }

    for(Function* func : *(irModule.getFuncDefs())) {
        baseTypePtr funcType = func->getType();
        std::vector<baseTypePtr> paramTypes = func->getArguTypes();
        std::vector<Value> funcParams = func->getArgus();
        int paramsCnt = paramTypes.size();
        std::vector<Value> lirFuncParams = std::vector<Value>();
        int intcnt = 0;
        int floatcnt = 0;

        LirFunction lirFunc = LirFunction(func->getName(), paramsCnt);
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
        lirModule.getFunctions().push_back(&lirFunc);
        funcMap[func] = &lirFunc;

        if(func->getBBlockList().getSize() > 0) {
            INode<BBlock> *blockNode = func->getBBlockList().getHeadPtr();
            while(!blockNode->isEnd()) {
                blockNode = blockNode->getNext();
                BBlock *block = blockNode->getOwner();
                LirBlock lirBlock = LirBlock(&lirFunc, block->getName() + "_" + func->getName());
                blockMap[block] = &lirBlock;
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
            LirBlock* lirBlock = blockMap[blockNode->getOwner()];
            globalMap.clear();
            
        }
    }

    
}

void ToLir::instResolve(Function *func, BBlock *block) {
    LirFunction* lirFunc = funcMap[func];
    LirBlock* lirBlock = blockMap[block];
    INode<Instruction> *instNode = block->getInstList().getHeadPtr();
    while(!instNode->isEnd()) {
        instNode = instNode->getNext();
        Instruction* inst = instNode->getOwner();

        //TODO:已经实现了整除加减乘除，需要实现其他二元指令
        if(inst->getKind()> InstKind::BinaryOPBegin && inst->getKind() < InstKind::BinaryOpEnd) {
            BinaryInst* i = dynamic_cast<BinaryInst*>(inst);
            Value *lhs = i->getLhs();
            Value *rhs = i->getRhs();
            LirOperand lhsReg, rhsReg, dstReg;
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
                LirBinary lirBin = LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(dynamic_cast<LirInst*>(&lirBin));
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
                LirBinary lirBin = LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(dynamic_cast<LirInst*>(&lirBin));
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
                LirBinary lirBin = LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(dynamic_cast<LirInst*>(&lirBin));
                break;

            case InstKind::Div:
            //除法不可以交换
                lhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                rhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
                lirInstKind = LirInstKind::Div;
                LirBinary lirBin = LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(dynamic_cast<LirInst*>(&lirBin));
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
                LirBinary lirBin = LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(dynamic_cast<LirInst*>(&lirBin));
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
                LirBinary lirBin = LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(dynamic_cast<LirInst*>(&lirBin));
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
                LirBinary lirBin = LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(dynamic_cast<LirInst*>(&lirBin));
                break;
            
            case InstKind::Divf:
                lhsReg = ToLir::operandResolve(lhs, lirFunc, lirBlock);
                rhsReg = ToLir::operandResolve(rhs, lirFunc, lirBlock);
                dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
                lirInstKind = LirInstKind::Divf;
                LirBinary lirBin = LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
                lirBlock->addInst(dynamic_cast<LirInst*>(&lirBin));
                break;


            default:
                break;
            }
        }
    }
}


LirOperand ToLir::operandResolve(Value* val, LirFunction* lirFunc, LirBlock* lirBlock) {
    if(dynamic_cast<ConstValue*>(val)) {
        return immResolve(val, lirFunc, lirBlock);
    }
    else {
        if(TypeBase::isInteger(val->getType())) {
            return IVReg();
        }
        else 
            return FVReg();
    }
}

LirOperand ToLir::immResolve(Value* val, LirFunction* lirFunc, LirBlock* lirBlock) {
    if(dynamic_cast<ConstFloatValue*>(val)) {
        return loadImmToFVReg(dynamic_cast<ConstFloatValue*>(val)->getFloat(), lirFunc, lirBlock);
    } else {
        
    }
}

FVReg& ToLir::loadImmToFVReg(float val, LirFunction* lirFunc, LirBlock* lirBlock) {
    FVReg reg = FVReg();
    FImm fImm = FImm(val);
    LirInstMove move = LirInstMove(*lirBlock, reg, fImm);
    lirFunc->getImmMap().emplace(reg, move);
    return reg;
}

IVReg& ToLir::loadImmToIVReg(int val, LirFunction* lirFunc, LirBlock* lirBlock) {
    IVReg reg = IVReg();
    IImm iImm = IImm(val);
    LirInstMove move = LirInstMove(*lirBlock, reg, iImm);
    lirFunc->getImmMap().emplace(reg, move);
    return reg;
}
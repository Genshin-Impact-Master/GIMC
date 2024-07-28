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
            while(blockNode != nullptr) {
                BBlock *block = blockNode->getOwner();
                LirBlock lirBlock = LirBlock(&lirFunc, block->getName() + "_" + func->getName());
                blockMap[block] = &lirBlock;
                blockNode = blockNode->getNext();
            }
        }

        INode<BBlock> *blockNode = func->getBBlockList().getHeadPtr();
        while(blockNode != nullptr) {
            BBlock *block = blockNode->getOwner();
            LirBlock *lirBlock = blockMap[block];
            for(BBlock* preBlock : block->getPres()) {
                lirBlock->addPres(blockMap[preBlock]);
            }

            std::unordered_set<BBlock*> lirSuccs = block->getSuccs();
            if(lirSuccs.size() == 1) {
                lirBlock->setTrueLirSucc(blockMap[*lirSuccs.begin()]);
            }else if(lirSuccs.size() == 2) {
                lirBlock->setTrueLirSucc(blockMap[*lirSuccs.begin()]);
                lirBlock->setFalseLirSucc(blockMap[*lirSuccs.end()]);
            }
        }

        

        







    }





    
}
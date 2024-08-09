#ifndef LIR_BLOCK_H
#define LIR_BLOCK_H
#include "../../Config.h"
#include "../../IR/GlobalVar.h"
#include "../lirInst/LirInst.h"
#include <unordered_set>



GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE
class LirFunction;
class LirBlock {
    private:
        std::string label;
        LirFunction *lirFunction; //parent
        std::unordered_set<LirBlock*> lirPres;
        LirBlock* trueLirSucc;
        LirBlock* falseLirSucc;
        IList<LirBlock, LirInst> lirInstLists;
        INode<LirBlock> node;

    public:
        // 修改 1 LirBlock 的无参初始化是不允许的
        LirBlock(LirFunction* lirFunction, const std::string &label);
        void addPres(LirBlock* lirPre);
        void setTrueLirSucc(LirBlock* tureLirSucc);
        void setFalseLirSucc(LirBlock* falseLirSucc);
        void addInst(LirInst* inst);
        
        INode<LirBlock>& getNode() {return node;}
        std::string &getLabel() {return label;}
        IList<LirBlock, LirInst> &getInst(){return lirInstLists;}
        LirFunction* getParent() {return lirFunction;}

        LirInst *getFirstInst() {
          INode<LirInst> *node = lirInstLists.getHeadPtr();
          if (node->isEnd()) {
            error("LirBlock 基本块中不含指令");
          }
          return node->getNext()->getOwner();
        }
};


GIMC_NAMESPACE_END


#endif
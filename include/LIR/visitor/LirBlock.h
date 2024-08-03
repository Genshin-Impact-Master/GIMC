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

    public:
        // 修改 1 LirBlock 的无参初始化是不允许的
        LirBlock(LirFunction* lirFunction, const std::string &label);
        void addPres(LirBlock* lirPre);
        void setTrueLirSucc(LirBlock* tureLirSucc);
        void setFalseLirSucc(LirBlock* falseLirSucc);
        void addInst(LirInst* inst);
        
        

};


GIMC_NAMESPACE_END


#endif
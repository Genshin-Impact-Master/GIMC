#ifndef LIR_BLOCK_H
#define LIR_BLOCK_H
#include "Config.h"
#include "GlobalVar.h"
#include <unordered_set>



GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class LirBlock {
    private:
        std::string label;
        LirFunction *lirFunction;
        std::unordered_set<LirBlock*> lirPres;
        LirBlock* trueLirSucc;
        LirBlock* falseLirSucc;

    public:
        LirBlock(LirFunction* lirFunction, const std::string &label);
        void addPres(LirBlock* lirPre);
        void setTrueLirSucc(LirBlock* tureLirSucc);
        void setFalseLirSucc(LirBlock* falseLirSucc);
        

};


GIMC_NAMESPACE_END


#endif
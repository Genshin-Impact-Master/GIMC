#ifndef LIR_MODULE_H
#define LIR_MODULE_H
#include "Config.h"
#include "GlobalVar.h"
#include "Function.h"
#include <map>
#include <list>



GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class LirModule {
    private :
        std::map<std::string, GlobalVar*> globalvars;
        std::list<LirFunction*> lirfunctions;
        
    public:
        std::map<std::string, GlobalVar*> &getGlobalvars() {return globalvars;}
        std::list<LirFunction*> &getFunctions() {return lirfunctions;}
};



GIMC_NAMESPACE_END


#endif
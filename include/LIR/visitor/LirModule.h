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
        std::list<Function*> functions;
        
    public:
        std::map<std::string, GlobalVar*> &getGlobalvars() {return globalvars;}
        std::list<Function*> &getFunctions() {return functions;}
};



GIMC_NAMESPACE_END


#endif
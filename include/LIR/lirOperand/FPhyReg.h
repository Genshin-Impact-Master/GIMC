#ifndef LIR_FPHYREG_H
#define LIR_FPHYREG_H
#include "Config.h"
#include "lirOperand.h"
#include "Reg.h"
#include <map>
#include <set>

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class FPhyReg : public Reg {
    private:
        int id;  

    public:
        FPhyReg(int id);

        static std::map<int, FPhyReg*>* FPhyRegs;
        static std::set<FPhyReg*>* allocatableFPhyRegs;

        static std::map<int, FPhyReg*>* generateFPhyRegs();
        static FPhyReg* RegS(int id);
        static std::set<FPhyReg*>* getAllocatableFPhyRegs();

        bool isCallerSave();
        bool isCalleeSave();

        std::string toString();


};

GIMC_NAMESPACE_END

#endif
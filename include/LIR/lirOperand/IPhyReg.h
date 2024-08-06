#ifndef LIR_IPHYAREG_H
#define LIR_IPHYAREG_H
#include "../../Config.h"
#include "lirOperand.h"
#include "Reg.h"
#include <map>
#include <set>

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class IPhyReg : public Reg {
    private:
        int id;  

    public:
        IPhyReg(int id);
        static IPhyReg *SP;
        static IPhyReg *LR;
        static IPhyReg *PC;
        static IPhyReg *CSPR;

        static std::map<int, IPhyReg*>* IPhyRegs;
        static std::set<IPhyReg*>* allocatableIPhyRegs;

        static IPhyReg* RegR(int id);
        static std::set<IPhyReg*>* getAllocatableIPhyRegs();

        bool isCallerSave();
        bool isSpecial();
        bool isCalleeSave();

        std::string toString() override;


};

GIMC_NAMESPACE_END


#endif
#include "../../include/LIR/lirOperand/Reg.h"
#include "IPhyReg.h"
#include "FPhyReg.h"

USING_GIMC_NAMESPACE

Reg::Reg(LirOperandKind RegKind) : LirOperand(RegKind) {}

std::set<Reg*>* Reg::getAllocatableRegs() {
    std::set<Reg*>* allocatableRegs = new std::set<Reg*>();


    for(IPhyReg* iPhyReg : *(IPhyReg::getAllocatableIPhyRegs())) {
        allocatableRegs->insert(static_cast<Reg*>(iPhyReg));
    }

    for(FPhyReg* fPhyReg : *(FPhyReg::getAllocatableFPhyRegs())) {
        allocatableRegs->insert(static_cast<Reg*>(fPhyReg));
    }

    return allocatableRegs;
}

int Reg::getAllocatableRegsCnt(bool isInteger) {
    return (isInteger ?  IPhyReg::getAllocatableIPhyRegs()->size(): FPhyReg::getAllocatableFPhyRegs()->size());
}
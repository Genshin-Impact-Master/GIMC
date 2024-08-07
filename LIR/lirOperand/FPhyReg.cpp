// #include "../../include/LIR/lirOperand/FPhyReg.h"
// #include <stdexcept>

// USING_GIMC_NAMESPACE

// FPhyReg::FPhyReg(int id) : Reg(LirOperandKind::FPhy), id(id) {};

// std::map<int, FPhyReg*>* FPhyReg::generateFPhyRegs() {
//     std::map<int, FPhyReg*>* FPhyRegs = new std::map<int, FPhyReg*>;

//     for(int i = 0; i <= 31; i++) {
//         // FPhyRegs->emplace(i, &FPhyReg(i));
//     }

//     return FPhyRegs;
// }

// std::map<int, FPhyReg*>* FPhyReg::FPhyRegs = FPhyReg::generateFPhyRegs();

// FPhyReg* FPhyReg::RegS(int id) {
//     if (id < 0 || id > 31) {
//         throw std::out_of_range("ID is out of valid range (0-31)");
//     }
//     return FPhyRegs->at(id);
// }

// std::set<FPhyReg*>* FPhyReg::getAllocatableFPhyRegs() {
//     std::set<FPhyReg*>* allocatableFPhyRegs;

//     for(int i = 0; i <= 31; i++) {
//         allocatableFPhyRegs->emplace(FPhyReg::RegS(i));
//     }

//     return allocatableFPhyRegs;
// }

//  bool FPhyReg::isCallerSave() {
//     return id < 16;
//  }

//  bool FPhyReg::isCalleeSave() {
//     return id >= 16;
//  }

//  std::string FPhyReg::toString() {
//     return "s" + id;
//  }



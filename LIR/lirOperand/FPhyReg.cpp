#include "../../include/LIR/lirOperand/FPhyReg.h"

USING_GIMC_NAMESPACE

FPhyReg::FPhyReg(int id) : Reg(LirOperandKind::FPhy), id(id) {};
std::map<int, FPhyReg*> FPhyReg::FPhyRegMap;
std::set<FPhyReg*> FPhyReg::allocatableFPhyRegs;

void FPhyReg::generateFPhyRegs() {
  for(int i = 0; i <= 31; i++) {
    FPhyRegMap[i] = new FPhyReg(i);
  }
  FPhyRegMap[FPSCR_REG_NUM - FLOAT_REG_START] = new FPhyReg(FPSCR_REG_NUM - FLOAT_REG_START);
}

// std::map<int, FPhyReg*>* FPhyReg::FPhyRegs = FPhyReg::generateFPhyRegs();

FPhyReg* FPhyReg::getRegS(int id) {
  if (id < 0 || id > 31) {
    error("ID is out of valid range (0-31)");
  }
  return FPhyRegMap.at(id);
}

std::set<FPhyReg*> &FPhyReg::getAllocatableFPhyRegs() {
  allocatableFPhyRegs.clear();
  for (int i = 0; i < 32; i++) {
    allocatableFPhyRegs.emplace(getRegS(i));
  }
  return allocatableFPhyRegs;
}

bool FPhyReg::isCallerSave() {
  return id < 16;
}

bool FPhyReg::isCalleeSave() {
  return id >= 16;
}

std::string FPhyReg::toString() {
  return ARM_REGS[id + FLOAT_REG_START];
}



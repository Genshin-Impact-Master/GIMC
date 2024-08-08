#include "../../include/LIR/lirOperand/IPhyReg.h"

USING_GIMC_NAMESPACE

IPhyReg::IPhyReg(int id) : Reg(LirOperandKind::IPhy), id(id) {};

IPhyReg* IPhyReg::SP = new IPhyReg(13); 
IPhyReg* IPhyReg::LR = new  IPhyReg(14);
IPhyReg* IPhyReg::PC = new  IPhyReg(15);
IPhyReg* IPhyReg::APSR = new  IPhyReg(APSR_REG_NUM);

std::map<int, IPhyReg*> IPhyReg::IPhyRegMap = {
  {0, new IPhyReg(0)},
  {1, new IPhyReg(1)},
  {2, new IPhyReg(2)},
  {3, new IPhyReg(3)},
  {4, new IPhyReg(4)},
  {5, new IPhyReg(5)},
  {6, new IPhyReg(6)},
  {7, new IPhyReg(7)},
  {8, new IPhyReg(8)},
  {9, new IPhyReg(9)},
  {10, new IPhyReg(10)},
  {11, new IPhyReg(11)},
  {12, new IPhyReg(12)},
  {13, IPhyReg::SP},
  {14, IPhyReg::LR},
  {15, IPhyReg::PC}
};

IPhyReg* IPhyReg::getRegR(int id) {
  if (id < 0 || id > 15) {
    error("ID is out of valid range (0-15)");
  }
  return IPhyRegMap.at(id);
}

std::set<IPhyReg*> allocatableIPhyRegs = std::set<IPhyReg*> {
  IPhyReg::getRegR(0),
  IPhyReg::getRegR(1),
  IPhyReg::getRegR(2),
  IPhyReg::getRegR(3), 
  IPhyReg::getRegR(4),
  IPhyReg::getRegR(5),
  IPhyReg::getRegR(6),
  IPhyReg::getRegR(7),
  IPhyReg::getRegR(8),
  IPhyReg::getRegR(9),
  IPhyReg::getRegR(10),
  IPhyReg::getRegR(11),
  IPhyReg::getRegR(12),
};


// bool IPhyReg::isCallerSave() {
//     return id < 4;
// }

// bool IPhyReg::isSpecial() {
//     return id == 13 || id == 15 || id == 16;
// }

// bool IPhyReg::isCalleeSave() {
//     return !isCallerSave() && !isSpecial();
// }

std::string IPhyReg::toString() {
  return ARM_REGS[id];
}
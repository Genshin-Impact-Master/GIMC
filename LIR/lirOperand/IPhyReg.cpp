// #include "../../include/LIR/lirOperand/IPhyReg.h"
// #include <stdexcept>

// USING_GIMC_NAMESPACE

// IPhyReg::IPhyReg(int id) : Reg(LirOperandKind::IPhy), id(id) {};

// IPhyReg* IPhyReg::SP = new IPhyReg(13);
// IPhyReg* IPhyReg::LR = new IPhyReg(14);
// IPhyReg* IPhyReg::PC = new IPhyReg(15);
// IPhyReg* IPhyReg::CSPR = new IPhyReg(16);

// std::map<int, IPhyReg*>* IPhyRegs = new std::map<int, IPhyReg*>{
//     {0, &IPhyReg(0)},
//     {1, &IPhyReg(1)},
//     {2, &IPhyReg(2)},
//     {3, &IPhyReg(3)},
//     {4, &IPhyReg(4)},
//     {5, &IPhyReg(5)},
//     {6, &IPhyReg(6)},
//     {7, &IPhyReg(7)},
//     {8, &IPhyReg(8)},
//     {9, &IPhyReg(9)},
//     {10, &IPhyReg(10)},
//     {11, &IPhyReg(11)},
//     {12, &IPhyReg(12)},
//     {13, IPhyReg::SP},
//     {14, IPhyReg::LR},
//     {15, IPhyReg::PC}
// };

// IPhyReg* IPhyReg::RegR(int id) {
//     if (id < 0 || id > 15) {
//         throw std::out_of_range("ID is out of valid range (0-15)");
//     }
//     return IPhyRegs->at(id);
// }

// std::set<IPhyReg*>* allocatableIPhyRegs = new std::set<IPhyReg*> {
//     IPhyReg::RegR(0),
//     IPhyReg::RegR(1),
//     IPhyReg::RegR(2),
//     IPhyReg::RegR(3), 
//     IPhyReg::RegR(4),
//     IPhyReg::RegR(5),
//     IPhyReg::RegR(6),
//     IPhyReg::RegR(7),
//     IPhyReg::RegR(8),
//     IPhyReg::RegR(9),
//     IPhyReg::RegR(10),
//     IPhyReg::RegR(11),
//     IPhyReg::RegR(12),
// };

// std::set<IPhyReg*>* IPhyReg::getAllocatableIPhyRegs() {
//     return allocatableIPhyRegs;
// }

// bool IPhyReg::isCallerSave() {
//     return id < 4;
// }

// bool IPhyReg::isSpecial() {
//     return id == 13 || id == 15 || id == 16;
// }

// bool IPhyReg::isCalleeSave() {
//     return !isCallerSave() && !isSpecial();
// }

// std::string IPhyReg::toString() {
//     switch (id)
//     {
//         case 13: return "sp";
//         case 14: return "lr";break;
//         case 15: return "pc";break;
//         case 16: return "cspr";break;
//         default: return "r" + id;break;
//     }
// }





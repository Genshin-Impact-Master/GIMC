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
  static IPhyReg *APSR;     // 通用状态寄存器

  static std::map<int, IPhyReg*> IPhyRegMap;
  static std::set<IPhyReg*> allocatableIPhyRegs;

  // 根据 id 获得通用寄存器 0 ~ 15
  static IPhyReg* getRegR(int id);
  static std::set<IPhyReg*>& getAllocatableIPhyRegs() {return allocatableIPhyRegs;}

  // bool isCallerSave();
  // bool isSpecial();
  // bool isCalleeSave();

  std::string toString() override;
};

GIMC_NAMESPACE_END


#endif
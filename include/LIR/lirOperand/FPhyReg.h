#ifndef LIR_FPHYREG_H
#define LIR_FPHYREG_H
#include "../../Config.h"
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

  // 维护 id -> Float Reg 的映射
  static std::map<int, FPhyReg*> FPhyRegMap;
  // 维护可分配的寄存器
  static std::set<FPhyReg*> allocatableFPhyRegs;

  static FPhyReg *FPSCR;

  // 生成物理寄存器
  static void generateFPhyRegs();
  // 根据 id 获得寄存器，0 ~ 31
  static FPhyReg* getRegS(int id);
  // 获得可分配的寄存器
  static std::set<FPhyReg*> &getAllocatableFPhyRegs();

  bool isCallerSave();
  bool isCalleeSave();

  std::string toString() override;
};

GIMC_NAMESPACE_END

#endif
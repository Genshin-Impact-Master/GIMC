#ifndef REGALLOCSTACK_H
#define REGALLOCSTACK_H
#include "../LIR/LirHearders.h"

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class RegAllocStack {
private:
  int size = 0;
  std::map<LirOperand*, IImm> regsOffset;
public:
  void alloc(LirModule &lirModule);
  void allocInst(LirInst *inst);
  IImm putLocal(LirOperand *reg, LirFunction *lirFunc);
};

GIMC_NAMESPACE_END

#endif // REGALLOCSTACK_H
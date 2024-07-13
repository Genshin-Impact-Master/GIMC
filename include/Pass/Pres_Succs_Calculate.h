#ifndef PRES_SUCCS_CALCULATE_H
#define PRES_SUCCS_CALCULATE_H

#include "Pass.h"

USING_GIMC_NAMESPACE
GIMC_NAMESPACE_BEGIN

class Pres_Succs_Calculate : public Pass {
public:
  static void calculate_Module(Module *module);
  static void calculate_Func(Function *func);
};

GIMC_NAMESPACE_END

#endif // PRES_SUCCS_CALCULATE_H
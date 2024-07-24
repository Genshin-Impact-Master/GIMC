#ifndef PRES_SUCCS_CALCULATE_H
#define PRES_SUCCS_CALCULATE_H
#include "../Config.h"
#include "../IR/Module.h"
#include "../IR/Function.h"

USING_GIMC_NAMESPACE
GIMC_NAMESPACE_BEGIN

class Pres_Succs_Calculate {
public:
  static void calculate_Module(Module *module);
  static void calculate_Func(Function *func);
};

GIMC_NAMESPACE_END

#endif // PRES_SUCCS_CALCULATE_H
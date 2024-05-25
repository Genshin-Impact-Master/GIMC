#include "include/Config.h"

USING_GIMC_NAMESPACE
GIMC_NAMESPACE_BEGIN

std::vector<std::string> ST_Insts = {
  "BinaryOPBegin", "add ", "sub ", "mul ", "sdiv ", "BinaryOPEND", "alloca ", "store ", "load ",
  "call ", "ret "
};

std::vector<Value*> Zero_Argu_List;

std::vector<baseTypePtr> Zero_Argu_Type_List;
GIMC_NAMESPACE_END

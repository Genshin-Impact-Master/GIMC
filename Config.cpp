#include "include/Config.h"

USING_GIMC_NAMESPACE
GIMC_NAMESPACE_BEGIN

std::vector<std::string> ST_Insts = {
  "BinaryOPBegin", "add ", "sub ", "mul ", "sdiv ", "srem ", "fadd ", "fsub ", "fmul ", "fdiv ", "and ", "or ", "BinaryOPEND", "alloca ", "store ", "load ",
  "call ", "ret ", "icmp ", "fcmp ", "br ", "gep ", " fptosi ", "sitofp ", "zext ", "phi ", "initMem "
};


std::vector<std::string> ST_IConds = {
  "eq ", "ne ", "ugt ", "uge ", "ult ", "ule ", "sgt ", "sge ", "slt " ,"sle "
};

std::vector<std::string> ST_FConds = {
  "oeq ", "ogt ", "oge ", "olt ", "ole ", "one "
};

std::vector<Value*> Zero_Argu_List;

std::vector<baseTypePtr> Zero_Argu_Type_List;

// 报错函数
void error(const std::string &msg) {
  std::cerr << "Error: " << msg << std::endl;
  std::exit(EXIT_FAILURE);
}

int alignsTo(int size, int alignSize) {
  int cnt = size / alignSize;
  if ((size % alignSize) != 0) {
    cnt++;
  }
  return cnt * alignSize;
}
GIMC_NAMESPACE_END

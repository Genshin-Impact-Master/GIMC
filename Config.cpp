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

std::vector<std::string> ARM_REGS = {
  "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", /* r7 为特殊的 fp 寄存器*/ "r8", "r9", "r10", "r11", "r12", "sp", "lr", "pc"
  // todo 浮点寄存器
}

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

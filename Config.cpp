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

std::vector<std::string> ST_ARM_STATUS = {
  "eq", "ne", "gt", "lt", "ge", "le", ""
};

std::vector<Value*> Zero_Argu_List;

std::vector<baseTypePtr> Zero_Argu_Type_List;

std::vector<std::string> ARM_REGS = {
  "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", /* r7 为特殊的 fp 寄存器*/ "r8", "r9", "r10", "r11", "r12", "sp", "lr", "pc",
  // 浮点 32 位寄存器
  "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "s12", "s13", "s14", "s15", "s16", "s17", "s18",
  "s19", "s20", "s21", "s22", "s23", "s24", "s25", "s26", "s27", "s28", "s29", "s30", "s31",
  // 浮点 64 位寄存器
  "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "d10", "d11", "d12", "d13", "d14", "d15", "d16", "d17", "d18", 
  "d19", "d20", "d21", "d22", "d23", "d24", "d25", "d26", "d27", "d28", "d29", "d30", "d31"
  "APSR_nzcv",/* 用户级状态寄存器 */ "FPSCR" /* 浮点运算单元的状态寄存器 */
};

std::vector<std::string> ST_LirConds = {
  "BinBegin", "add ", "sub ", "rsb ", "mul ", "div ", "srem ", "addf ", "subf ", "mulf ", "divf ", "binEnd ", "store ", "load ", 
  "call ", "ret ", "cmp ", "br ", "fp2int ", "int2fp ", "move ", "push ", "pop "
};

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

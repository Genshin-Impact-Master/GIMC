#include "../include/IR/ConstValue.h"

USING_GIMC_NAMESPACE
// ConstValue *boolTrue = new ConstValue(i1Type, 1);

// 重载 Value 中的 getName
std::string& ConstFloatValue::getName() {
  float x = getFloat();
  double tmp = (double)x;              // 将 float 转换为 double
  uint64_t bits = *(uint64_t*)(&tmp);

  // fprintf(stdout, "%f\n", tmp);
  // for (int i=7; i >= 0; i--) {
  //   fprintf(stdout, "%x", *((uint8_t*)(&bits) + i));
  // }
  // fprintf(stdout, "\n");
  
  std::stringstream ss;
  ss << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(16) << bits;
  setValueName(ss.str());
  return Value::getName();
}

// 重载 Value 中的 getFullName
std::string& ConstFloatValue::getFullName() {
  return getName();
}
#include "../include/IR/ConstValue.h"

USING_GIMC_NAMESPACE
// ConstValue *boolTrue = new ConstValue(i1Type, 1);

// 重载 Value 中的 getName
std::string& ConstFloatValue::getName() {
  float x = getFloat();
  uint32_t bits = *(uint32_t*)(&x);
  std::stringstream ss;
  ss << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(8) << bits;
  setValueName(ss.str());
  return Value::getName();
}

// 重载 Value 中的 getFullName
std::string& ConstFloatValue::getFullName() {
  float x = getFloat();
  double tmp = (double)x;              // 将 float 转换为 double
  uint64_t bits = *(uint64_t*)(&tmp);
  
  std::stringstream ss;
  ss << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(16) << bits;
  setValueName(ss.str());
  return Value::getName();
}
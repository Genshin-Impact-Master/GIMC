#ifndef CONSTVALUE_H_
#define CONSTVALUE_H_

#include "../Config.h"
#include "Type.h"
#include "Value.h"
#include <cstdint>
#include <memory>

GIMC_NAMESPACE_BEGIN

class ConstValue : public Value {
protected:
  uint64_t value_;
public:
  /**
   * 实际上此函数不会被直接调用，只会在生成子类对象时调用
   * 因为 Type 仅有具体的 Integer or Float
  */
  ConstValue(baseTypePtr type, uint64_t value)
    : Value("anonymous", type), value_(value) {}
};

class ConstIntValue final : public ConstValue {
private:
public:
  ConstIntValue(uint64_t value) : ConstValue(i32TyPtr, value) {}
  
  /**
   * @todo 暂时只支持了符号整数，还有无符号整数
  */
  // 返回 符号整数
  int32_t getInt() {return static_cast<int32_t>(value_);}

  // 重载 Value 中的 getName
  std::string& getName() override {
    setValueName(std::to_string(getInt()));
    return Value::getName();
  }

  // 重载 Value 中 getFullName
  std::string& getFullName() override {
    setValueName(std::to_string(getInt()));
    return Value::getName();                    // 因为对于值而言，没有加前缀的说法
  }
};

class ConstFloatValue final : public ConstValue {
private:
public:
  ConstFloatValue(double value)
    : ConstValue(fTyPtr, static_cast<uint64_t>(value)) {}
  
  // 返回 符号浮点数
  double getFloat() {return static_cast<double>(value_);}
};

GIMC_NAMESPACE_END

#endif  // CONSTVALUE_H_
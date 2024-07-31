#ifndef CONSTVALUE_H_
#define CONSTVALUE_H_

#include "../Config.h"
#include "Type.h"
#include "Value.h"
#include <cstdint>
#include <memory>
#include <iomanip>
#include <sstream>
#include <iostream>

GIMC_NAMESPACE_BEGIN

typedef union IntFloat {
  int i;                    // 共用体作为 int
  float f;                  // 共用体作为 float
} IntFloat;

class ConstValue : public Value {
protected:
  IntFloat value_;
public:
  /**
   * 实际上此函数不会被直接调用，只会在生成子类对象时调用
   * 因为 Type 仅有具体的 Integer or Float
  */
  ConstValue(baseTypePtr type)
    : Value("anonymous", type) {}
  
  // @C++_Learn 利用模板方法实现一个函数不同类型返回值
  // template<typename T>
  // T getValue(); 
};

class ConstIntValue final : public ConstValue {
private:
public:
  ConstIntValue(baseTypePtr ty, int value) : ConstValue(ty) {value_.i = value;}
  ConstIntValue(int value) : ConstValue(i32Type) {value_.i = value;}
  
  // 返回 符号整数
  int32_t getInt() {return value_.i;}

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

  // 重载 Value 中 getData 同样是返回值的 string
  std::string getData() override {
    return std::to_string(getInt());
  }

  // 重载 getHash 函数 
  uint32_t getHash() override {
    if (!isHashed()) {
      std::cout << "I'm in int's get Hash" <<std::endl;
      setHashCode(std::hash<int>()(value_.i));
    }
    return getHash();
  }

  bool isEqual(Value *t) override {
    ConstIntValue *con = dynamic_cast<ConstIntValue*>(t);
    if (!con)
      return false;
    if (!(con->getInt() == getInt()))
      return false;
    return true;
  }
};

class ConstFloatValue final : public ConstValue {
private:
public:
  ConstFloatValue(float value)
    : ConstValue(floatType) {value_.f = value;}
  
  // 重载 Value 中的 getName
  std::string& getName() override;

  // 重载 Value 中的 getFullName
  std::string& getFullName() override;

  // 返回 符号浮点数
  float getFloat() {return value_.f;}

  // 重载 getHash 函数
  uint32_t getHash() override {
    if (!isHashed()) {
      std::cout << "I'm in int's get Hash" <<std::endl;
      setHashCode(std::hash<int>()(value_.f));
    }
    return getHash();
  }

  // 重载 isEqual()
  bool isEqual(Value *t) override {
    ConstFloatValue *con = dynamic_cast<ConstFloatValue*>(t);
    if (!con)
      return false;
    if (!(con->getFloat() == getFloat()))
      return false;
    return true;
  }
};

GIMC_NAMESPACE_END

#endif  // CONSTVALUE_H_
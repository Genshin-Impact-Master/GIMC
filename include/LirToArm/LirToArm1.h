#ifndef LIR_TO_ARM1_H
#define LIR_TO_ARM1_H
#include <fstream>
#include <string>
#include <iostream>
#include "../Config.h"
#include "../LIR/visitor/LirModule.h"
#include "../LIR/visitor/LirBlock.h"
#include "../LIR/visitor/LirFunction.h"

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class LirToArm {
private:
  LirModule lirModule_;
  std::ofstream armOut;           // 输出 arm 汇编的字符流
public:
  LirToArm(LirModule lirModule) : lirModule_(lirModule) {
    armOut.open("test.s");             // 急切地需要一个 Module 的名字
  }
  
  // @C++_Learn 变长参数模板，实现类似 printf 的功能 (采用递归的方法解析)
  template<typename... Args>
  void smartOut(const std::string &attr, Args... args) {
    armOut << "\t" << attr << " ";
    if (sizeof...(args) > 0) {
      armOut << " ";              // 在 attr 和第一个参数间添加空格
      appendToStream(args...);
    }
  }
  template<typename T>
  void appendToStream(T &value) {armOut << value << std::endl;}
  template<typename T, typename... Args>
  void appendToStream(T &value, Args&... args) {
    armOut << value;
    if (sizeof...(args) > 0) {
      armOut << ", ";
      appendToStream(args...);
    }
  }

  void genFunction();
  void genBlock();
  void genModule();
};


GIMC_NAMESPACE_END

#endif // LIR_TO_ARM1_H
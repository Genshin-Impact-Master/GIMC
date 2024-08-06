#ifndef TO_ARM_H
#define TO_ARM_H
#include "../LIR/LirHearders.h"
#include <fstream>
#include <iostream>
#include <string>

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class LirToArm {
private:
  LirModule lirModule_; // LirModule 包含了所有 LIR 的指令和数据
  std::ofstream armOut; // 输出 arm 汇编的字符流
public:
  LirToArm(LirModule lirModule) : lirModule_(lirModule) {
    armOut.open("test.s");
  } // 唯一的构造方法

  /*********************************** 汇编代码生成 *****************************************/
  // 输出 module
  void genModule();

  // 输出 Function
  void genFunction(LirFunction *func);

  // 输出 Block
  void genBlock(LirBlock *blk);
  
  // 输出 Arm 指令的全局变量部分
  void Output_Arm_global();



  /********************************** 通用函数（之后也可复用）*******************************/

  /**
   * 通用寄存器压栈
   */
  void push(std::string reg) { smartOut("push", "{" + reg + "}"); }

  /**
   * 整数 dst <- lhs - rhs
   */
  void sub(std::string dst, std::string lhs, std::string rhs) {
    smartOut("sub", dst, lhs, rhs + "\t@ " + dst + " <- " + lhs + " - " + rhs);
  }

  /**
   * 整数 dst <- lhs + rhs
   */
  void add(std::string dst, std::string lhs, std::string rhs) {
    smartOut("add", dst, lhs, rhs + "\t@ " + dst + " <- " + lhs + " + " + rhs);
  }

  /**
   * 整数 dst <- lhs * rhs
   */
  void mul(std::string dst, std::string lhs, std::string rhs) {
    smartOut("mul", dst, lhs, rhs + "\t@ " + dst + " <- " + lhs + " * " + rhs);
  }

  /**
   * 整数 dst <- lhs / rhs
   */
  void div(std::string dst, std::string lhs, std::string rhs) {
    smartOut("sdiv", dst, lhs, rhs + "\t@ " + dst + " <- " + lhs + " / " + rhs);
  }

  // @C++_Learn 变长参数模板，实现类似 printf 的功能 (采用递归的方法解析)
  template <typename... Args>
  void smartOut(const std::string &attr, Args... args) {
    armOut << "\t" << attr << " ";
    if (sizeof...(args) > 0) {
      armOut << " "; // 在 attr 和第一个参数间添加空格
      appendToStream(args...);
    }
  }
  template <typename T> void appendToStream(T &value) {
    armOut << value << std::endl;
  }
  template <typename T, typename... Args>
  void appendToStream(T &value, Args &...args) {
    armOut << value;
    if (sizeof...(args) > 0) {
      armOut << ", ";
      appendToStream(args...);
    }
  }
};

GIMC_NAMESPACE_END

#endif
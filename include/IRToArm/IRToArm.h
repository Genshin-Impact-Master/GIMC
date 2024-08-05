#ifndef IRToArm_H
#define IRToArm_H
#include <fstream>
#include <string>
#include <iostream>
#include "../Config.h"
#include "../IR/Module.h"
#include "../IR/BBlock.h"
#include "../IR/Function.h"
#include "../IR/Inst.h"
#include <unordered_map>

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class IRToArm {
private:
  Module module_;
  std::ofstream armOut;
  std::unordered_map<Value*, int> stackOffset;
public:
  // 特殊时期，暂时用栈操作过渡
  IRToArm(Module module) : module_(module) {
    armOut.open(module.getName() + ".s");
  }

  void genModule();
  void genFunction(Function *func);
  void genBBlock(BBlock *bBlk);
  void genInst(Instruction *inst);

  int getStackSize(Function *func);

  /* 简单的线性寄存器分配 */
  


  /********************************** 通用函数（之后也可复用） *******************************/

  /**
   * 通用寄存器压栈
   */
  void push(std::string reg) {
    smartOut("push", "{" + reg + "}");
  }

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
};

GIMC_NAMESPACE_END


#endif // IRToArm_H
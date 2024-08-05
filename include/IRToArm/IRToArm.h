#ifndef IRToArm_H
#define IRToArm_H
#include <fstream>
#include <string>
#include <iostream>
#include "../Config.h"
#include "../IR/Module.h"
#include "../IR/BBlock.h"
#include "../IR/Function.h"
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

  int getStackSize(Function *func);

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
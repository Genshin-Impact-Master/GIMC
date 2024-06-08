#ifndef MODULE_H_
#define MODULE_H_

#include "../Config.h"
#include "Function.h"
#include "Value.h"

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class GlobalVar;
class IRBuilder;

class Module : public Value {
friend class IRBuilder;
private:
  std::vector<GlobalVar*> globalVars_;        // 全局变量链表
  std::vector<Function*> funcDefs_;       // 函数定义链表
  std::vector<Function*> funcDeclares_;       // 函数声明链表
public:
  Module(const std::string &name, 
          baseTypePtr type,
          std::vector<GlobalVar*> &globalVars,
          std::vector<Function*> &funcDefs,
          std::vector<Function*> &funcDeclares) : Value(name, type), globalVars_(globalVars), funcDefs_(funcDefs), funcDeclares_(funcDeclares) {}

  Module(const std::string &name, baseTypePtr type) : Value(name, type) {}
  /**
   * 将函数定义（所有指令，及其基本块），全局变量释放并清空容器
   * @note 函数声明仅仅为清空容器（因为每个函数声明并没有具体的基本块）
  */
  void clearModule();

  std::vector<GlobalVar*>* getGlobalVars() {return &globalVars_;}

  std::vector<Function*>* getFuncDefs() {return &funcDefs_;}

  std::vector<Function*>* getFuncDeclares() {return &funcDeclares_;}
};

GIMC_NAMESPACE_END

#endif // MODULE_H_
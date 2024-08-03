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
  std::vector<Function*> funcDefs_;           // 函数定义链表
  std::vector<Function*> funcDeclares_;       // 函数声明链表
  int start = 0;                              // 库函数的起始位置
public:
  Module(const std::string &name, 
          baseTypePtr type,
          std::vector<GlobalVar*> &globalVars,
          std::vector<Function*> &funcDefs,
          std::vector<Function*> &funcDeclares);

  Module(const std::string &name, baseTypePtr type) : Value(name, type) {addLibs();}
  /**
   * 将函数定义（所有指令，及其基本块），全局变量释放并清空容器
   * @note 函数声明仅仅为清空容器（因为每个函数声明并没有具体的基本块）
  */
  void clearModule();

  std::vector<GlobalVar*>* getGlobalVars() {return &globalVars_;}

  std::vector<Function*>* getFuncDefs() {return &funcDefs_;}

  std::vector<Function*>* getFuncDeclares() {return &funcDeclares_;}

  void addLibs();

  Function* getPutch() {return funcDeclares_[start];}
  Function* getPutInt() {return funcDeclares_[start + 1];}
  Function* getPutArray() {return funcDeclares_[start + 2];}
  Function* getPutFloat() {return funcDeclares_[start + 3];}
  Function* getPutFarray() {return funcDeclares_[start + 4];}
  Function* getBefore_Main() {return funcDeclares_[start + 5];}
  Function* getAfter_Main() {return funcDeclares_[start + 6];}
  Function* getStartTime() {return funcDeclares_[start + 7];}
  Function* getStopTime() {return funcDeclares_[start + 8];}
  Function* getGetInt() {return funcDeclares_[start + 9];}
  Function* getGetCh() {return funcDeclares_[start + 10];}
  Function* getGetFloat() {return funcDeclares_[start + 11];}
  Function* getGetArray() {return funcDeclares_[start + 12];}
  Function* getGetFarray() {return funcDeclares_[start + 13];}

  void correctCheck();
};

GIMC_NAMESPACE_END

#endif // MODULE_H_
#include "../include/IR/Module.h"
#include "../include/IR/GlobalVar.h"

USING_GIMC_NAMESPACE

void Module::clearModule() {
  for (auto func : funcDefs_) {
    func->clearFunc();
    delete func;
  }
  funcDefs_.clear();
  for (auto globalVar : globalVars_) {
    delete globalVar;
  }
  globalVars_.clear();
  // 函数声明不需要清空其中基本块，因为其不含基本块
  funcDeclares_.clear();
}

Module::Module(const std::string &name, 
                baseTypePtr type,
                std::vector<GlobalVar*> &globalVars,
                std::vector<Function*> &funcDefs,
                std::vector<Function*> &funcDeclares) : Value(name, type), globalVars_(globalVars), funcDefs_(funcDefs), funcDeclares_(funcDeclares) {
                  addLibs();
                }

void Module::addLibs() {
  start = static_cast<int>(funcDeclares_.size());
  std::vector<baseTypePtr> putch_arguTypes; // putch 和 putint 和 starttime stoptime 函数是一样的 arguTypes
  std::vector<baseTypePtr> putarray_arguTypes; 
  std::vector<baseTypePtr> putfloat_arguTys; 
  std::vector<baseTypePtr> putfarrary_arguTys; 
  std::vector<baseTypePtr> getarray_arguTys; 
  std::vector<baseTypePtr> getfarray_arguTys; 

  putch_arguTypes.push_back(i32Type);

  putarray_arguTypes.push_back(i32Type);
  putarray_arguTypes.push_back(int32PointerType);

  putfloat_arguTys.push_back(floatType);

  putfarrary_arguTys.push_back(i32Type);
  putfarrary_arguTys.push_back(floatPointerType);

  getarray_arguTys.push_back(int32PointerType);

  getfarray_arguTys.push_back(floatPointerType);

  Function *putch = new Function("putch", voidType, putch_arguTypes);
  Function *putint = new Function("putint", voidType, putch_arguTypes);
  Function *putarrary = new Function("putarray", voidType, putarray_arguTypes);
  Function *putfloat = new Function("putfloat", voidType, putfloat_arguTys);
  Function *putfarray = new Function("putfarray", voidType, putfarrary_arguTys);
  Function *before_main = new Function("before_main", voidType, Zero_Argu_Type_List);
  Function *after_main = new Function("after_main", voidType, Zero_Argu_Type_List);
  Function *_sysy_starttime = new Function("_sysy_starttime", voidType, putch_arguTypes);
  Function *_sysy_stoptime = new Function("_sysy_stoptime", voidType, putch_arguTypes);
  Function *getint = new Function("getint", i32Type, Zero_Argu_Type_List);
  Function *getch = new Function("getch", i32Type, Zero_Argu_Type_List);
  Function *getfloat = new Function("getfloat", floatType, Zero_Argu_Type_List);
  Function *getarray = new Function("getarray", i32Type, getarray_arguTys);
  Function *getfarray = new Function("getfarray", i32Type, getfarray_arguTys);

  funcDeclares_.push_back(putch);
  funcDeclares_.push_back(putint);
  funcDeclares_.push_back(putarrary);
  funcDeclares_.push_back(putfloat);
  funcDeclares_.push_back(putfarray);
  funcDeclares_.push_back(before_main);
  funcDeclares_.push_back(after_main);
  funcDeclares_.push_back(_sysy_starttime);
  funcDeclares_.push_back(_sysy_stoptime);
  funcDeclares_.push_back(getint);
  funcDeclares_.push_back(getch);
  funcDeclares_.push_back(getfloat);
  funcDeclares_.push_back(getarray);
  funcDeclares_.push_back(getfarray);
}

void Module::correctCheck() {
  for (auto global : globalVars_) {
    global->correctCheck();
  }
  for (auto func : funcDefs_) {
    func->correctCheck();
  }
}
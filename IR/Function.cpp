#include "../include/IR/Function.h"
USING_GIMC_NAMESPACE

//@C++_Learn 会隐式地调用没有指定初始化值的变量（bBlocks）的默认构造函数
Function::Function(const std::string &fName, baseTypePtr funcType, std::vector<baseTypePtr> &arguTypes)
                  : Value(fName, funcType), arguTypes_(arguTypes) {
                    this->setPrefix(false);
                  }

#include "../include/IR/Function.h"
#include "../include/IR/BBlock.h"     // @C++_Learn 由于 Function，BBlock 类中均使用了对方的函数，include 两个头文件
USING_GIMC_NAMESPACE

//@C++_Learn 会隐式地调用没有指定初始化值的变量（bBlocks）的默认构造函数
Function::Function(const std::string &fName, baseTypePtr funcType, std::vector<baseTypePtr> &arguTypes)
                  : Value(fName, funcType), arguTypes_(arguTypes) {
                    this->setLocalPrefix(false);
                  }

void Function::clearFunc() {
  for (auto bBlock : bBlocks_) {
    bBlock->clearBBlock(); 
    delete bBlock;  
  }
  bBlocks_.clear();
}
#include "../include/IR/GlobalVar.h"
USING_GIMC_NAMESPACE

std::string GlobalVar::getData() {
  // 返回 value 的初始化 llvm 代码
  if (values_.size() == 0) {
    fprintf(stderr, "Have no initialization of this global var: %s\n", this->getName().c_str());
  }
  std::shared_ptr<PointerType> ptr = std::dynamic_pointer_cast<PointerType>(this->getType());
  if (ptr == nullptr) {
    fprintf(stderr, "GlobalVar type error\n");
    exit(1);
  }
  baseTypePtr basePtr = ptr->getBaseType();
  if (ptr->getArraySizeCnt() == 1) {
    // 非数组类型
    if (TypeBase::isInteger(basePtr)) {
      // 整数类型
      ConstIntValue* value = dynamic_cast<ConstIntValue*>(values_[0]);
      return std::to_string(value->getInt());
    }
    if (TypeBase::isFloat(basePtr)) {
      // 浮点数类型 @todo
    }
  }
  else {
    // 处理数组@todo
  }
  return nullptr;
}

baseTypePtr GlobalVar::getValueType() {
  if (values_.size() == 0) {
    // 没有 value 空赋值
    fprintf(stderr, "GlobalVar without initialization value\n");
    exit(1);
  }
  else {
    baseTypePtr type = values_[0]->getType();
    return type;
  }
}
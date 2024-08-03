#include "../include/IR/GlobalVar.h"
USING_GIMC_NAMESPACE

std::string GlobalVar::getData() {
  // 返回 value 的初始化 llvm 代码
  std::shared_ptr<PointerType> ptr = std::dynamic_pointer_cast<PointerType>(this->getType());
  if (ptr == nullptr) {
    error("GlobalVar type error");
    exit(1);
  }
  if (ptr->isArray() == false) {
    // 非数组类型，此处与 C 语言有所不同，数组初始化不一定为常数
    if (values_.size() == 0) {
      return "zeroinitializer";
    }
    return values_[0]->getData();
  }
  else {
    // 处理数组
    if (values_.size() == 0) {
      // 若不含初始化变量，则认为是 zeroinitializer
      return "zeroinitializer";
    }
    std::string ret = "[";
    for (int i = 0; i < values_.size(); i++) {
      ret += values_[i]->getType()->getDetailName();
      ret += " ";
      ret += values_[i]->getData();
      if (i != values_.size() - 1) {
        ret += ", ";
      }
    }
    ret += "]";
    return ret;
  }
}

void GlobalVar::correctCheck() {
  baseTypePtr ty = getValueType();
  if (TypeBase::isPointer(ty)) {
    // 说明全局变量为数组，则数组中每个元素的类型需要相同
    // @todo
  }
}
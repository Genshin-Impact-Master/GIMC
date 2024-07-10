#include "../include/IR/Type.h"

USING_GIMC_NAMESPACE

GIMC_NAMESPACE_BEGIN

baseTypePtr AddrLenPtr = std::make_shared<IntegerType>(ADDR_LENGTH);
baseTypePtr i32Type = std::make_shared<IntegerType>(32);
baseTypePtr i1Type = std::make_shared<IntegerType>(1);
baseTypePtr floatType = std::make_shared<FloatType>();
baseTypePtr voidType = std::make_shared<VoidType>();
baseTypePtr int32PointerType = std::make_shared<PointerType>(i32Type);

std::string PointerType::getDetailName() {
  if (!isArray()) {
    return getBaseType()->getDetailName();
  }
  else {
    std::string ret = "[";
    ret += std::to_string(cnt_);
    ret += " x ";
    ret += getBaseType()->getDetailName();
    ret += "]";
    return ret;
  }
}

GIMC_NAMESPACE_END

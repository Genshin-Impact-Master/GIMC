#include "../include/IR/Type.h"

USING_GIMC_NAMESPACE

GIMC_NAMESPACE_BEGIN

baseTypePtr i32TyPtr = std::make_shared<IntegerType>(32);
baseTypePtr i1TyPtr = std::make_shared<IntegerType>(1);
baseTypePtr fTyPtr = std::make_shared<FloatType>();
baseTypePtr voidTyPtr = std::make_shared<VoidType>();

GIMC_NAMESPACE_END

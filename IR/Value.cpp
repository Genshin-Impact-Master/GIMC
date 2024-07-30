#include "../include/IR/Value.h"

USING_GIMC_NAMESPACE

const std::string Value::LOCAL_PREFIX = "%";
const std::string Value::FUNC_OR_GLOBAL_PREFIX = "@";

GIMC::Value GIMC::voidValue("__Void__V", voidType);
#include "../include/IR/IRBuilder.h"
USING_GIMC_NAMESPACE

Module IRBuilder::createModule(const std::string &name,
                                baseTypePtr type,
                                std::vector<GlobalVar*> globalVars)
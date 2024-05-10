#include "../include/IR/Inst.h"

USING_GIMC_NAMESPACE

Instruction::Instruction(const std::string &name,
                         baseTypePtr type,
                         InstKind kind,
                         BBlock *parent) : Value(name, type), kind_(kind), parent_(parent) {}

Instruction::Instruction(baseTypePtr type, InstKind kind, BBlock *parent) :
                         Instruction(std::to_string(parent->getCnt()),
                                     type, kind, parent) {}

Instruction::Instruction(InstKind kind, BBlock *parent) : Instruction(i32TyPtr, kind, parent) {}

Instruction::Instruction(const std::string &name, InstKind kind, BBlock *parent) :
                         Instruction(name, i32TyPtr, kind, parent) {}


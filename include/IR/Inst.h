#ifndef INST_H_
#define INST_H_

#include "../Config.h"
#include "BBlock.h"
#include "Value.h"
#include "Type.h"
GIMC_NAMESPACE_BEGIN

class TypeBase;
class IRBuilder;
class BBlock;

/**
 * 代表 Instruction 的种类的枚举类型类
 * 所有 Instruction 子类也共用（方便 dump 输出）
*/
enum class InstKind {
  // 二元算术操作
  BinaryOPBegin,
  Add,
  Sub,
  Mul,
  Div,
  BinaryOpEnd
};

/**
 * Instruction 类，以 InstKind 作为指令种类
*/
class Instruction : public Value {
friend class IRBuilder;
private:
  InstKind kind_;                 // 指令的种类
  BBlock *parent_;                // 指示包含该指令的 BBlock
public:
  Instruction(const std::string &name,
              baseTypePtr type,
              InstKind kind,
              BBlock *parent);
  Instruction(baseTypePtr type, InstKind kind, BBlock *parent);
  Instruction(InstKind kind, BBlock *parent);
  Instruction(const std::string &name, InstKind kind, BBlock *parent);
  const std::string getTypeName() {return getType()->getName();}
  virtual ~Instruction() = default;
};

/**
 * 二元操作指令
*/
class BinaryInst final : public Instruction {
friend class IRBuilder;
private:
  Value *lhs_;  // 左操作 Value
  Value *rhs_;  // 右操作 Value
public:
  BinaryInst(const std::string &name,
             baseTypePtr type,
             InstKind kind,
             BBlock *parent,
             Value *lhs,
             Value *rhs)
            : Instruction(name, type, kind, parent), lhs_(lhs), rhs_(rhs) {}
  
};

GIMC_NAMESPACE_END

#endif //INST_H_
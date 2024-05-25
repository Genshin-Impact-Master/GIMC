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
  BinaryOpEnd,
  Alloca,
  Store,
  Load,
  Call,
  Ret
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

/**
 * 分配内存并产生指向该内存指针的指令
*/
class Alloca final : public Instruction {
friend class IRBuilder;
private:
  // baseTypePtr cntType;                    // 计数元素类型
public:
  /**
   * 此处传递的 baseTypePtr 需要为 PointerType 的指针
  */
  Alloca(const std::string &name,
         baseTypePtr type,
         BBlock *parent) : Instruction(name, type, InstKind::Alloca, parent) {}
};

/**
 * store 不产生 Value
*/
class Store final : public Instruction {
friend class IRBuilder;
private:
  Value *input_;                      // 需要存入的数据
  Value *ptr_;                        // 存入的内存指针
public:
  Store(const std::string &name,
        baseTypePtr type,
        BBlock *parent,
        Value *input,
        Value *ptr) : Instruction(name, type, InstKind::Store, parent), input_(input), ptr_(ptr) {} 
  // Value* getInput() {return input_;}
  // Value* getPtr() {return ptr_;}
};

class Load final : public Instruction {
friend class IRBuilder;
private:
  Value *ptr_;
public:
  Load(const std::string &name,
       baseTypePtr type,
       BBlock *parent,
       Value *ptr) : Instruction(name, type, InstKind::Load, parent), ptr_(ptr) {}
};

class Call final : public Instruction {
friend class IRBuilder;
private:
Function *func_;
std::vector<Value*> argus_;
public:
  Call(const std::string &name,
        baseTypePtr type,
        BBlock *parent,
        Function *func,
        std::vector<Value*> &argus) : Instruction(name, type, InstKind::Call, parent), func_(func), argus_(argus) {}
};

/**
 * Ret 指令所代表 Value 的类型即为返回值类型
 * @see IRBuilder.cpp
*/
class Ret final : public Instruction {
friend class IRBuilder;
private:
Value* retValue_;
public:
  Ret(const std::string &name,
      baseTypePtr type,
      BBlock *parent,
      Value* retValue) : Instruction(name, type, InstKind::Ret, parent), retValue_(retValue) {}
};
GIMC_NAMESPACE_END

#endif //INST_H_
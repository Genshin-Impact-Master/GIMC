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
  Ret,
  Icmp,
  Br,
  GEP
};

/**
 * Icmp 比较条件的类型
*/
enum class CondKind {
  Eq,
  Ne,
  Ugt,
  Uge,
  Ult,
  Ule,
  Sgt,
  Sge,
  Slt,
  Sle
};

/**
 * Instruction 类，以 InstKind 作为指令种类
*/
class Instruction : public Value {
friend class IRBuilder;
private:
  InstKind kind_;                   // 指令的种类
  BBlock *parent_;                  // 指示包含该指令的 BBlock
protected:
  std::vector<Value*> ops_;         // 可能用到的操作数
  std::vector<Value*> argus_;       // 参数列表，仅 Call 用到
  CondKind ckind_;                  // 在 icmp 指令中的 compare 类型
public:
  Instruction(const std::string &name,
              baseTypePtr type,
              InstKind kind,
              BBlock *parent);
  Instruction(const std::string &name,
              baseTypePtr type,
              InstKind kind,
              BBlock *parent,
              std::vector<Value*> argus);
  Instruction(const std::string &name,
              baseTypePtr type,
              InstKind kind,
              BBlock *parent,
              CondKind ckind);
  Instruction(baseTypePtr type, InstKind kind, BBlock *parent);
  Instruction(InstKind kind, BBlock *parent);
  Instruction(const std::string &name, InstKind kind, BBlock *parent);
  virtual ~Instruction() = default;
};

/**
 * 二元操作指令
*/
class BinaryInst final : public Instruction {
private:
public:
  /**
   * @param lhs 左操作数
   * @param rhs 右操作数
  */
  BinaryInst(const std::string &name,
             baseTypePtr type,
             InstKind kind,
             BBlock *parent,
             Value *lhs,
             Value *rhs);
  
};

/**
 * 分配内存并产生指向该内存指针的指令
*/
class Alloca final : public Instruction {
private:
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
private:
public:
  /**
   * @param input 需要存入的数据
   * @param ptr   存入的内存指针
  */
  Store(const std::string &name,
        baseTypePtr type,
        BBlock *parent,
        Value *input,
        Value *ptr);
};

class Load final : public Instruction {
private:
public:
  /**
   * @param ptr Load 需要加载到的地址的指针
  */
  Load(const std::string &name,
       baseTypePtr type,
       BBlock *parent,
       Value *ptr);
};

class Call final : public Instruction {
private:
public:
  /**
   * @param func  需要调用的 Function
   * @param argus 调用方程的参数
  */
  Call(const std::string &name,
        baseTypePtr type,
        BBlock *parent,
        Function *func,
        std::vector<Value*> &argus);
};

/**
 * Ret 指令所代表 Value 的类型即为返回值类型
 * @see IRBuilder.cpp
*/
class Ret final : public Instruction {
private:
public:
  /**
   * @param retValue 返回值
  */
  Ret(const std::string &name,
      baseTypePtr type,
      BBlock *parent,
      Value* retValue);
};

/**
 * Icmp 指令 比较两个整型 或 指针参数
*/
class Icmp final : public Instruction {
private:
public:
  /**
   * @param kind 表示比较类型
  */
  Icmp(const std::string &name,
      baseTypePtr type,
      BBlock *parent,
      CondKind kind,
      Value *first,
      Value *second);
};

/**
 * Br 指令，提供有条件跳转或无条件跳转
*/
class Br final : public Instruction {
private:
public:
  /**
   * @param cond 跳转的条件可以理解为 bool 值
  */
  Br(const std::string &name,
      baseTypePtr type,
      BBlock *parent,
      Value *cond,
      BBlock *ifTrue,
      BBlock *ifFalse);
};

/**
 * GEP 指令 获取数组元素地址 
*/
class GEP final : public Instruction {
public:
  /**
   * @param ptr     给定数组的基址
   * @param offset  相对基址偏移量
  */
  GEP(const std::string &name,
      baseTypePtr type,
      BBlock *parent,
      Value *ptr,
      int offset);
};

GIMC_NAMESPACE_END

#endif //INST_H_
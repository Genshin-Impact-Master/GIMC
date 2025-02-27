#ifndef INST_H_
#define INST_H_

#include "../Config.h"
#include "BBlock.h"
#include "Value.h"
#include "Type.h"
#include <unordered_map>
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
  SRem,
  Addf,
  Subf,
  Mulf,
  Divf,
  And,
  Or,
  BinaryOpEnd,
  Alloca,
  Store,
  Load,
  Call,
  Ret,
  Icmp,
  Fcmp,
  Br,
  GEP,
  Fp2Int,
  Int2Fp,
  Zext,
  Phi,
  InitMem
};

/**
 * Icmp 比较条件的类型
*/
enum class ICondKind {
  Eq,                 // 相等
  Ne,                 // 不等
  Ugt,                // 无符号 大于
  Uge,                // 无符号 大于等于
  Ult,                // 无符号 小于
  Ule,                // 无符号 小于等于
  Sgt,                // 有符号 大于
  Sge,                // 有符号 大于等于
  Slt,                // 有符号 小于
  Sle                 // 有符号 小于
};

/**
 * Fcmp 比较条件的类型
 */
enum class FCondKind {
  Oeq,                // 等于
  Ogt,                // 大于
  Oge,                // 大于等于
  Olt,                // 小于
  Ole,                // 小于等于
  One                 // 不等于
};

union CondKind {
  FCondKind fCond;
  ICondKind iCond;
};

/**
 * Instruction 类，以 InstKind 作为指令种类
*/
class Instruction : public Value {
friend class IRBuilder;
private:
  InstKind kind_;                   // 指令的种类
  BBlock *parent_;                  // 指示包含该指令的 BBlock
  INode<Instruction> instNode_;     // 自身对应于一个 Instruction 结点
protected:
  CondKind ckind_;                  // 在 icmp 指令或 fcmp 指令中的 compare 类型
  bool isParam_ = false;
public:
  Instruction(const std::string &name,
              baseTypePtr type,
              InstKind kind,
              BBlock *parent);
  Instruction(const std::string &name,
              baseTypePtr type,
              InstKind kind,
              BBlock *parent,
              CondKind ckind);
  Instruction(baseTypePtr type, InstKind kind, BBlock *parent);
  Instruction(InstKind kind, BBlock *parent);
  Instruction(const std::string &name, InstKind kind, BBlock *parent);
  virtual ~Instruction() = default;
  INode<Instruction> &getNode() {return instNode_;};
  void calculateDef_Uses();
  bool isAllocaInst() {return kind_ == InstKind::Alloca;}
  BBlock *getParent() {return parent_;}
  InstKind getKind() {return kind_;}
  // 一般指令的 hash 计算 InstKind + ops_
  uint32_t getHash() override;
  bool isEqual(Value *t) override;
  virtual void correctCheck() {};
  // 对于 Fcmp 和 Icmp 获得其对比类型
  CondKind getCondKind() {return ckind_;}
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
  
  // 获取左操作数
  Value *getLhs() {
    return ops_[0];
  }

  // 获取右操作数
  Value *getRhs() {
    return ops_[1];
  }

  bool isEqual(Value *t) override ;

  // 对于某些二元操作数，可以换位
  uint32_t getHash() override;

  void correctCheck() override {
    if (ops_.size() != 2) {
      error("BinaryInst 必须为两个操作数");
    }
    if (!ops_[0] || !ops_[1]) {
      error("BinaryInst 两个 Value* 不能为 nullptr");
    }
    if (!ops_[0]->getType()->isEqual(getType()) || !ops_[1]->getType()->isEqual(getType())) {
      error("BinaryInst 两个操作数类型不等或不与二元操作指令类型相等");
    }
  }
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
  
  void correctCheck() override {
    if (!TypeBase::isPointer(getType())) {
      error("Alloca 指令必须为 pointer 类型");
    }
  }
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
  
  // 获取存取的数据
  Value *getInput() {
    return ops_[0];
  }

  // 获取 store 存入的内存指针 
  Value *getPtr() {
    return ops_[1];
  }

  void correctCheck() override {
    if (ops_.size() != 2)
      error("Store 参数数目不匹配");
    if (!ops_[0] || !ops_[1])
      error("Store 参数不能为 nullptr");
    if (!TypeBase::isPointer(getPtr()->getType())) {
      error("Store 指令存入内存指针非 Pointer 类型");
    }
  }
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
  
  // 获取需要加载的指针
  Value *getPtr() {return ops_[0];} 

  void correctCheck() override {
    if (ops_.size() != 1)
      error("Load 参数数目有误");
    if (!getPtr())
      error("Load 参数不能为 nullptr");
    if (!getType()->isEqual(getPtr()->getType()))
      error("Load 存入地址指针类型必须是 Pointer"); 
  }
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

  // 获取所调用的 Function
  Function *getFunc() {return dynamic_cast<Function*>(ops_[0]);}

  // 获取所 Call 函数的参数链表，注意从 1 开始
  std::vector<Value*> &getArgus() {return ops_;}

  void correctCheck() override {
    if (static_cast<int>(ops_.size()) < 1)
      error("Call 参数数目有误");
    if (!ops_[0]) {
      error("Call Function 不能为 nullptr");
    }
    if (!getType()->isEqual(ops_[0]->getType())) {
      error("Call 函数返回值类型与 Call 指令类型不相等");
    }
  }
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
  
  // 获取返回值
  Value *getRetValue() {return ops_[0];}

  void correctCheck() override {
    // 接下来的指令只检测 Type，不再进行 nullptr 检验
    if (!ops_[0]->getType()->isEqual(getType())) {
      error("Ret 类型错误");
    }
  }

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
      ICondKind kind,
      Value *first,
      Value *second);

  // 获取第一个数据
  Value *getFirst() {return ops_[0];}

  // 获取第二个数据
  Value *getSecond() {return ops_[1];}

  void correctCheck() override {
    // 检验两个数据类型是否相等
    if (!ops_[0]->getType()->isEqual(ops_[1]->getType())) {
      error("Icmp 两个类型不同的操作数不能比较");
    }
  }
};

/**
 * Fcmp 指令 比较两个 float
 */
class Fcmp final : public Instruction {
public:
  /**
   * @param kind 表示比较类型
   */
  Fcmp(const std::string &name,
      baseTypePtr type,
      BBlock *parent,
      FCondKind kind,
      Value *first,
      Value *second);
  
  // 获取第一个数据
  Value *getFirst() {return ops_[0];}

  // 获取第二个数据
  Value *getSecond() {return ops_[1];}

  void correctCheck() override {
    // 检验两个数据类型是否相等
    if (!ops_[0]->getType()->isEqual(ops_[1]->getType())) {
      error("Fcmp 两个类型不同的操作数不能比较");
    }
  }
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
  
  // 判断是否为无条件跳转
  bool isUnconditional();

  // 获取条件值
  Value *getCond() {
    if (isUnconditional()) {
      error("为无条件跳转，没有 Cond");
      exit(1);
    }
    return ops_[0];
  }

  // 获取 条件为 True 的 BBlock
  BBlock *getTrueBBlk() {
    if (isUnconditional())
      return dynamic_cast<BBlock*>(ops_[0]);
    return dynamic_cast<BBlock*>(ops_[1]);
  }

  // 获取 条件为 False 的 BBlock
  BBlock *getFalseBBlk() {
    if (isUnconditional()) {
      error("无条件跳转，没有 False 基本块");
    }
    return dynamic_cast<BBlock*>(ops_[2]);
  }

  void correctCheck() override {
    // GIMC 中 Br 指令必须在 cmp 指令后
    if (isUnconditional())
      return;
    Instruction *pre = getNode().getPre()->getOwner();
    if (pre != ops_[0]) {
      error("GIMC 中有条件跳转前一条指令必须为其跳转条件");
    }
  }
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
      Value *offset);

  // GEP 指令数组基址
  Value* getPtr() {return ops_[0];}

  // 获得偏移量的 Value
  Value* getOffsetValue() {return ops_[1];}

  void correctCheck() override {
    // 检验两个数据类型
    if (!TypeBase::isPointer(ops_[0]->getType())) {
      error("GEP 指针参数的类型必须为 Pointer");
    }
  }

  void setIsParam(bool isParam) {
    isParam_ = isParam;
  }
};

/**
 * Fp2Int 指令，Float 转为 int
 */
class Fp2Int final : public Instruction {
public:
  Fp2Int(const std::string &name,
          baseTypePtr type,
          BBlock *parent,
          Value *fp);

  // 获取待转换的 Float Value
  Value *getFp() {return ops_[0];}
  void correctCheck() override {
    // 检验 float 类型
    if (!TypeBase::isFloat(ops_[0]->getType())) {
      error("Fp2Int 转换的数据类型必须为 Float");
    }
  }
};

/**
 * Int2Fp 指令，int 转为 Float
 */
class Int2Fp final : public Instruction {
public:
  Int2Fp(const std::string &name,
          baseTypePtr type,
          BBlock *parent,
          Value *i32);
  // 获取待转换的 Int Value
  Value *getInt() {return ops_[0];}
  void correctCheck() override {
    if (!TypeBase::isInteger(ops_[0]->getType())) {
      error("Int2Fp 转换的数据类型必须为 int");
    }
  }
};

class Zext final : public Instruction {
public:
  /**
   * @param proto 需要改变的 Value
   * @param type 最终的数据类型
   */
  Zext(const std::string &name,
        baseTypePtr type,
        BBlock *parent,
        Value *proto) : Instruction(name, type, InstKind::Zext, parent) {ops_.push_back(proto);}

  // 获得零拓展前的 Value
  Value *getProto() {return ops_[0];}
  void correctCheck() override {
    if (!TypeBase::isInteger(ops_[0]->getType())) {
      error("Zext 转换的数据类型必须为 int");
    }
    // Zext 前一个指令必须为 CMP 指令
    Instruction *i = getNode().getPre()->getOwner();
    InstKind kind = i->getKind();
    if (kind != InstKind::Icmp && kind != InstKind::Fcmp) {
      error("Zext 前一个指令必须为 ICMP 或 FCMP");
    }
  }
};

class Phi final : public Instruction {
public:
  /**
   * @param maps 按照 Value，BBlock 为一组的方式存储进向量中
   */
  Phi(const std::string &name,
      baseTypePtr type,
      BBlock *parent,
      std::vector<Value*> maps);

  // 获取 phi 结点对应的变量
  Value *getAllocaPtr() {return ops_[0];}   // 由于构建 phi 结点时默认首先插入变量的 alloca 指令

  // 获取 ops
  std::vector<Value*>& getOps() {return ops_;}

  void correctCheck() override {
    if (!TypeBase::isPointer(ops_[0]->getType())) {
      error("Phi 指令第一个参数必须为 Alloca 类型");
    }
  }
};

class InitMem final : public Instruction {
public:
  /**
   * 数组全初始化为 0
   * @param length 将长度为 length 的字节数置为 0 （注意字节数为数组总长度 * 4）
   */
  InitMem(const std::string &name,
          baseTypePtr type,
          BBlock *parent,
          Value *ptr,
          int length);

  int getLength() {
    uint32_t len = dynamic_cast<ConstIntValue*>(ops_[1])->getInt();
    return (int)len;
  }

  Value* getPtr() {return ops_[0];}

  void correctCheck() override {
    if (!TypeBase::isPointer(ops_[0]->getType())) {
      error("InitMem 内存参数的数据类型必须是 pointer");
    }
  }
};
GIMC_NAMESPACE_END

#endif //INST_H_
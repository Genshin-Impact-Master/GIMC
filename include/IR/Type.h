#ifndef TYPE_H_
#define TYPE_H_

#include "../Config.h"
#include <string>
#include <cassert>
#include <memory>
GIMC_NAMESPACE_BEGIN

// 基础类型，所有数据类型的基类
class TypeBase {  
public:
  virtual ~TypeBase() = default;              //@C++_Learn 当基类指针/引用指向子类时，会调用子类析构函数
  virtual std::string getName() const = 0;    //@C++_Learn 纯虚函数，子类必须实现  
};  

// 整数数据类型
class IntegerType final : public TypeBase {  
private:
  int int_w;  // int 字长
public:
  // 构造长度为 length 比特的 Int 类型
  IntegerType(int length) : int_w(length) {
    assert((length == 16 || length == 32 || length == 64) 
          && "整型字长必须为 16 or 32 or 64");

    if (!(length == 16 || length == 32 || length == 64))
      fprintf(stderr, "Invalid Int length\n");              //@todo 统一的错误报告模板
  }

  // 默认构造 32 位长的 int
  IntegerType() : int_w(32) {}

  // 整型获取类型名用于 emit llvm
  std::string getName() const override { return "i" + std::to_string(int_w); }
};  

// 浮点数数据类型
class FloatType final : public TypeBase {  
public:
  /**
   * @todo 构造函数
  */
  FloatType() {}

  /**
   * 浮点数获取类型名用于 emit llvm
   * @todo
  */
  std::string getName() const override { return "Float"; }  
};

// void 数据类型
class VoidType final : public TypeBase {
public:
  std::string getName() const override {
    return "void";
  }
};

// 指针类型
class PointerType final : public TypeBase {
private:
  baseTypePtr base_;
  int cnt_; 
public:
  PointerType(baseTypePtr base, int cnt) : base_(base), cnt_(cnt) {}
  PointerType(baseTypePtr base) : PointerType(base, 1) {}
  PointerType(const PointerType&) = delete;                             // @C++_Learn 禁用拷贝构造函数和赋值运算符，防止浅拷贝
  PointerType& operator=(const PointerType&) = delete;

  baseTypePtr getBaseType() {return base_;}                             // 返回指针指向的数据类型
  std::string getName() const override {return base_->getName();}
  int getArraySizeCnt() {return cnt_;}
};

/**
 * 给每种类型都构造一个对象
 * 所有使用基础类型的指针都指向这些对象
*/
// @C++_Learn 此处使用 shared_ptr 保证其所指内存在无对象指向时销毁
extern baseTypePtr i32TyPtr;         // 32位长的 int 类型实例
extern baseTypePtr fTyPtr;
extern baseTypePtr voidTyPtr;

GIMC_NAMESPACE_END

#endif // TYPE_H_
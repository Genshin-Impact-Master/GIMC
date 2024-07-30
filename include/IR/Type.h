#ifndef TYPE_H_
#define TYPE_H_

#include "../Config.h"
#include <string>
#include <cassert>
#include <memory>
GIMC_NAMESPACE_BEGIN

class PointerType;
class IntegerType;
class FloatType;
class VoidType;

// 基础类型，所有数据类型的基类
class TypeBase {
protected:
  int size_;                                  // 类型占据的字节数
public:
  TypeBase(int size) : size_(size) {}
  TypeBase() : size_(4) {}                    // 默认 4 字节大小
  virtual ~TypeBase() = default;              //@C++_Learn 当基类指针/引用指向子类时，会调用子类析构函数
  virtual std::string getName() const = 0;    //@C++_Learn 纯虚函数，子类必须实现  
  virtual std::string getDetailName() {return getName();}

  int getSize() {return size_;}

  bool static isInteger(baseTypePtr type) {
    return std::dynamic_pointer_cast<IntegerType>(type) != nullptr;   // @C++_Learn 智能指针转换
  }
  
  static bool isFloat(baseTypePtr type) {
    return std::dynamic_pointer_cast<FloatType>(type) != nullptr;
  }

  bool static isPointer(baseTypePtr type) {
    return std::dynamic_pointer_cast<PointerType>(type) != nullptr;
  }

  bool static isVoid(baseTypePtr type) {
    return std::dynamic_pointer_cast<VoidType>(type) != nullptr;
  }
};  

// 整数数据类型
class IntegerType final : public TypeBase {  
private:
  int int_w;  // int 字长
public:
  // 构造长度为 length 比特的 Int 类型
  IntegerType(int length) : int_w(length) {
    assert((length == 1 || length == 8 || length == 16 || length == 32 || length == 64) 
          && "整型字长必须为 1 or 16 or 32 or 64");

    if (!(length == 1 ||  length == 8  || length == 16 || length == 32 || length == 64))
      fprintf(stderr, "Invalid Int length\n");              //@todo 统一的错误报告模板
    switch (length) {
      case 1:
      case 8:
        size_ = 1;
        break;
      case 16:
        size_ = 2;
      case 32:
        size_ = 4;
      case 64:
        size_ = 8;
      default:
        break;
    }
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
   * 构造函数
  */
  FloatType() {}

  /**
   * 浮点数获取类型名用于 emit llvm
  */
  std::string getName() const override { return "float"; }  
};

// void 数据类型
class VoidType final : public TypeBase {
public:
  VoidType() {size_ = 0;}
  std::string getName() const override {
    return "void";
  }
};

// 指针类型
class PointerType final : public TypeBase {
private:
  baseTypePtr base_;
  int cnt_;             // 数组元素则为其个数，非数组变量用 0 代替 1
public:
  PointerType(baseTypePtr base, int cnt) : base_(base), cnt_(cnt) {
    size_ = cnt * base->getSize();
  }
  PointerType(baseTypePtr base) : PointerType(base, 0) {}               // cnt 为 0 表示构造非数组变量
  PointerType(const PointerType&) = delete;                             // @C++_Learn 禁用拷贝构造函数和赋值运算符，防止浅拷贝
  PointerType& operator=(const PointerType&) = delete;

  baseTypePtr getBaseType() {return base_;}                             // 返回指针指向的数据类型
  std::string getName() const override {return "ptr";}
  std::string getDetailName() override;
  int getArraySizeCnt() {return cnt_;}

  bool isArray() {return cnt_!=0;}
};

/**
 * 给每种类型都构造一个对象
 * 所有使用基础类型的指针都指向这些对象
*/
// @C++_Learn 此处使用 shared_ptr 保证其所指内存在无对象指向时销毁
extern baseTypePtr AddrLenPtr;
extern baseTypePtr i32Type;          // 32 位长的 int 类型实例
extern baseTypePtr i1Type;           // 1 位长的 int 类型实例
extern baseTypePtr floatType;
extern baseTypePtr voidType;
extern baseTypePtr int32PointerType;
extern baseTypePtr floatPointerType;

GIMC_NAMESPACE_END

#endif // TYPE_H_
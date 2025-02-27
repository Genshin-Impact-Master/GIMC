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

  // 获取类型占据的空间，若为 PointerType 则返回其指向数组大小
  virtual int getSize() {return size_;}

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

  // 判断类型是否相等
  virtual bool isEqual(baseTypePtr ty) = 0; 
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
      error("Invalid Int length");              //@todo 统一的错误报告模板
    switch (length) {
      case 1:
      case 8:
        size_ = 1;
        break;
      case 16:
        size_ = 2;
        break;
      case 32:
        size_ = 4;
        break;
      case 64:
        size_ = 8;
        break;
      default:
        break;
    }
  }

  // 默认构造 32 位长的 int
  IntegerType() : int_w(32) {}

  // 整型获取类型名用于 emit llvm
  std::string getName() const override { return "i" + std::to_string(int_w); }

  // 获取 type 的长度
  int getBitWidth() {return int_w;}

  bool isEqual(baseTypePtr ty) override {
    std::shared_ptr<IntegerType> intTy = std::dynamic_pointer_cast<IntegerType>(ty);
    if (!intTy) 
      return false;
    if (intTy->getBitWidth() != int_w)
      return false;
    return true;
  }
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

  bool isEqual(baseTypePtr ty) override {
    return TypeBase::isFloat(ty);
  }
};

// void 数据类型
class VoidType final : public TypeBase {
public:
  VoidType() {size_ = 0;}
  std::string getName() const override {
    return "void";
  }
  bool isEqual(baseTypePtr ty) override {
    return TypeBase::isVoid(ty);
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

  bool isEqual(baseTypePtr ty) override {
    std::shared_ptr<PointerType> ptr = std::dynamic_pointer_cast<PointerType>(ty);
    if (!ptr) 
      return false;
    if (cnt_ != ptr->getArraySizeCnt())
      return false;
    return true;
  }

  int getSize() override {
    if (cnt_ == 0) {
      // 说明为非数组变量，pointer 所指向的大小即为 baseType 的大小
      return base_->getSize();
    }
    size_ = getBaseType()->getSize() * cnt_;
    return size_;
  }
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
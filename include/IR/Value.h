#ifndef VALUE_H_
#define VALUE_H_

#include "../Config.h"
#include <cstdint>
#include <string>
#include <memory> //@C++_Learn 用于智能指针 unique_ptr,shared_ptr...
#include "Type.h"
#include "../Utils/IList.h"
#include <functional>
GIMC_NAMESPACE_BEGIN

class VoidType;

/**
 * IR 最基础类型，SSA 中的值
*/
class Value {
private:
  std::string valueName;                            // value 的名称
  static const std::string LOCAL_PREFIX;            // 本地 变量 or 常量 or 指令的前缀
  static const std::string FUNC_OR_GLOBAL_PREFIX;   // 全局变量 or 函数
  std::string fullName;                             // emit LLVM 时用到的全称
  std::string prefix;                               // emit LLVM 时用到的前缀
  std::vector<Value*> uses_;                        // 在哪些 Value 中被用到
  // @C++_Learn 因为 TypeBase 里面有纯虚函数，故 TypeBase 不能被实例化，只能传递其引用 or 指针
  baseTypePtr type_;                                // Value 的数据类型的指针
  bool isValid_ = true;                             // 是否有效（优化可能会删除）
  uint32_t hashcode = 0;                            // 存储 hash 值，避免每次都要重新计算
  bool hashed = false;                              // 记录是否进行了 hashcode 的计算
protected:
  std::vector<Value*> ops_;                         // 用到了哪些 Value
public:
  /**
   * @todo 带名称 Value 初始化
   * 如 Function,变量等
  */
  Value(const std::string &name, baseTypePtr type) : 
        valueName(name),
        type_(type),
        fullName(LOCAL_PREFIX + name),
        prefix(LOCAL_PREFIX) {}

  // 匿名构造函数
  Value(baseTypePtr type) : Value("anonymous", type) {}

  /**
   * 获取 Value 的 string 形式引用，如一个 ConstValue 则获取具体值
   * 一个 变量 Value 则获得其名称
  */
  virtual std::string& getName() {return valueName;}

  // 获取带前缀的 Value 名
  virtual std::string& getFullName() {return fullName;}

  // 获取 Value 的值
  virtual std::string getData() {return "no value";}

  // 修改 name 值
  void setValueName(const std::string& newName) {
    valueName = newName;
    fullName = prefix + newName;
  }

  // 修改为 GlobalVar 前缀
  void setGlobalVarPrefix() {
    prefix = FUNC_OR_GLOBAL_PREFIX + "_gimc_";
    fullName = prefix + valueName;
  }

  // 修改为 Function 前缀
  void setFunctionPrefix() {
    prefix = FUNC_OR_GLOBAL_PREFIX;
    fullName = prefix + valueName;
  }

  baseTypePtr getType() {return type_;}

  const std::string getTypeName() {return getType()->getName();}

  // 获得使用本 Value 的值的链表
  std::vector<Value*>& getUses() {return uses_;}
  // 获得本变量使用的值的链表
  std::vector<Value*>& getDefs() {return ops_;}

  bool isValid() {return isValid_;}

  void setValid(bool v) {isValid_ = v;}

  virtual ~Value() = default;

  virtual uint32_t getHash() {
    if(!hashed) {
      hashed = true;
      hashcode = std::hash<std::string>()(getFullName());
    }
    return hashcode; 
  }

  bool isHashed() {return hashed;}

  void setIsHashed(bool b) {hashed = b;}

  void setHashCode(uint32_t v) {hashcode = v; hashed = true;}

  /**
   * 在替换 Value* 或新插入时维护 def-use 链表且将 hashed 设为 false
   * @param newOne 新插入的 Value*
   * @param pos 需要在 ops_ 中插入的位置，若为 -1 表示在尾部插入
   **/ 
  virtual void updateValue(Value* newOne, int pos) {
    if (pos == -1) {
      ops_.push_back(newOne);
      hashed = false;
      return;
    }
    ops_[pos] = newOne;
    newOne->getUses().push_back(this);
    hashed = false;
  }

  // 对于普通的 Value *，只需对比他们两个是否相等即可。 
  virtual bool isEqual(Value *t) {
    return this == t;
  }
};

// 仅仅作为占位，实际上任何一个 voidType 的 Value 都 ok
extern Value voidValue;
GIMC_NAMESPACE_END


#endif //VALUE_H_
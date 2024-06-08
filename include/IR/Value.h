#ifndef VALUE_H_
#define VALUE_H_

#include "../Config.h"
#include <cstdint>
#include <string>
#include <memory> //@C++_Learn 用于智能指针 unique_ptr,shared_ptr...
#include "Type.h"
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

  // @C++_Learn 因为 TypeBase 里面有纯虚函数，故 TypeBase 不能被实例化，只能传递其引用 or 指针
  baseTypePtr type_;                                // Value 的数据类型的指针
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
  // @todo 需要添加自动加变量前缀的代码，这里先支持局部
  virtual std::string& getFullName() {return fullName;}

  // 修改 name 值
  void setValueName(const std::string& newName) {
    valueName = newName;
    fullName = prefix + newName;
  }

  // 修改前缀
  void setLocalPrefix(bool setLocal) {
    if (setLocal) prefix = LOCAL_PREFIX;
    else prefix = FUNC_OR_GLOBAL_PREFIX;
    fullName = prefix + valueName;
  }

  baseTypePtr getType() {return type_;}

  const std::string getTypeName() {return getType()->getName();}

  virtual ~Value() = default;
};

GIMC_NAMESPACE_END


#endif //VALUE_H_
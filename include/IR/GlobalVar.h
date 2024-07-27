#ifndef GLOBALVAR_H_
#define GLOBALVAR_H_

#include "../Config.h"
#include "ConstValue.h"


GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class IRBuilder;

class GlobalVar : public Value {
friend class IRBuilder;
private:
  std::vector<Value*> values_;
public:
  /**
   * @param type 全局变量的类型一定为指针
  */
  GlobalVar(const std::string &name, baseTypePtr type, std::vector<Value*> values)
           : Value(name, type), values_(values) { 
                                                  if(!TypeBase::isPointer(type)) 
                                                    fprintf(stderr, "全局变量类型必须为指针\n");
                                                  this->setLocalPrefix(false); 
                                                }

  std::string getData() override;     // @C++_Learn 注意 override 关键字不能出现在 class 外的函数定义中

  baseTypePtr getValueType() {return std::dynamic_pointer_cast<PointerType>(this->getType())->getBaseType();}
};

GIMC_NAMESPACE_END

#endif // GLOBALVAR_H_
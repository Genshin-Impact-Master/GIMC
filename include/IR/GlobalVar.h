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
  std::vector<ConstValue*> values_;
public:
  /**
   * @param type 全局变量的类型一定为指针
  */
  GlobalVar(const std::string &name, baseTypePtr type, std::vector<ConstValue*> values)
           : Value(name, type), values_(values) { 
                                                  if(!TypeBase::isPointer(type)) 
                                                    fprintf(stderr, "全局变量类型必须为指针\n");
                                                  this->setLocalPrefix(false); 
                                                }

  std::string getData();
  baseTypePtr getValueType();
  std::string getValueTypeName() {return getValueType()->getName();}
};

GIMC_NAMESPACE_END

#endif // GLOBALVAR_H_
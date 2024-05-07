#ifndef CONFIG_H_
#define CONFIG_H_
#define NDEBUG   //@C++_Learn 如果定义 NDEBUG 则 assert 不会工作

#define GIMC_NAMESPACE_BEGIN namespace GIMC {
#define GIMC_NAMESPACE_END }  // GIMC namespace
#define USING_GIMC_NAMESPACE using namespace GIMC;

#include <string>
#include <vector>

GIMC_NAMESPACE_BEGIN
/******************* 指令输出字符串 ********************/
/**
 * 与 InstKind 一一对应
 * @see IR/Inst.h
*/
std::vector<std::string> ST_Insts = {
  "IntegerOPBegin", "Add", "Sub", "Mul", "Div", "IntegerOPEND" 
};

GIMC_NAMESPACE_END

#endif // CONFIG_H_
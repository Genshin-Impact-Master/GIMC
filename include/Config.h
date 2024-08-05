#ifndef CONFIG_H_
#define CONFIG_H_
#define NDEBUG   //@C++_Learn 如果定义 NDEBUG 则 assert 不会工作

#define GIMC_NAMESPACE_BEGIN namespace GIMC {
#define GIMC_NAMESPACE_END }                          // GIMC namespace
#define USING_GIMC_NAMESPACE using namespace GIMC;
#define ADDR_LENGTH 32                                // 机器字长
#define STACK_ALIGN 8                                 // arm 栈对齐大小
//#define PRINT_CFG                                     // 设置此宏，将 CFG 生成出来

#include <string>
#include <vector>
#include <memory>
#include "Utils/ErrorConfig.h"
GIMC_NAMESPACE_BEGIN
// 通用函数
int alignsTo(int size, int alignSize);
/*********************************** 类型重命名 ***********************************/
class TypeBase;
class Value;
typedef std::shared_ptr<TypeBase> baseTypePtr;          // 数据类型基类指针

/*********************************** 全局变量 ************************************/
/**
 * 与 InstKind 一一对应，各个指令的 string
 * @see IR/Inst.h
*/
extern std::vector<std::string> ST_Insts;
extern std::vector<std::string> ST_IConds;
extern std::vector<std::string> ST_FConds;

// 定义一个空参数列表，所有零参函数在 call 时均使用此列表
extern std::vector<Value*> Zero_Argu_List;

// 定义一个空参数类型向量，在零参函数 declare 时使用
extern std::vector<baseTypePtr> Zero_Argu_Type_List;

GIMC_NAMESPACE_END

#endif // CONFIG_H_
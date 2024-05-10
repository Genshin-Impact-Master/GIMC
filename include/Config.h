#ifndef CONFIG_H_
#define CONFIG_H_
#define NDEBUG   //@C++_Learn 如果定义 NDEBUG 则 assert 不会工作

#define GIMC_NAMESPACE_BEGIN namespace GIMC {
#define GIMC_NAMESPACE_END }  // GIMC namespace
#define USING_GIMC_NAMESPACE using namespace GIMC;

#include <string>
#include <vector>
#include <memory>

GIMC_NAMESPACE_BEGIN
/*********************************** 类型重命名 ***********************************/
class TypeBase;
typedef std::shared_ptr<TypeBase> baseTypePtr;          // 数据类型基类指针

/*********************************** 全局变量 ************************************/
/**
 * 与 InstKind 一一对应，各个指令的 string
 * @see IR/Inst.h
*/
extern std::vector<std::string> ST_Insts;

GIMC_NAMESPACE_END

#endif // CONFIG_H_
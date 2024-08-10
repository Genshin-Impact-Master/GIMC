#ifndef CONFIG_H_
#define CONFIG_H_
#define NDEBUG   //@C++_Learn 如果定义 NDEBUG 则 assert 不会工作

#define GIMC_NAMESPACE_BEGIN namespace GIMC {
#define GIMC_NAMESPACE_END }                          // GIMC namespace
#define USING_GIMC_NAMESPACE using namespace GIMC;
#define ADDR_LENGTH 32                                // 机器字长
#define LIRINST_STRING ST_LirConds[static_cast<int>(inst->getKind())]
//#define PRINT_CFG                                     // 设置此宏，将 CFG 生成出来
// #define DEBUG_MODE                                    // 设置此宏开启 Debug 模式
#define COMMIT_MODE                                   // 提交模式

/*********************************************** 后端宏定义 **********************************************/
#define STACK_ALIGN 8                                 // arm 栈对齐大小
#define FP_REG 7                                      // 默认 r7 为 fp 寄存器
#define FLOAT_REG_START 16                            // 浮点寄存器在 ARM_REGS 中编号
#define APSR_REG_NUM 80
#define FPSCR_REG_NUM 81

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
extern std::vector<std::string> ST_ARM_STATUS;
extern std::vector<std::string> ST_LirConds;

// 定义一个空参数列表，所有零参函数在 call 时均使用此列表
extern std::vector<Value*> Zero_Argu_List;

// 定义一个空参数类型向量，在零参函数 declare 时使用
extern std::vector<baseTypePtr> Zero_Argu_Type_List;

// 定义 arm 汇编中用到的寄存器
extern std::vector<std::string> ARM_REGS;
GIMC_NAMESPACE_END

#endif // CONFIG_H_
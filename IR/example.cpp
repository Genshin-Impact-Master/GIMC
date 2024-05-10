#include "../include/IR/Function.h"
#include "../include/IR/Inst.h"
#include "../include/IR/IRBuilder.h"
#include "../include/IR/Type.h"
#include "../include/Config.h"

USING_GIMC_NAMESPACE

int main() {
  // 创建 IR 构造器对象
  IRBuilder builder;

  // 创建方程 "main"，返回类型为 i32
  Function* myFunc = builder.createFunction("main", i32TyPtr);

  // 创建基本块 entry
  builder.createBBlock("entry", voidTyPtr);

  // 创建一些指令实现如下代码
  /**
   * int main(){
   *    return 1 + (-2) * (3/(4-5))   // return 7
   * }
  */
  Instruction* i1 = builder.createBinaryInst(InstKind::Sub, new ConstIntValue(4), new ConstIntValue(5));
  Instruction* i2 = builder.createBinaryInst(InstKind::Div, new ConstIntValue(3), i1);
  Instruction* i3 = builder.createBinaryInst(InstKind::Mul, new ConstIntValue(-2), i2);
  Instruction* i4 = builder.createBinaryInst(InstKind::Add, new ConstIntValue(1), i3);
  
  // 由 IRBuilder 发射 LLVM 代码
  builder.emitIRFunc(myFunc);
  
  // 关闭 builder 的 irout 文件输出流
  builder.close();
}
#include "../include/IR/Function.h"
#include "../include/IR/Inst.h"
#include "../include/IR/IRBuilder.h"
#include "../include/IR/Type.h"
#include "../include/Config.h"

USING_GIMC_NAMESPACE

int main(int argc, char** args) {
  // 创建 IR 构造器对象
  IRBuilder builder;
  if (argc == 2) {
    builder = IRBuilder(args[1], nullptr, nullptr);
  }

  // 创建方程 "main"，返回类型为 i32
  Function* myFunc = builder.createFunction("main", i32TyPtr);

  // 创建基本块 entry
  builder.createBBlock("entry", voidTyPtr);

  // eg.1 创建一些指令实现如下代码
  /**
   * int main(){
   *    return 1 + (-2) * (3/(4-5))   // return 7
   * }
  */
  Instruction* i1 = builder.createBinaryInst(InstKind::Sub, new ConstIntValue(4), new ConstIntValue(5));
  Instruction* i2 = builder.createBinaryInst(InstKind::Div, new ConstIntValue(3), i1);
  Instruction* i3 = builder.createBinaryInst(InstKind::Mul, new ConstIntValue(-2), i2);
  Instruction* i4 = builder.createBinaryInst(InstKind::Add, new ConstIntValue(1), i3);
  
  // eg.2 实现局部变量与赋值
  /**
   * int main() {
        const int Nqn7m1 = 010;
        int yiersan = 456;
        int mAgIc_NuMbEr;
        mAgIc_NuMbEr = 8456;
        int a1a11a11 = (mAgIc_NuMbEr - yiersan) / 1000 - Nqn7m1, _CHAOS_TOKEN;
        _CHAOS_TOKEN = 2;
        a1a11a11 = a1a11a11 + _CHAOS_TOKEN;
        return a1a11a11;
        }
  */
  Instruction* i_2_1 = builder.createAllocaInst("Nqn7m1", i32TyPtr, 1);
  Instruction* i_2_2 = builder.createAllocaInst("yiersan", i32TyPtr, 1);
  Instruction* i_2_3 = builder.createAllocaInst("mAgIc_NuMbEr", i32TyPtr, 1);
  Instruction* i_2_4 = builder.createAllocaInst("a1a11a11", i32TyPtr, 1);
  Instruction* i_2_5 = builder.createAllocaInst("_CHAOS_TOKEN", i32TyPtr, 1);
  Instruction* i_2_6 = builder.createStoreInst(new ConstIntValue(8) ,i_2_1);        // Nqn7m1 = 010   8进制
  Instruction* i_2_7 = builder.createStoreInst(new ConstIntValue(456), i_2_2);
  Instruction* i_2_8 = builder.createStoreInst(new ConstIntValue(8456), i_2_3); 
  Instruction* i_2_9 = builder.createLoadInst(i32TyPtr, i_2_3);                     // mAgIc_NuMbEr load
  Instruction* i_2_10 = builder.createLoadInst(i32TyPtr, i_2_2);                    // yiersan load
  Instruction* i_2_11 = builder.createBinaryInst(InstKind::Sub, i_2_9, i_2_10);
  Instruction* i_2_12 = builder.createBinaryInst(InstKind::Div, i_2_11, new ConstIntValue(1000));
  Instruction* i_2_13 = builder.createBinaryInst(InstKind::Sub, i_2_12, new ConstIntValue(8));         // 常数折叠
  Instruction* i_2_14 = builder.createStoreInst(i_2_13, i_2_4);
  Instruction* i_2_15 = builder.createStoreInst(new ConstIntValue(2), i_2_5);
  Instruction* i_2_16 = builder.createLoadInst(i_2_4->getType(), i_2_4);            // 这里 Load Instruction 的 Type 同样为指针基类 type
  Instruction* i_2_17 = builder.createLoadInst(i_2_5->getType(), i_2_5);
  Instruction* i_2_18 = builder.createBinaryInst(InstKind::Add, i_2_16, i_2_17);
  Instruction* i_2_19 = builder.createStoreInst(i_2_18, i_2_4);                     // a1a11a11 = a1a11a11 + _CHAOS_TOKEN;
  Instruction* i_2_20 = builder.createLoadInst(i_2_4->getType(), i_2_4);

  // 由 IRBuilder 发射 LLVM 代码
  builder.emitIRFunc(myFunc);
  
  // 关闭 builder 的 irout 文件输出流
  builder.close();
}
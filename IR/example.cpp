#include "../include/IR/Function.h"
#include "../include/IR/Inst.h"
#include "../include/IR/Module.h"
#include "../include/IR/IRBuilder.h"
#include "../include/IR/Type.h"
#include "../include/Config.h"

USING_GIMC_NAMESPACE

GIMC_NAMESPACE_BEGIN
// 全局库函数（贯穿所有 example）
std::vector<baseTypePtr> putch_arguTypes;
std::vector<baseTypePtr> putint_arguTypes;
Function *putch;
Function *putint;
Function *getch;
Function *getint;

// 每个 example 必须包含
Function *myFunc;                               // main 函数
BBlock *entry;                                  // main 中首个基本块 entry
std::vector<Function*> *defs;                          // 函数定义容器
std::vector<Function*> *declares;                      // 函数声明容器
std::vector<GlobalVar*> *globals;                      // 全局变量容器

Module* initialize(IRBuilder &builder) {
  putch = builder.createFunction("putch", voidTyPtr, putch_arguTypes);
  putint = builder.createFunction("putint", voidTyPtr, putint_arguTypes);
  getch = builder.createFunction("getch", i32TyPtr, Zero_Argu_Type_List);
  getint = builder.createFunction("getint", i32TyPtr, Zero_Argu_Type_List);              // getint 为零参函数，使用全局零参空向量，见 Config.cpp
  putch_arguTypes.push_back(i32TyPtr);
  putint_arguTypes.push_back(i32TyPtr);  

  // 初始化一个 Module
  return new Module("start", voidTyPtr);
}

void addLib() {
  // 加入库函数
  declares->push_back(getch);
  declares->push_back(getint);
  declares->push_back(putch);
  declares->push_back(putint);

  // Module 中加入 main
  defs->push_back(myFunc);
}

void newModule(IRBuilder &builder, Module *module) {
  // ps:为什么不选择 new 一个 Module，因为想错了把 clear 做了，不用可惜了 q_q
  /**
   * 完全可以用以下方式平替
   * Module *module = new Module("example" + cnt, voidTyPtr, globals, defs, declares); 
   */
  static int cnt = 1;
  module->setValueName("example" + std::to_string(cnt));
  cnt++;
  module->clearModule();
  // 创建零参函数 "main"，返回类型为 i32
  myFunc = builder.createFunction("main", i32TyPtr, Zero_Argu_Type_List);
  globals = module->getGlobalVars();
  declares = module->getFuncDeclares();
  defs = module->getFuncDefs();

  // 创建基本块 entry
  entry = builder.createBBlock("entry", voidTyPtr);

  // 加入库函数
  addLib();
}

GIMC_NAMESPACE_END

int main(int argc, char** args) {
  // 创建 IR 构造器对象
  IRBuilder builder;
  if (argc == 2) {
    builder = IRBuilder(args[1], nullptr, nullptr);
  }

  // 初始化并获得 Module
  Module *myModule = initialize(builder);

  // eg.1 创建一些指令实现如下代码
  /**
   * int main() {
   *    return 1 + (-2) * (3/(4-5))   // return 7
   * }
  */
  newModule(builder, myModule);
  Instruction* i1 = builder.createBinaryInst(InstKind::Sub, new ConstIntValue(4), new ConstIntValue(5));
  Instruction* i2 = builder.createBinaryInst(InstKind::Div, new ConstIntValue(3), i1);
  Instruction* i3 = builder.createBinaryInst(InstKind::Mul, new ConstIntValue(-2), i2);
  Instruction* i4 = builder.createBinaryInst(InstKind::Add, new ConstIntValue(1), i3);
  Instruction* ireturn = builder.createRetInst(i4);

  builder.emitIRModule(myModule);
  
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
        结果：2
  */
  newModule(builder, myModule);

  Instruction* i_2_1 = builder.createAllocaInst("Nqn7m1", i32TyPtr, 1);
  Instruction* i_2_2 = builder.createAllocaInst("yiersan", i32TyPtr, 1);
  Instruction* i_2_3 = builder.createAllocaInst("mAgIc_NuMbEr", i32TyPtr, 1);
  Instruction* i_2_4 = builder.createAllocaInst("a1a11a11", i32TyPtr, 1);
  Instruction* i_2_5 = builder.createAllocaInst("_CHAOS_TOKEN", i32TyPtr, 1);
  Instruction* i_2_6 = builder.createStoreInst(new ConstIntValue(8) ,i_2_1);        // Nqn7m1 = 010   8 进制
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
  Instruction* eg2_ret = builder.createRetInst(i_2_20);
  
  builder.emitIRModule(myModule);

  /**
   * eg.3 实现小写转大写（无鲁棒性）
   *  int  getint(), getch(), getarray(int a[]);
      void putint(int a), putch(int a), putarray(int n, int a[]);
      int main() {
          int a = getch(), b;
          b = getch();
          putch(a - 32);
          putch(b - 32);
          return 0;
      }
  */
  newModule(builder, myModule);

  Instruction *eg3_a_ptr = builder.createAllocaInst("a", i32TyPtr, 1);
  Instruction *eg3_b_ptr = builder.createAllocaInst("b", i32TyPtr, 1);
  Instruction *eg3_call1 = builder.createCallInst("call1", getch, Zero_Argu_List);
  Instruction *eg3_call2 = builder.createCallInst("call2", getch, Zero_Argu_List);
  builder.createStoreInst(eg3_call1, eg3_a_ptr);
  builder.createStoreInst(eg3_call2, eg3_b_ptr);
  Instruction *eg3_load_a = builder.createLoadInst(i32TyPtr, eg3_a_ptr);
  Instruction *eg3_load_b = builder.createLoadInst(i32TyPtr, eg3_b_ptr);
  Instruction *eg3_arg1 = builder.createBinaryInst(InstKind::Sub, eg3_load_a, new ConstIntValue(32));
  Instruction *eg3_arg2 = builder.createBinaryInst(InstKind::Sub, eg3_load_b, new ConstIntValue(32));
  std::vector<Value*> eg3_argus1;
  std::vector<Value*> eg3_argus2;
  eg3_argus1.push_back(eg3_arg1);
  eg3_argus2.push_back(eg3_arg2);
  builder.createCallInst("call3", putch, eg3_argus1);
  builder.createCallInst("call4", putch, eg3_argus2);
  builder.createRetInst(new ConstIntValue(0));
 
    // 由 IRBuilder 发射 LLVM 代码
  builder.emitIRModule(myModule);


  /**
   * eg.4 实现 if 分支
   * @note return a <= b;
   * int main() {
    int a = getint();
    int b = getint();
    if (a <= b) {
        putint(1);
    }
    else {
        putint(0);
    }
    return 0;
    }
  */
  newModule(builder, myModule);

  Instruction *eg4_call1 = builder.createCallInst("call1", getint, Zero_Argu_List);
  Instruction *eg4_call2 = builder.createCallInst("call2", getint, Zero_Argu_List);
  Instruction *eg4_cmp = builder.createIcmpInst("icmp", CondKind::Sle, eg4_call1, eg4_call2);
  // 首先为 entry BBlock 新建两个后继 BBlock if_true,if_false，以及最终汇合 BBlock if_end
  BBlock *eg4_if_end = builder.createBBlock("eg4_if_end", voidTyPtr);
  Instruction *eg4_ret = builder.createRetInst(new ConstIntValue(0));

  BBlock *eg4_if_true = builder.createBBlock("eg4_if_true", voidTyPtr);
  std::vector<Value*> eg4_argus_0;
  std::vector<Value*> eg4_argus_1;
  eg4_argus_0.push_back(new ConstIntValue(0));
  eg4_argus_1.push_back(new ConstIntValue(1));
  Instruction *eg4_call_ifTrue = builder.createCallInst(putint, eg4_argus_1); 
  Instruction *eg4_true_br = builder.createBrInst(nullptr, eg4_if_end, nullptr);

  BBlock *eg4_if_false = builder.createBBlock("eg4_if_false", voidTyPtr);
  Instruction *eg4_call_ifFalse = builder.createCallInst(putint, eg4_argus_0); 
  Instruction *eg4_false_br = builder.createBrInst(nullptr, eg4_if_end, nullptr);
  // 将需要加入 Inst 的 BBlock 设为 entry
  builder.setChosedBBlock(entry);
  Instruction *eg4_br = builder.createBrInst(eg4_cmp, eg4_if_true, eg4_if_false);

  // 由 IRBuilder 发射 LLVM 代码
  builder.emitIRModule(myModule);

  /**
   * eg.5 支持全局变量
   * @note print(b + 5)
   *  int a = 5;
      int h;
      int main() {
          int b = getint();
          putint(a + b);
          return 0;
      }
  */
  newModule(builder, myModule);

  GlobalVar *eg5_a = builder.createGlobalVar<ConstValue*>("a", i32TyPtr, new ConstIntValue(5));
  // 注意 ptr 类型的数据需要先 load
  Instruction *eg5_load_a = builder.createLoadInst("load_a", eg5_a->getValueType(), eg5_a);
  GlobalVar *eg5_h = builder.createGlobalVar<ConstValue*>("h", i32TyPtr, new ConstIntValue(0));
  globals->push_back(eg5_a);
  globals->push_back(eg5_h);
  Value *eg5_b = builder.createCallInst("call1", getint, Zero_Argu_List);
  Value *eg5_add = builder.createBinaryInst(InstKind::Add, eg5_load_a, eg5_b);
  std::vector<Value*> eg5_args;
  eg5_args.push_back(eg5_add);
  builder.createCallInst(putint, eg5_args);
  builder.createRetInst(new ConstIntValue(0));
  
  // 由 IRBuilder 发射 LLVM 代码
  builder.emitIRModule(myModule);
  
  // 关闭 builder 的 irout 文件输出流
  builder.close();
}
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
std::vector<baseTypePtr> memset_arguTypes;
Function *putch;
Function *putint;
Function *getch;
Function *getint;
Function *memset;

// 每个 example 必须包含
Function *myFunc;                               // main 函数
BBlock *entry;                                  // main 中首个基本块 entry
std::vector<Function*> *defs;                          // 函数定义容器
std::vector<Function*> *declares;                      // 函数声明容器
std::vector<GlobalVar*> *globals;                      // 全局变量容器

Module* initialize(IRBuilder &builder) {
  putch = builder.createFunction("putch", voidType, putch_arguTypes);
  putint = builder.createFunction("putint", voidType, putint_arguTypes);
  getch = builder.createFunction("getch", i32Type, Zero_Argu_Type_List);
  getint = builder.createFunction("getint", i32Type, Zero_Argu_Type_List);              // getint 为零参函数，使用全局零参空向量，见 Config.cpp
  memset = builder.createFunction("myMemset", voidType, memset_arguTypes);
  putch_arguTypes.push_back(i32Type);
  putint_arguTypes.push_back(i32Type);
  memset_arguTypes.push_back(std::make_shared<PointerType>(i32Type));  
  memset_arguTypes.push_back(i32Type);  
  memset_arguTypes.push_back(i32Type);  

  // 初始化一个 Module
  return new Module("start", voidType);
}

void addLib() {
  // 加入库函数
  declares->push_back(getch);
  declares->push_back(getint);
  declares->push_back(putch);
  declares->push_back(putint);
  declares->push_back(memset);

  // Module 中加入 main
  defs->push_back(myFunc);
}

void newModule(IRBuilder &builder, Module *module) {
  // ps:为什么不选择 new 一个 Module，因为想错了把 clear 做了，不用可惜了 q_q
  /**
   * 完全可以用以下方式平替
   * Module *module = new Module("example" + cnt, voidType, globals, defs, declares); 
   */
  static int cnt = 1;
  module->setValueName("example" + std::to_string(cnt));
  cnt++;
  module->clearModule();
  // 创建零参函数 "main"，返回类型为 i32
  myFunc = builder.createFunction("main", i32Type, Zero_Argu_Type_List);
  globals = module->getGlobalVars();
  declares = module->getFuncDeclares();
  defs = module->getFuncDefs();

  // 创建基本块 entry
  entry = builder.createBBlock("entry", voidType);

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

  // alloca 
  Instruction* eg2_Nqn7m1_ptr = builder.createAllocaInst("Nqn7m1", int32PointerType);
  Instruction* eg2_yiersan_ptr = builder.createAllocaInst("yiersan", int32PointerType);
  Instruction* eg2_mAg_ptr = builder.createAllocaInst("mAgIc_NuMbEr", int32PointerType);
  Instruction* eg2_a1a11_ptr = builder.createAllocaInst("a1a11a11", int32PointerType);
  Instruction* eg2_chaos_ptr = builder.createAllocaInst("_CHAOS_TOKEN", int32PointerType);
  
  // store 初始化
  builder.createStoreInst(new ConstIntValue(8) ,eg2_Nqn7m1_ptr);        // Nqn7m1 = 010   8 进制
  builder.createStoreInst(new ConstIntValue(456), eg2_yiersan_ptr);
  builder.createStoreInst(new ConstIntValue(8456), eg2_mAg_ptr); 

  // 加载运算
  Instruction* eg2_mAg_1 = builder.createLoadInst(i32Type, eg2_mAg_ptr);                     // mAgIc_NuMbEr load
  Instruction* eg2_yiersan_1 = builder.createLoadInst(i32Type, eg2_yiersan_ptr);                    // yiersan load
  Instruction* eg2_sub_1 = builder.createBinaryInst(InstKind::Sub, eg2_mAg_1, eg2_yiersan_1);
  Instruction* eg2_div_1 = builder.createBinaryInst(InstKind::Div, eg2_sub_1, new ConstIntValue(1000));
  Instruction* eg2_sub_2 = builder.createBinaryInst(InstKind::Sub, eg2_div_1, new ConstIntValue(8));         // 常数折叠
  builder.createStoreInst(eg2_sub_2, eg2_a1a11_ptr);
  builder.createStoreInst(new ConstIntValue(2), eg2_chaos_ptr);
  Instruction* eg2_a1a11_1 = builder.createLoadInst(eg2_a1a11_ptr->getType(), eg2_a1a11_ptr);            // 这里 Load Instruction 的 Type 同样为指针基类 type
  Instruction* eg2_chaos_1 = builder.createLoadInst(eg2_chaos_ptr->getType(), eg2_chaos_ptr);
  Instruction* eg2_add_1 = builder.createBinaryInst(InstKind::Add, eg2_a1a11_1, eg2_chaos_1);
  builder.createStoreInst(eg2_add_1, eg2_a1a11_ptr);                     // a1a11a11 = a1a11a11 + _CHAOS_TOKEN;
  Instruction* eg2_a1a11_2 = builder.createLoadInst(eg2_a1a11_ptr->getType(), eg2_a1a11_ptr);
  builder.createRetInst(eg2_a1a11_2);
  
  builder.emitIRModule(myModule);

  /**
   * eg.3 函数调用 
   * 实现小写转大写（无鲁棒性）
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

  Instruction *eg3_a_ptr = builder.createAllocaInst("a", int32PointerType);
  Instruction *eg3_b_ptr = builder.createAllocaInst("b", int32PointerType);
  Instruction *eg3_call1 = builder.createCallInst("call1", getch, Zero_Argu_List);
  Instruction *eg3_call2 = builder.createCallInst("call2", getch, Zero_Argu_List);
  builder.createStoreInst(eg3_call1, eg3_a_ptr);
  builder.createStoreInst(eg3_call2, eg3_b_ptr);
  Instruction *eg3_load_a = builder.createLoadInst(i32Type, eg3_a_ptr);
  Instruction *eg3_load_b = builder.createLoadInst(i32Type, eg3_b_ptr);
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
  BBlock *eg4_if_end = builder.createBBlock("eg4_if_end", voidType);
  Instruction *eg4_ret = builder.createRetInst(new ConstIntValue(0));

  BBlock *eg4_if_true = builder.createBBlock("eg4_if_true", voidType);
  std::vector<Value*> eg4_argus_0;
  std::vector<Value*> eg4_argus_1;
  eg4_argus_0.push_back(new ConstIntValue(0));
  eg4_argus_1.push_back(new ConstIntValue(1));
  Instruction *eg4_call_ifTrue = builder.createCallInst(putint, eg4_argus_1); 
  Instruction *eg4_true_br = builder.createBrInst(nullptr, eg4_if_end, nullptr);

  BBlock *eg4_if_false = builder.createBBlock("eg4_if_false", voidType);
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

  GlobalVar *eg5_a = builder.createGlobalVar<Value*>("a", int32PointerType, new ConstIntValue(5));
  // 注意 ptr 类型的数据需要先 load
  Instruction *eg5_load_a = builder.createLoadInst("load_a", eg5_a->getValueType(), eg5_a);
  GlobalVar *eg5_h = builder.createGlobalVar<Value*>("h", int32PointerType, new ConstIntValue(0));
  globals->push_back(eg5_a);
  globals->push_back(eg5_h);
  Value *eg5_b = builder.createCallInst("call1", getint, Zero_Argu_List);
  Value *eg5_add = builder.createBinaryInst(InstKind::Add, eg5_load_a, eg5_b);
  std::vector<Value*> eg5_args;
  eg5_args.push_back(eg5_add);
  builder.createCallInst(putint, eg5_args);
  builder.createRetInst(new ConstIntValue(0));

  builder.emitIRModule(myModule);

  /**
   * eg.6 支持整型数组
   *  int a = 1;
      int b[2] = {1, a};
      int main() {
          putint(b[1]);
          int c[4][2] = {3,4};
          putint(c[0][1]);
          return 0;
      }
   */
  newModule(builder, myModule);
  // 对于非数组 Value 构建使用
  GlobalVar *eg6_a = builder.createGlobalVar<Value*>("a", int32PointerType, new ConstIntValue(1));
  globals->push_back(eg6_a);
  
  // 对于数组的构建
  baseTypePtr eg6_ty_1 = std::make_shared<PointerType>(i32Type, 2);
  std::vector<Value*> eg6_init_b;
  eg6_init_b.push_back(new ConstIntValue(1));
  eg6_init_b.push_back(eg6_a);
  GlobalVar *eg6_b = builder.createGlobalVar<std::vector<Value*>>("b", eg6_ty_1, eg6_init_b);
  globals->push_back(eg6_b);
  
  // GEP 指令
  Instruction *eg6_gep_1 = builder.createGEPInst("b_1_ptr", eg6_b, 1);
  Instruction *eg6_b_1 = builder.createLoadInst("b_1", i32Type, eg6_gep_1);
  std::vector<Value*> eg6_argus;
  eg6_argus.push_back(eg6_b_1);
  builder.createCallInst(putint, eg6_argus);
  
  // 生成局部数组变量
  baseTypePtr eg6_ty_2 = std::make_shared<PointerType>(i32Type, 2);
  baseTypePtr eg6_ty_3 = std::make_shared<PointerType>(eg6_ty_2, 4);
  Instruction *eg6_c_ptr = builder.createAllocaInst(eg6_ty_3);
  Instruction *eg6_gep_2 = builder.createGEPInst("c_0_ptr", eg6_c_ptr, 0);
  Instruction *eg6_gep_3 = builder.createGEPInst("c_0_0_ptr", eg6_gep_2, 0);
  Instruction *eg6_gep_4 = builder.createGEPInst("c_0_1_ptr", eg6_gep_2, 1);
  builder.createStoreInst(new ConstIntValue(3), eg6_gep_3);
  builder.createStoreInst(new ConstIntValue(4), eg6_gep_4);
  // 调用 memset 函数
  Instruction *eg6_gep_5 = builder.createGEPInst("c_1_ptr", eg6_c_ptr, 1);
  std::vector<Value*> eg6_argus_1;
  eg6_argus_1.push_back(eg6_gep_5);
  eg6_argus_1.push_back(new ConstIntValue(0));
  eg6_argus_1.push_back(new ConstIntValue(3*2*4));
  builder.createCallInst(memset, eg6_argus_1);
  Instruction *eg6_c_0_1 = builder.createLoadInst("c_0_1", i32Type, eg6_gep_4);
  std::vector<Value*> eg6_argus_2;
  eg6_argus_2.push_back(eg6_c_0_1);
  builder.createCallInst(putint, eg6_argus_2);
  builder.createRetInst(new ConstIntValue(0));
  
  // 由 IRBuilder 发射 LLVM 代码
  builder.emitIRModule(myModule);
  
  // 关闭 builder 的 irout 文件输出流
  builder.close();
}
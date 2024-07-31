#include "../include/IR/Function.h"
#include "../include/IR/Inst.h"
#include "../include/IR/Module.h"
#include "../include/IR/IRBuilder.h"
#include "../include/IR/Type.h"
#include "../include/Config.h"
#include "../include/Pass/Pres_Succs_Calculate.h"
#include "../include/Pass/Domination.h"
#include "../include/Pass/Mem2reg.h"
#include "../include/Pass/PassManager.h"

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
Function *memset_;

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
  memset_ = builder.createFunction("myMemset", voidType, memset_arguTypes);
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
  declares->push_back(memset_);

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

  myFunc->setEntry(entry);

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
  Instruction *eg4_cmp = builder.createIcmpInst("icmp", ICondKind::Sle, eg4_call1, eg4_call2);
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
   * eg 4.1 前驱后继结点 PASS 检测，绘制 CFG
   */
  // Pres_Succs_Calculate::calculate_Func(myFunc);
#ifdef PRINT_CFG
  // 使用 graphviz 画 main 的数据流图
  // myFunc->drawCFG();
#endif

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
  Instruction *eg6_gep_1 = builder.createGEPInst("b_1_ptr", eg6_b, new ConstIntValue(1));
  Instruction *eg6_b_1 = builder.createLoadInst("b_1", i32Type, eg6_gep_1);
  std::vector<Value*> eg6_argus;
  eg6_argus.push_back(eg6_b_1);
  builder.createCallInst(putint, eg6_argus);
  
  // 生成局部数组变量
  baseTypePtr eg6_ty_2 = std::make_shared<PointerType>(i32Type, 2);
  baseTypePtr eg6_ty_3 = std::make_shared<PointerType>(eg6_ty_2, 4);
  Instruction *eg6_c_ptr = builder.createAllocaInst(eg6_ty_3);
  Instruction *eg6_gep_2 = builder.createGEPInst("c_0_ptr", eg6_c_ptr, new ConstIntValue(0));
  Instruction *eg6_gep_3 = builder.createGEPInst("c_0_0_ptr", eg6_gep_2, new ConstIntValue(0));
  Instruction *eg6_gep_4 = builder.createGEPInst("c_0_1_ptr", eg6_gep_2, new ConstIntValue(1));
  builder.createStoreInst(new ConstIntValue(3), eg6_gep_3);
  builder.createStoreInst(new ConstIntValue(4), eg6_gep_4);
  // 调用 memset 函数
  Instruction *eg6_gep_5 = builder.createGEPInst("c_1_ptr", eg6_c_ptr, new ConstIntValue(1));
  std::vector<Value*> eg6_argus_1;
  eg6_argus_1.push_back(eg6_gep_5);
  eg6_argus_1.push_back(new ConstIntValue(0));
  eg6_argus_1.push_back(new ConstIntValue(2*4));
  builder.createCallInst(memset_, eg6_argus_1);
  Instruction *eg6_c_0_1 = builder.createLoadInst("c_0_1", i32Type, eg6_gep_4);
  std::vector<Value*> eg6_argus_2;
  eg6_argus_2.push_back(eg6_c_0_1);
  builder.createCallInst(putint, eg6_argus_2);
  builder.createRetInst(new ConstIntValue(0));
  
  // 由 IRBuilder 发射 LLVM 代码
  builder.emitIRModule(myModule);

  /**
   * eg.7. 支持浮点数运算与整数浮点数转换
   * int main() {
          float x = 1.2, y = 3.62;
          int z = 2;
          x = ((float)z + y/(x-2)) * 6;
          return x;
      }
      结果 241
   */
  newModule(builder, myModule);
  //  初始化变量
  Instruction *eg7_x_ptr = builder.createAllocaInst(floatPointerType);
  Instruction *eg7_y_ptr = builder.createAllocaInst(floatPointerType);
  Instruction *eg7_z_ptr = builder.createAllocaInst(int32PointerType);
  builder.createStoreInst(new ConstFloatValue(1.2f), eg7_x_ptr);
  builder.createStoreInst(new ConstFloatValue(3.62f), eg7_y_ptr);
  builder.createStoreInst(new ConstIntValue(2), eg7_z_ptr);
  // signed int 2 fp
  Instruction *eg7_load_z = builder.createLoadInst("z1", i32Type, eg7_z_ptr);
  Instruction *eg7_i2fp_z = builder.createInt2FpInst("i2fp", eg7_load_z);
  // 浮点数加减乘除
  Instruction *eg7_load_y = builder.createLoadInst("y1", floatType, eg7_y_ptr);
  Instruction *eg7_load_x = builder.createLoadInst("x1", floatType, eg7_x_ptr);
  Instruction *eg7_sub = builder.createBinaryInst(InstKind::Subf, eg7_load_x, new ConstFloatValue(2.0));
  Instruction *eg7_div = builder.createBinaryInst(InstKind::Divf, eg7_load_y, eg7_sub);
  Instruction *eg7_add = builder.createBinaryInst(InstKind::Addf, eg7_i2fp_z, eg7_div);
  Instruction *eg7_mul = builder.createBinaryInst(InstKind::Mulf, eg7_add, new ConstFloatValue(6.0));
  // fp 2 signed int
  builder.createStoreInst(eg7_mul, eg7_x_ptr);
  Instruction *eg7_load_x2 = builder.createLoadInst(floatType, eg7_x_ptr);
  Instruction *eg7_fp2i_x = builder.createFp2IntInst("fp2i", eg7_load_x2);
  builder.createRetInst(eg7_fp2i_x);

  builder.emitIRModule(myModule);

  /**
   * eg.8. 支持浮点数比较与整数求余操作
   * int main() {
   *  float x = 0.2;
   *  int m = 2;
   *  return x > (m % 2);
   * }
   * // 返回 1
   */
  newModule(builder, myModule);
  // 初始化变量
  Instruction *eg8_x_ptr = builder.createAllocaInst(floatPointerType);
  Instruction *eg8_m_ptr = builder.createAllocaInst(int32PointerType);
  builder.createStoreInst(new ConstFloatValue(0.2f), eg8_x_ptr);
  builder.createStoreInst(new ConstIntValue(2), eg8_m_ptr);
  // 计算 m % 2
  Instruction *eg8_load_m = builder.createLoadInst("load_m", i32Type, eg8_m_ptr);
  Instruction *eg8_m_rem_2 = builder.createBinaryInst(InstKind::SRem, eg8_load_m, new ConstIntValue(2));
  // 注意 float 与 int 相比较会隐式地将 int 强转为 float
  Instruction *eg8_i2fp_rem = builder.createInt2FpInst("i2fp", eg8_m_rem_2);
  Instruction *eg8_load_x = builder.createLoadInst(floatType, eg8_x_ptr);
  Instruction *eg8_fcmp = builder.createFcmpInst("fcmp", FCondKind::Ogt, eg8_load_x, eg8_i2fp_rem);
  // 注意 icmp 与 fcmp 均是 bool 类型，需要零拓展至 i32
  Instruction *eg8_zext = builder.createZextInst("zext", i32Type, eg8_fcmp);
  builder.createRetInst(eg8_zext);

  builder.emitIRModule(myModule);

  /**
   * eg.9. 支配树算法测试
   */
  newModule(builder, myModule);
  std::unordered_map<char, BBlock*> eg_9_nodes;
  for (char tmp = 'A'; tmp <= 'L'; tmp++) {
    BBlock *bBlk = builder.createBBlock(std::string(1, tmp), voidType);
    eg_9_nodes[tmp] = bBlk;
  }
  BBlock *eg_9_r = builder.createBBlock("R", voidType);
  myFunc->setEntry(eg_9_r);

  BBlock::addEdge(eg_9_r, eg_9_nodes['A']);
  BBlock::addEdge(eg_9_r, eg_9_nodes['B']);
  BBlock::addEdge(eg_9_r, eg_9_nodes['C']);
  BBlock::addEdge(eg_9_nodes['A'], eg_9_nodes['D']);
  BBlock::addEdge(eg_9_nodes['B'], eg_9_nodes['E']);
  BBlock::addEdge(eg_9_nodes['B'], eg_9_nodes['A']);
  BBlock::addEdge(eg_9_nodes['B'], eg_9_nodes['D']);
  BBlock::addEdge(eg_9_nodes['C'], eg_9_nodes['F']);
  BBlock::addEdge(eg_9_nodes['C'], eg_9_nodes['G']);
  BBlock::addEdge(eg_9_nodes['D'], eg_9_nodes['L']);
  BBlock::addEdge(eg_9_nodes['E'], eg_9_nodes['H']);
  BBlock::addEdge(eg_9_nodes['F'], eg_9_nodes['I']);
  BBlock::addEdge(eg_9_nodes['G'], eg_9_nodes['I']);
  BBlock::addEdge(eg_9_nodes['G'], eg_9_nodes['J']);
  BBlock::addEdge(eg_9_nodes['H'], eg_9_nodes['E']);
  BBlock::addEdge(eg_9_nodes['H'], eg_9_nodes['K']);
  BBlock::addEdge(eg_9_nodes['I'], eg_9_nodes['K']);
  BBlock::addEdge(eg_9_nodes['J'], eg_9_nodes['I']);
  BBlock::addEdge(eg_9_nodes['K'], eg_9_nodes['I']);
  BBlock::addEdge(eg_9_nodes['K'], eg_9_r);
  BBlock::addEdge(eg_9_nodes['L'], eg_9_nodes['H']);

#ifdef PRINT_CFG
  // 使用 graphviz 画 main 的数据流图
  myFunc->drawCFG();
#endif
  Domination eg9_dom;
  eg9_dom.initialize(myFunc);
  eg9_dom.calculate();

  /**
   * eg.10. 支持 phi 指令
      int main() {
        int x, cond = 1;
        if (cond > 0)
            x = 1;
        else
            x = -1;
        return x;
      }
   */
  newModule(builder, myModule);
  Instruction *eg_10_x_ptr =  builder.createAllocaInst("x", int32PointerType);
  Instruction *eg_10_cond_ptr =  builder.createAllocaInst("cond", int32PointerType);
  builder.createStoreInst(new ConstIntValue(1), eg_10_cond_ptr);
  Instruction *eg_10_load_cond = builder.createLoadInst("load_cond", i32Type, eg_10_cond_ptr);
  Instruction *eg_10_cmp = builder.createIcmpInst(ICondKind::Sgt, eg_10_load_cond, new ConstIntValue(0));
  BBlock *eg_10_if_then = builder.createBBlock("if_then", voidType);
  BBlock *eg_10_if_else = builder.createBBlock("if_else", voidType);
  BBlock *eg_10_if_end = builder.createBBlock("if_end", voidType);
  builder.setChosedBBlock(entry);
  Instruction *eg_10_entry_br = builder.createBrInst(eg_10_cmp, eg_10_if_then, eg_10_if_else);
  builder.setChosedBBlock(eg_10_if_then);
  builder.createStoreInst(new ConstIntValue(1), eg_10_x_ptr);
  builder.createBrInst(nullptr, eg_10_if_end, nullptr);
  builder.setChosedBBlock(eg_10_if_else);
  builder.createStoreInst(new ConstIntValue(-1), eg_10_x_ptr);
  builder.createBrInst(nullptr, eg_10_if_end, nullptr);
  builder.setChosedBBlock(eg_10_if_end);
  Instruction *eg_10_load_x = builder.createLoadInst(i32Type, eg_10_x_ptr);
  builder.createRetInst(eg_10_load_x);

  PassManager eg_10_pm(myFunc);
  eg_10_pm.mem2reg();

  builder.emitIRModule(myModule);



  /**
   * eg.11. 支持函数形参调用，&& 和 || 的控制流程
   * 
   * int foo(float x, int y, int z) {
   *  return !x && y || z;
   * }
   * 
   * int main() {
   *  return foo(2, 0, 3);
   * }
   * 结果 true
   */
  newModule(builder, myModule);
  std::vector<baseTypePtr> eg_11_foo_argu_ty;
  eg_11_foo_argu_ty.push_back(floatType);
  eg_11_foo_argu_ty.push_back(i32Type);
  eg_11_foo_argu_ty.push_back(i32Type);
  Function *eg_11_foo = builder.createFunction("foo", i32Type, eg_11_foo_argu_ty);
  BBlock *eg_11_foo_entry = builder.createBBlock("entry", voidType, eg_11_foo);
  eg_11_foo->setEntry(eg_11_foo_entry);       // 将 BBlock 加入其中
  // 获取函数形参作为变量，注意作为变量规范做法则需要 load store
  std::vector<Value> &eg_11_foo_argus = eg_11_foo->getArgus();
  Instruction *eg_11_x_ptr = builder.createAllocaInst("x_ptr", floatPointerType);
  Instruction *eg_11_y_ptr = builder.createAllocaInst("y_ptr", floatPointerType);
  Instruction *eg_11_z_ptr = builder.createAllocaInst("z_ptr", floatPointerType);
    // 注意此时因为是 Value* 指针所以要用取址符  
  builder.createStoreInst(&eg_11_foo_argus[0], eg_11_x_ptr);
  builder.createStoreInst(&eg_11_foo_argus[1], eg_11_y_ptr);
  builder.createStoreInst(&eg_11_foo_argus[2], eg_11_z_ptr);
  // 对于整个表达式构建两个基本块 true,false
  BBlock *eg_11_false = builder.createBBlock("false", voidType, eg_11_foo);
  BBlock *eg_11_true = builder.createBBlock("true", voidType, eg_11_foo);
  // 针对 || 构建 1 个额外基本块（二叉树中 || 为根结点）
  BBlock *eg_11_or_A1p_false = builder.createBBlock("or_a1p_false", voidType, eg_11_foo);
  // 针对 && 构建 1 个 额外基本块
  BBlock *eg_11_and_A1_true = builder.createBBlock("and_a1_true", voidType, eg_11_foo);
    // 在 entry 基本块计算 && 的 A1（左侧表达式），并条件跳转到 a1_true 或 ||_A1_false（即 || 的第一个表达式为 false）
  Instruction *eg_11_x_load = builder.createLoadInst(floatType, eg_11_x_ptr, eg_11_foo_entry);
  Instruction *eg_11_fcmp = builder.createFcmpInst(FCondKind::One, new ConstFloatValue(0), eg_11_x_load, eg_11_foo_entry);
  Instruction *eg_11_and_a1_br = builder.createBrInst(eg_11_fcmp, eg_11_and_A1_true, eg_11_or_A1p_false, eg_11_foo_entry);
    // 在 &&_A1_true 基本块计算 && 的 A2（右侧表达式），并条件跳转到 true 或 ||_A1_false
  Instruction *eg_11_y_load = builder.createLoadInst(i32Type, eg_11_y_ptr, eg_11_and_A1_true);
  Instruction *eg_11_icmp_y = builder.createIcmpInst(ICondKind::Eq, new ConstIntValue(0), eg_11_y_load, eg_11_and_A1_true);
  Instruction *eg_11_and_a2_br = builder.createBrInst(eg_11_icmp_y, eg_11_true, eg_11_or_A1p_false, eg_11_and_A1_true);
    //  在 ||_A1'_false 基本块计算 || 的 A2'，条件跳转到 true 或 false
  Instruction *eg_11_z_load = builder.createLoadInst(i32Type, eg_11_z_ptr, eg_11_or_A1p_false);
  Instruction *eg_11_icmp_z = builder.createIcmpInst(ICondKind::Eq, new ConstIntValue(0), eg_11_z_load, eg_11_or_A1p_false);
  Instruction *eg_11_or_a2p_br = builder.createBrInst(eg_11_icmp_z, eg_11_true, eg_11_false, eg_11_or_A1p_false);
  // 在 true 和 false 中设置两种 return 值的设置。（llvm 会隐式分配局部变量 %return），在 true 和 false 中分别给两个附上不同值。
  // true 和 false 基本块会回流到一起，即 if() {xxx;} else {yyy;} zzz; 中 zzz 的部分。
  BBlock *eg_11_end = builder.createBBlock("end", voidType, eg_11_foo);
  Instruction *eg_11_br_true = builder.createBrInst(nullptr, eg_11_end, nullptr, eg_11_true);
  Instruction *eg_11_br_false = builder.createBrInst(nullptr, eg_11_end, nullptr, eg_11_false);
  // 这里使用 phi 指令，从那个基本块流过来就用谁的值。
  std::vector<Value*> tmps;
  Value *eg_11_tmp = new Value("tmp", int32PointerType);      // 这里需要有一个类型为 i32* 的 Value 作为 phi 指令的占位符，phi 指令的数据类型取决于
  tmps.push_back(eg_11_tmp);
  tmps.push_back(new ConstIntValue(1));         // 一个值对应一个基本块，先存入 Value* 后存入 BBlock*
  tmps.push_back(eg_11_true);
  tmps.push_back(new ConstIntValue(0));
  tmps.push_back(eg_11_false);
  Instruction *eg_11_phi = builder.createPhiInst("phi", i32Type, tmps, eg_11_end);
  builder.createRetInst(eg_11_phi);
  defs->push_back(eg_11_foo);   // 将函数加入定义中
  builder.setChosedFunc(myFunc);
  builder.setChosedBBlock(entry);
  std::vector<Value*> eg_11_call_argus;
  eg_11_call_argus.push_back(new ConstFloatValue(2));
  eg_11_call_argus.push_back(new ConstIntValue(0));
  eg_11_call_argus.push_back(new ConstIntValue(3));
  Instruction *eg_11_call = builder.createCallInst(eg_11_foo, eg_11_call_argus);
  builder.createRetInst(eg_11_call);

  builder.emitIRModule(myModule);

  /**
   * eg.12. 支持 void 返回值
   * void f(int a) {
      putint(a);
      return;
    }
    int main() {
      f(getint());
    }
   */
  newModule(builder, myModule);
  std::vector<baseTypePtr> eg_12_f_ty;
  eg_12_f_ty.push_back(i32Type);
  Function *eg_12_f = builder.createFunction("f", voidType, eg_12_f_ty);
  BBlock *eg_12_f_entry = builder.createBBlock("entry", voidType, eg_12_f);
  eg_12_f->setEntry(eg_12_f_entry);       // 将 BBlock 加入其中
  builder.setChosedBBlock(eg_12_f_entry);
  std::vector<Value> eg_12_params = eg_12_f->getArgus();
  Instruction *eg_12_a_ptr = builder.createAllocaInst("a_ptr", int32PointerType);
  builder.createStoreInst(&eg_12_params[0], eg_12_a_ptr);
  Instruction *eg_12_load = builder.createLoadInst("a", i32Type, eg_12_a_ptr);
  // 调用 putint
  std::vector<Value*> eg_12_putint_argus;
  eg_12_putint_argus.push_back(eg_12_load);
  Instruction *eg_12_call = builder.createCallInst(putint, eg_12_putint_argus);
  builder.createRetInst(&voidValue);
  // 记得加入 module 的 defs
  defs->push_back(eg_12_f);

  // 构建 main 
  builder.setChosedFunc(myFunc);
  builder.setChosedBBlock(entry);

  Instruction *eg_12_call_1 = builder.createCallInst(getint, Zero_Argu_List);
  std::vector<Value*> eg_12_f_argus;
  eg_12_f_argus.push_back(eg_12_call_1);
  Instruction *eg_12_call_2 = builder.createCallInst(eg_12_f, eg_12_f_argus);
  builder.createRetInst(new ConstIntValue(0));
  
  builder.emitIRModule(myModule);

  // 关闭 builder 的 irout 文件输出流
  builder.close();
}
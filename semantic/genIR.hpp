#include "../include/AST.hpp"
#include "../include/IR/IRBuilder.h"
#include "../include/SymbolTable.hpp"

extern std::vector<Function*> *defs;                          // 函数定义容器
extern std::vector<Function*> *declares;                      // 函数声明容器
extern std::vector<GlobalVar*> *globals;                      // 全局变量容器
extern SymbolTable sym_tb;
extern string error_msg;
extern IRBuilder builder;
extern Module* module;

NumberPtr getConstExpValue(ExpPtr exp, bool array_dim = false);
CompUnit* parse(char *filename);
Module* initialize(IRBuilder &builder);
void parseCompUnit(CompUnitPtr rt);
void parseDecl(DeclPtr decl, bool is_global = false);
void parseAssign(AssignStmtPtr stmt);
void parseIfElse(IfElseStmtPtr stmt, BBlock* loop_st = nullptr, BBlock* loop_ed = nullptr);
void parseWhile(WhileStmtPtr stmt);
void parseReturn(ReturnStmtPtr stmt);
void parseBreak(StmtPtr stmt, BBlock* bBlock);
void parseContinue(StmtPtr stmt, BBlock* bBlock);
void parseBlock(BlockPtr block, vector<VarNode *> *va_list = nullptr, BBlock* loop_st = nullptr, BBlock* loop_ed = nullptr);
pair<Value*,bool> parseExp(ExpPtr exp, bool is_cond, bool is_exp, bool is_func_param, BBlock* cond_true=nullptr, BBlock* cond_false=nullptr);
void parseArrayInitVal(ArrayInitValPtr arr_init, vector<int> &pos, vector<int> dims, int depth, int limit, Instruction* array_base, bool is_float, bool is_const=false);
void parseArrayInitVal(ArrayInitValPtr arr_init, vector<int> &pos, vector<int> dims, int depth, int limit, bool is_float, map<vector<int>, NumberPtr>& arr_val_mp);
void genIRModule(char *filename);

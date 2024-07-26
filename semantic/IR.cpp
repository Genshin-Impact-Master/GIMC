#include "../include/IR/IRBuilder.h"
#include "../include/SymbolTable.hpp"
#include "genIR.hpp"
#include "errors.hpp"

// 每个 example 必须包含
Function *myFunc;                               // main 函数
BBlock *entry;                                  // main 中首个基本块 entry
std::vector<Function*> *defs;                          // 函数定义容器
std::vector<Function*> *declares;                      // 函数声明容器
std::vector<GlobalVar*> *globals;                      // 全局变量容器
SymbolTable sym_tb = SymbolTable();
string error_msg = "";

IRBuilder builder;
Module* module;

void error_handle(){
    cout << error_msg << endl;
    exit(0);
}


// 解析函数调用
Instruction* parseFuncCall(ExpPtr exp){
    auto func_call_exp = dynamic_pointer_cast<FuncCall>(exp);
    // 函数不存在
    if (! sym_tb.check_func(func_call_exp -> getIdentifier())){
        error_msg = "function " + func_call_exp -> getIdentifier() + " not defined";
        error_handle();
    }
    auto func_node = sym_tb.find_func(func_call_exp -> getIdentifier());
    auto R_param = func_call_exp -> getArgs();
    auto F_param = func_node -> _func_params -> getFuncFParam();
    if (R_param.size() != F_param.size()){
        error_msg = "function " + func_call_exp -> getIdentifier() + " expects " + std::to_string(F_param.size()) + " arguments, but " + std::to_string(R_param.size()) + " given";
        error_handle();
    }
    // 函数参数为空
    if (F_param.size() == 0) return builder.createCallInst(func_node -> _entry, Zero_Argu_List);

    // 函数参数不为空
    vector<Value*> args;
    for (int i = 0; i < R_param.size(); i++){
        auto R_param_i = R_param[i];
        auto F_param_i = F_param[i];
        auto arg_exp = parseExp(R_param_i, false);
        if (R_param_i -> getType() != F_param_i -> getType()){
            error_msg = "function " + func_call_exp -> getIdentifier() + " expects " + std::to_string(F_param.size()) + " arguments, but " + std::to_string(R_param.size()) + " given";
            error_handle();
        }
        args.push_back(arg_exp.first);
    }
    return builder.createCallInst(func_node -> _entry, args);
}

// 返回表达式IR、是否为常量表达式、是否合法
pair<Value*,bool> parseExp(ExpPtr exp, bool is_cond){
    switch (exp -> getType()){
        case ExpType::ET_INT :{
            exp -> addResType (BaseType::B_INT);
            auto tmp = dynamic_pointer_cast<Number>(exp);
            return pair<Value*,bool>(new ConstIntValue(tmp -> getIntVal()), true);
        }

        case ExpType::ET_FLOAT :{
            exp -> addResType (BaseType::B_FLOAT);
            auto tmp = dynamic_pointer_cast<Number>(exp);
            return pair<Value*,bool>(new ConstFloatValue(tmp -> getFloatVal()), true);
        }

        case ExpType::ET_FUNC :{
            // 函数调用先检查是否存在该函数
            auto tmp = dynamic_pointer_cast<FuncCall>(exp);
            // 函数不存在
            if (! sym_tb.check_func(tmp -> getIdentifier())){
                error_msg = "function " + tmp -> getIdentifier() + " not defined";
                error_handle();
            }
            // 函数存在但返回值是void
            else if (sym_tb.find_func(tmp -> getIdentifier()) -> _ret_type == BaseType::B_VOID){
                error_msg = "function " + tmp -> getIdentifier() + " returns void";
                error_handle();
            }
            // 函数存在且返回值不是void
            else{
                exp -> addResType(sym_tb.find_func(tmp -> getIdentifier()) -> _ret_type);
                return pair<Value*,bool>(parseFuncCall(exp), false);
            }
        }
        case ExpType::ET_LVAL: {
            auto tmp = dynamic_pointer_cast<LVal>(exp);
            // 变量不存在
            if (!sym_tb.check_var(tmp -> getIdentifier())){
                error_msg = "variable " + tmp -> getIdentifier() + " not defined";
                error_handle();
            }
            auto var_node = sym_tb.find_var(tmp -> getIdentifier());
            exp -> addResType(var_node -> _type);
            // 变量是数组
            if (var_node->_is_array){
                // 是否取到了数
                if (tmp -> getDims().size() != var_node->_dims.size()){
                    error_msg = "array " + tmp -> getIdentifier() + " expects " + std::to_string(var_node->_dims.size()) + " dimensions, but " + std::to_string(tmp -> getDims().size()) + " given";
                    error_handle();
                }
                return pair<Value*,bool>(parseArrayLval(tmp, var_node), false);
            }
            // 变量不是数组
            else {
                if 
            }
        }
        case ExpType::ET_BIN :{
            auto tmp = dynamic_pointer_cast<BinaryExp>(exp);
            auto left = parseExp(tmp -> getExp1(), is_cond);
            auto right = parseExp(tmp -> getExp2(), is_cond);
            // 是否含有浮点数
            bool is_float = tmp -> getExp1() -> getResType() == BaseType::B_FLOAT && tmp -> getExp2() -> getResType() == BaseType::B_FLOAT;
            exp -> addResType(is_float ? BaseType::B_FLOAT : BaseType::B_INT);
            // 类型提升
            if (is_float) {
                if (tmp -> getExp1() -> getResType() == BaseType::B_INT) {
                    left.first = builder.createInt2FpInst(left.first);
                }
                if (tmp -> getExp2() -> getResType() == BaseType::B_INT) {
                    right.first = builder.createInt2FpInst(right.first);
                }
            }

            // 检查是否是浮点数取模操作 
            if (tmp -> getOp() == BinOpType::OP_MOD && is_float){
                error_msg = "float modulo is not supported";
                error_handle();
            }
            switch (tmp -> getOp()){
                case BinOpType::OP_ADD :{
                    if (is_float) return pair<Value*, bool>(builder.createBinaryInst(InstKind::Addf, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createBinaryInst(InstKind::Add, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_SUB :{
                    if (is_float) return pair<Value*, bool>(builder.createBinaryInst(InstKind::Subf, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createBinaryInst(InstKind::Sub, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_MUL :{
                    if (is_float) return pair<Value*, bool>(builder.createBinaryInst(InstKind::Mulf, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createBinaryInst(InstKind::Mul, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_DIV :{
                    if (is_float) return pair<Value*, bool>(builder.createBinaryInst(InstKind::Divf, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createBinaryInst(InstKind::Div, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_MOD :{
                    return pair<Value*, bool>(builder.createBinaryInst(InstKind::SRem, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_GTE :{
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    if (is_float) return pair<Value*, bool>(builder.createFcmpInst(FCondKind::Oge, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createIcmpInst(ICondKind::Sge, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_EQ :{
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    if (is_float) return pair<Value*, bool>(builder.createFcmpInst(FCondKind::Oeq, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createIcmpInst(ICondKind::Eq, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_NEQ :{
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    if (is_float) return pair<Value*, bool>(builder.createFcmpInst(FCondKind::One, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createIcmpInst(ICondKind::Ne, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_GT: {
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    if (is_float) return pair<Value*, bool>(builder.createFcmpInst(FCondKind::Ogt, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createIcmpInst(ICondKind::Sgt, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_LT: {
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    if (is_float) return pair<Value*, bool>(builder.createFcmpInst(FCondKind::Olt, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createIcmpInst(ICondKind::Slt, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_LTE: {
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    if (is_float) return pair<Value*, bool>(builder.createFcmpInst(FCondKind::Ole, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createIcmpInst(ICondKind::Sle, left.first, right.first), left.second && right.second);
                }
                default: {
                    error_msg = "unsupported binary operator";
                    error_handle();
                }   
            }
        }
    }
}


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

Instruction* parseExp(ExpPtr exp){
    get_exp_ret_type(exp);
    switch (exp -> getType()) {
        case ExpType::ET_BIN: {
            auto bin_exp = dynamic_pointer_cast<BinaryExp>(exp);
            auto op = bin_exp -> getOp();
            if (op == BinOpType::OP_ADD) return builder.createBinaryInst(InstKind::Add, parseExp(bin_exp -> getExp1()), parseExp(bin_exp -> getExp2()));
            else if (op == BinOpType::OP_AND) return builder.createBinaryInst();
            else if (op == BinOpType::OP_DIV) return builder.createBinaryInst(exp -> getResType() == BaseType::B_FLOAT? InstKind::Addf : InstKind::Add, parseExp(bin_exp -> getExp1()), parseExp(bin_exp -> getExp2()));
            else if ()
        }
    }
}


// 获取函数
void get_exp_ret_type(ExpPtr exp) {
    switch (exp -> getType()) {
        case ExpType::ET_BIN:{
            auto bin_exp = dynamic_pointer_cast<BinaryExp>(exp);
            get_exp_ret_type(bin_exp -> getExp1());
            get_exp_ret_type(bin_exp -> getExp1());
            bool float_exist = ((bin_exp -> getExp1() -> getResType() != BaseType::B_INT) || (bin_exp -> getExp1() -> getResType() != BaseType::B_INT));
            if (bin_exp -> getOp() == BinOpType::OP_MOD && float_exist) {
                error_msg = "mod error";
                error_handle();
            }
            else if (bin_exp -> getOp() ==)
            return;
        }
        case ExpType::ET_FLOAT: {
            exp -> addResType(BaseType::B_FLOAT);
            return;
        }
        case ExpType::ET_INT: {
            exp -> addResType(BaseType::B_INT);
            return;
        }
        case ExpType::ET_FUNC: {
            auto func_exp = dynamic_pointer_cast<FuncCall>(exp);
            FuncNode* func = sym_tb.find_func(func_exp -> getIdentifier());
            exp -> addResType(func -> _ret_type);
            return;
        }
        case ExpType::ET_LVAL: {
            auto lval_exp = dynamic_pointer_cast<LVal>(exp);
            VarNode* var = sym_tb.find_var(lval_exp -> getIdentifier());
            exp -> addResType(var -> _is_float ? BaseType::B_FLOAT : BaseType::B_INT);
            return;
        }
    }
}

// 检查表达式是否使用不存在的变量，函数，以及是否是常量表达式
bool exp_check(ExpPtr exp){
    switch (exp -> getType()){
        case ExpType::ET_BIN: {
            auto bin_exp = dynamic_pointer_cast<BinaryExp>(exp);
            return exp_check(bin_exp -> getExp1()) && exp_check(bin_exp -> getExp2());
        }
        case ExpType::ET_FLOAT : return true;
        case ExpType::ET_INT : return true;
        case ExpType::ET_FUNC: {
            auto func_exp = dynamic_pointer_cast<FuncCall>(exp);
            if (sym_tb.check_func(func_exp -> getIdentifier()) == false) {
                error_msg = func_exp -> getIdentifier() + func_undefine;
                error_handle();
            }
            return false;
        }
        case ExpType::ET_LVAL : {
            auto lval_exp = dynamic_pointer_cast<LVal>(exp);
            if (sym_tb.check_var(lval_exp -> getIdentifier()) == false) {
                error_msg = lval_exp -> getIdentifier() + var_undefine;
                error_handle();
            } else {
                VarNode* var = sym_tb.find_var(lval_exp -> getIdentifier());
                // TODO: 数组和变量重名
                return var -> _is_const;
            }
        }
    }  
    return false;
}

void parseGlobalDecl(DeclPtr decl) {
    if (decl -> isConst()) {
        auto tmp = decl -> getConstDecl();
        auto type = tmp -> getType() == BaseType::B_INT ? int32PointerType : floatPointerType;
        for (auto def: tmp -> getConstDef() -> getConstDef()){
            if (sym_tb.check_var_current_bk(def -> getIdentifier()) == true) {
                error_msg = def -> getIdentifier() + var_multidefine;
                error_handle();
            }
            if (def -> isArray()){

            } else {
                if (exp_check(def -> getInitVal() -> getExp()) == false) {
                    error_msg = def -> getIdentifier() + initialize_error;
                    error_handle();
                } else {
                    auto exp_inst = parseExp(def -> getInitVal() -> getExp());
                    GlobalVar* var = builder.createGlobalVar<Value*>(def -> getIdentifier(), type, exp_inst);
                    globals->push_back(var);
                    sym_tb.add_var(def -> getIdentifier(), tmp -> getType(), def -> isArray(), true, tmp -> getType() == BaseType::B_FLOAT, var);
                }
            }
        }
    } else {
        auto tmp = decl -> getVarDecl();
        auto type = tmp -> getType() == BaseType::B_INT ? int32PointerType : floatPointerType;
        for (auto def: tmp -> getVarDefs() -> getVarDef()){
            if (sym_tb.check_var_current_bk(def -> getIdentifier()) == true) {
                error_msg = def -> getIdentifier() + var_multidefine;
                error_handle();
            }
            if (def -> isArray()) {

            } else {
                if (def -> isInit()) {
                    exp_check(def ->getInitVal());
                    GlobalVar* var = builder.createGlobalVar<Value*>(def -> getIdentifier(), type, parseExp(def -> getInitVal()));
                    globals -> push_back(var);
                    sym_tb.add_var(def -> getIdentifier(), tmp -> getType(), def -> isArray(), false, tmp -> getType() == BaseType::B_FLOAT, var);
                }
                else {
                    GlobalVar* var;
                    if (type == int32PointerType) var = builder.createGlobalVar<Value*>(def -> getIdentifier(), type, new ConstIntValue(0));
                    else var = builder.createGlobalVar<Value*>(def -> getIdentifier(), type, new ConstFloatValue(0));
                    globals->push_back(var);
                    sym_tb.add_var(def -> getIdentifier(), tmp -> getType(), def -> isArray(), false, tmp -> getType() == BaseType::B_FLOAT, var);

                }
            }
        }
    }
}

void genIR(char* filename, string dump) {
    CompUnit* root = parse(filename);
    builder = IRBuilder(dump, nullptr, nullptr);
    module = new Module("start", voidType);
    vector<DeclPtr> global_decls = root->getDecl();
    for (DeclPtr decl : global_decls) {
        if (decl -> isConst()) {
            auto tmp = decl -> getConstDecl();
            auto type = tmp -> getType() == BaseType::B_INT ? int32PointerType : floatPointerType;
            for (auto def: tmp -> getConstDef()->getConstDef()){
                // Instruction* inst = builder.createAllocaInst(def -> getIdentifier(), type);
                // builder.createStoreInst(new ConstIntValue(parseExp(def-> getInitVal() ->getExp())->getIntVal()), inst);
                GlobalVar* var = builder.createGlobalVar<Value*>(def -> getIdentifier(), 
                                                                 type, 
                                                                 new ConstIntValue(parseExp(def-> getInitVal() ->getExp())->getIntVal()));
                globals -> push_back(var);
            }
        }
        else {
            auto tmp = decl -> getVarDecl();
            auto type = tmp -> getType() == BaseType::B_INT ? int32PointerType : floatPointerType;
            for (auto def: tmp -> getVarDefs()->getVarDef()){
                GlobalVar* var = nullptr;
                if (def -> isInit()) {
                    var = builder.createGlobalVar<Value*>(def -> getIdentifier(), 
                                                                 type, 
                                                                 new ConstIntValue(parseExp(def-> getInitVal())->getIntVal()));
                }
                else {
                    var = builder.createGlobalVar<Value*>(def -> getIdentifier(), 
                                                                 type, 
                                                                 new ConstIntValue(0));
                }
                globals -> push_back(var);
            }
        }
    }

    builder.emitIRModule(module);
}

int main(int argc, char *argv[]){
    ++ argv;
    if (argc > 0) genIR(argv[0], "testout.ll");
    else {
        printf("No input file\n");
        return 0;
    }
    return 0;
}
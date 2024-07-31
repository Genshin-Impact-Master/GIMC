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

// 表达式解析数组
Value* parseArrayLval(LValPtr lval, VarNode* var_node, bool is_number, bool ptr=false){
    auto array_entry = var_node -> _inst;
    for (auto &dim: lval -> getDims()) {
        auto inst = parseExp(dim, false, true, false).first;
        // 表达式解析出来的不是整数
        if (dim -> getResType() != BaseType::B_INT) {
            error_msg = "array index must be integer";
            error_handle();
        }
        array_entry = builder.createGEPInst(array_entry, inst);
    }
    if (ptr) return array_entry;
    if (!is_number) return builder.createLoadInst(var_node->_type == BaseType::B_INT? int32PointerType : floatPointerType, array_entry);
    else return builder.createLoadInst(var_node->_type == BaseType::B_INT? i32Type : floatType, array_entry);
}

// 解析表达式时使用
Value* parseVarLval(LValPtr lval, VarNode* var_node, bool ptr = false){
    auto var_entry = var_node -> _inst;
    if (ptr) return var_entry;
    return builder.createLoadInst(var_node->_type == BaseType::B_INT? i32Type: floatType, var_entry);
}

// Assign 语句
Value* parseVarLval(LValPtr lval){
    auto id = lval -> getIdentifier();
    // 检查变量是否存在
    if (! sym_tb.check_var(id)){
        error_msg = "variable " + id + " not defined";
        error_handle();
    }
    auto var_node = sym_tb.find_var(id);
    // 数组
    if (var_node -> _is_array) {
        if (lval -> getDims().size() != var_node->_dims.size()){
            error_msg = "array " + lval -> getIdentifier() + " expects " + std::to_string(var_node -> _dims.size()) + " dimensions, but " + std::to_string(lval -> getDims().size()) + " given";
            error_handle();
        }

        return parseArrayLval(lval, var_node, true, true);
    }
    return parseVarLval(lval, var_node, true);
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
        auto arg_exp = parseExp(R_param_i, false, false, true);
        // 判断函数参数类型是否正确，注意类型转换！以及数组的处理！
        // TODO: 函数形参数组的处理，为expResType多添加一个array_ptr
        // TODO: 类型不匹配时进行类型转换
        // 类型转换
        if (R_param_i -> getResType() == BaseType::B_FLOAT && F_param_i -> getType() == BaseType::B_INT) arg_exp.first = builder.createFp2IntInst(arg_exp.first);
        if (R_param_i -> getResType() == BaseType::B_INT && F_param_i -> getType() == BaseType::B_FLOAT) arg_exp.first = builder.createInt2FpInst(arg_exp.first);

        // 参数类型错误
        if (R_param_i -> getResType() == BaseType::B_ARRAY_PTR && !F_param_i -> isArray()) {
            error_msg = "function " + func_call_exp -> getIdentifier() + " expects array argument, but " + std::to_string(R_param_i -> getResType()) + " given";
            error_handle();
        }
        else if (R_param_i -> getResType() != BaseType::B_ARRAY_PTR && F_param_i -> isArray()) {
            error_msg = "function " + func_call_exp -> getIdentifier() + " does not expect array argument, but " + std::to_string(R_param_i -> getResType()) + " given";
            error_handle();   
        }
        args.push_back(arg_exp.first);
    }
    return builder.createCallInst(func_node -> _entry, args);
}

// 返回表达式IR、是否为常量表达式、是否合法
// is_cond 用于判断是否为条件表达式
// is_exp 用于判断是否为表达式 (返回类型只有int/float)
// is_func_param 用于判断是否为函数参数 (返回类型有int/float/array_ptr)
int and_cnt = 1;
int or_cnt = 1;
pair<Value*,bool> parseExp(ExpPtr exp, bool is_cond, bool is_exp, bool is_func_param){
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
            // 变量不是数组
            if (!var_node->_is_array) return pair<Value*, bool>(parseVarLval(tmp, var_node), var_node->_is_const);
            // 变量是数组
            if (!is_func_param){
                // 检查数组维数是否正确
                // 是否取到了数
                if (tmp -> getDims().size() != var_node->_dims.size()){
                    error_msg = "array " + tmp -> getIdentifier() + " expects " + std::to_string(var_node->_dims.size()) + " dimensions, but " + std::to_string(tmp -> getDims().size()) + " given";
                    error_handle();
                }
                return pair<Value*,bool>(parseArrayLval(tmp, var_node, true), var_node->_is_const);
            }
            else {
                // 作为函数实参时可以是数组指针
                if (tmp -> getDims().size() == var_node -> _dims.size()) return pair<Value*,bool>(parseArrayLval(tmp, var_node, true), false); 
                else if (tmp -> getDims().size() > var_node -> _dims.size()){
                    error_msg = "array " + tmp -> getIdentifier() + " expects " + std::to_string(var_node->_dims.size()) + " dimensions, but " + std::to_string(tmp -> getDims().size()) + " given";
                    error_handle();
                }
                else {
                    exp -> addResType(BaseType::B_ARRAY_PTR);
                    return pair<Value*,bool>(parseArrayLval(tmp, var_node, false), false);
                }
            }
        }
        case ExpType::ET_BIN :{

            auto tmp = dynamic_pointer_cast<BinaryExp>(exp);
            // 二元表达式不可能返回一个array_ptr
            auto left = parseExp(tmp -> getExp1(), is_cond, is_exp, false);
            auto right = parseExp(tmp -> getExp2(), is_cond, is_exp, false);
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
                case BinOpType::OP_AND: {
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    BBlock* par_block = builder.getparent();
                    BBlock* and_false = builder.createBBlock("and_false"+to_string(and_cnt), voidType);
                    BBlock* and_true = builder.createBBlock("and_true"+to_string(and_cnt), voidType);
                    BBlock* and_end = builder.createBBlock("and_end"+to_string(and_cnt), voidType);
                    and_cnt++;
                    builder.createBrInst(left.first, and_true, and_false, par_block);
                }
                default: {
                    error_msg = "unsupported binary operator";
                    error_handle();
                }   
            }
        }
    }
}

// TODO: add compare expression and parse it 
void parseStmt(StmtPtr _stmt, BBlock* loop_st = nullptr, BBlock* loop_ed = nullptr) {
    if (_stmt -> getType() == StmtType::ST_ASSIGN) {
        parseAssign(dynamic_pointer_cast<AssignStmt>(_stmt));
    }
    else if (_stmt -> getType() == StmtType::ST_IF) {
        parseIfElse(dynamic_pointer_cast<IfElseStmt>(_stmt));
    }
    else if (_stmt -> getType() == StmtType::ST_WHILE) {
        parseWhile(dynamic_pointer_cast<WhileStmt>(_stmt));
    }
    else if (_stmt -> getType() == StmtType::ST_RETURN) {
        parseReturn(dynamic_pointer_cast<ReturnStmt>(_stmt));
    }   
    else if (_stmt -> getType() == StmtType::ST_BREAK) {
        parseBreak(_stmt, loop_ed);
    }
    else if (_stmt -> getType() == StmtType::ST_CONTINUE) {
        parseContinue(_stmt, loop_st);
    }
    else if (_stmt -> getType() == StmtType::ST_BLOCK) {
        parseBlock(dynamic_pointer_cast<Block>(_stmt));
    }
}

void parseDecl(DeclPtr decl, bool is_global = false) {
    if (decl -> isConst()) {
        auto const_decl = decl -> getConstDecl();

    }
}

void parseAssign(AssignStmtPtr stmt){
    auto lval_inst = parseVarLval(stmt -> getLVal());
    auto exp_inst = parseExp(stmt -> getExp(), false, true, false);
    builder.createStoreInst(exp_inst.first, lval_inst);
}

int if_cnt = 1;
void parseIfElse(IfElseStmtPtr stmt){
    auto cond_inst = parseExp(stmt -> getCond(), true, false, false).first;
    BBlock* if_else_end = builder.createBBlock("if_end" + to_string(if_cnt), voidType);
    BBlock* if_true = builder.createBBlock("if_true" + to_string(if_cnt), voidType);
    parseStmt(stmt -> getThenStmt());
    builder.createBrInst(nullptr, if_else_end, nullptr);
    if (stmt -> getElseStmt() != nullptr){
        BBlock* if_false = builder.createBBlock("if_true" + to_string(if_cnt), voidType);
        parseStmt(stmt -> getElseStmt());
        builder.createBrInst(nullptr, if_else_end, nullptr);
        builder.createBrInst(cond_inst, if_true, if_false);
    }
    else builder.createBrInst(cond_inst, if_true, if_else_end);
    if_cnt++;
    builder.setChosedBBlock(if_else_end);
}
void parseWhile(WhileStmtPtr stmt){
    
}

void parseReturn(ReturnStmtPtr stmt){
    if (stmt -> getExp() == nullptr) ;
    else builder.createRetInst(parseExp(stmt -> getExp(), false, true, false).first);
}

void parseBreak(StmtPtr stmt, BBlock* bBlock) {
    builder.createBrInst(nullptr, bBlock, nullptr);
}

void parseContinue(StmtPtr stmt, BBlock* bBlock){
    builder.createBrInst(nullptr, bBlock, nullptr);
}

void parseBlock(BlockPtr block) {
    sym_tb.enter_block();
    auto bk = block -> getBlockItem();
    for (int i = 0; i < bk -> getStmt().size(); i++) {
        auto stmt = bk -> getStmt()[i];
        if (stmt -> _node_type == NodeType::NT_DECL) parseDecl(dynamic_pointer_cast<Decl>(stmt));
        else {
            auto _stmt = dynamic_pointer_cast<Stmt>(stmt);

        }
    }
    sym_tb.exit_block();
}

void parseFuncDefine(FuncDefPtr func_def) {
    // 获取形参类型
    if (func_def -> hasParam()){
        // 有参数函数
        vector<baseTypePtr> param_types;
        for (int i = 0; i < func_def->getFuncFParams()->getFuncFParam().size(); i++) 
            param_types.pb(func_def->getFuncFParams()->getFuncFParam()[i]->getType() == BaseType::B_INT ? int32PointerType : floatPointerType);
        auto ret_ty = func_def->getReturnType() == BaseType::B_INT ? int32PointerType : func_def->getReturnType() == BaseType::B_FLOAT ? floatPointerType : voidType;
        Function* func = builder.createFunction(func_def -> getIdentifier(), ret_ty, param_types);
        BBlock* func_entry = builder.createBBlock("entry", voidType, func);
        func -> setEntry(func_entry);
        vector<Value> &params = func -> getArgus();
        for (int i = 0; i< params.size(); i++) {
            auto F_param = func_def->getFuncFParams()->getFuncFParam()[i];
            Instruction* param_ptr = builder.createAllocaInst(F_param -> getIdentifier(), F_param -> getType() == BaseType::B_INT ? int32PointerType : floatPointerType);
            builder.createStoreInst(&params[i], param_ptr);
        }
        sym_tb.add_func(func_def -> getIdentifier(), func_def -> getReturnType(), func_def -> getFuncFParams(), func);
    }
    else {
        // 无参数函数
        auto ret_ty = func_def->getReturnType() == BaseType::B_INT ? int32PointerType : func_def->getReturnType() == BaseType::B_FLOAT ? floatPointerType : voidType;
        Function* func = builder.createFunction(func_def -> getIdentifier(), ret_ty, Zero_Argu_Type_List);
        BBlock* func_entry = builder.createBBlock("entry", voidType, func);
        func -> setEntry(func_entry);
        sym_tb.add_func(func_def -> getIdentifier(), func_def -> getReturnType(), func_def -> getFuncFParams(), func);
    }
    
    // 解析函数体
    parseBlock(func_def -> getFuncBlock());
} 




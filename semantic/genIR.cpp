#include "../include/IR/IRBuilder.h"
#include "../include/SymbolTable.hpp"
#include "genIR.hpp"
#include "errors.hpp"


void parseDecl(DeclPtr decl, bool is_global = false);
void parseAssign(AssignStmtPtr stmt);
void parseIfElse(IfElseStmtPtr stmt, BBlock* loop_st = nullptr, BBlock* loop_ed = nullptr);
void parseWhile(WhileStmtPtr stmt);
void parseReturn(ReturnStmtPtr stmt);
void parseBreak(StmtPtr stmt, BBlock* bBlock);
void parseContinue(StmtPtr stmt, BBlock* bBlock);
void parseBlock(BlockPtr block, vector<VarNode *> *va_list = nullptr, BBlock* loop_st = nullptr, BBlock* loop_ed = nullptr);
pair<Value*,bool> parseExp(ExpPtr exp, bool is_cond, bool is_exp, bool is_func_param, BBlock* cond_true=nullptr, BBlock* cond_false=nullptr);
void parseArrayInitVal(ArrayInitValPtr arr_init, vector<int> &pos, vector<int> dims, int depth, Instruction* array_base, bool is_float, bool is_const=false);
void parseArrayInitVal(ArrayInitValPtr arr_init, vector<int> &pos, vector<int> dims, int depth, bool is_float, map<vector<int>, NumberPtr>& arr_val_mp);
// 每个 example 必须包含
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



// TODO: 传递数组形参后面的维度置为0
// 表达式解析数组
Value* parseArrayLval(LValPtr lval, VarNode* var_node, bool is_number, bool ptr=false){
    auto array_entry = var_node -> _inst;
    int i = 0;
    for (auto dim: lval -> getDims()) {
        auto inst = parseExp(dim, false, true, false).first;
        
        // 表达式解析出来的不是整数
        if (dim -> getResType() != BaseType::B_INT) {
            error_msg = "array index must be integer";
            error_handle();
        }
        if (i == 0 && var_node -> _is_param) array_entry = builder.createGEPInst(array_entry, inst, nullptr,true);
        else array_entry = builder.createGEPInst(array_entry, inst);
        i++;
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

        return parseArrayLval(lval, var_node, false, true);
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

    // 函数参数个数不匹配
    auto func_node = sym_tb.find_func(func_call_exp -> getIdentifier());
    auto R_param = func_call_exp -> getArgs();
    if (func_node -> _func_params == nullptr && R_param.size() != 0){
        error_msg = "function " + func_call_exp -> getIdentifier() + " expects zero arguments, but " + std::to_string(R_param.size()) + " given";
        error_handle();
    }

    if (func_node -> _func_params == nullptr) return builder.createCallInst(func_node -> _entry, Zero_Argu_List);
    auto F_param = func_node -> _func_params -> getFuncFParam();
    if (R_param.size() != F_param.size()){
        error_msg = "function " + func_call_exp -> getIdentifier() + " expects " + std::to_string(F_param.size()) + " arguments, but " + std::to_string(R_param.size()) + " given";
        error_handle();
    }

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
        if ( (R_param_i -> getResType() == BaseType::B_FARRAY_PTR || R_param_i -> getResType() == BaseType::B_ARRAY_PTR) && !F_param_i -> isArray()) {
            error_msg = "function " + func_call_exp -> getIdentifier() + " expects array argument, but " + std::to_string(R_param_i -> getResType()) + " given";
            error_handle();
        }
        else if ( (R_param_i -> getResType() != BaseType::B_ARRAY_PTR && R_param_i -> getResType() != BaseType::B_FARRAY_PTR) && F_param_i -> isArray()) {
            error_msg = "function " + func_call_exp -> getIdentifier() + " does not expect array argument, but " + std::to_string(R_param_i -> getResType()) + " given";
            error_handle();   
        }
        else if (R_param_i -> getResType() == BaseType::B_FARRAY_PTR && F_param_i -> getType() == BaseType::B_INT && F_param_i -> isArray()) {
            error_msg = "function " + func_call_exp -> getIdentifier() + " expects float array argument, but " + std::to_string(R_param_i -> getResType()) + " given";
            error_handle();
        }
        else if (R_param_i -> getResType() == BaseType::B_ARRAY_PTR && F_param_i -> getType() == BaseType::B_FLOAT && F_param_i -> isArray()) {
            error_msg = "function " + func_call_exp -> getIdentifier() + " expects int array argument, but " + std::to_string(R_param_i -> getResType()) + " given";
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
pair<Value*,bool> parseExp(ExpPtr exp, bool is_cond, bool is_exp, bool is_func_param, BBlock* cond_true, BBlock* cond_false){
    if (exp -> getNotCnt() % 2 != 0) {
        if (!is_cond) {
            error_msg = "boolean type expression is not supported";
            error_handle();
        }
        auto ret = parseExp(exp, is_cond, is_exp, is_func_param);
        if (exp -> getResType() == BaseType::B_FLOAT) ret.first = builder.createFcmpInst(FCondKind::Oeq, new ConstFloatValue(0.), ret.first);
        else ret.first = builder.createIcmpInst(ICondKind::Eq, new ConstIntValue(0), ret.first);

        ret.first = builder.createZextInst(i32Type, ret.first);
        exp -> addResType(BaseType::B_INT);
        return ret;
    }

    if (exp -> getNegCnt() % 2 != 0) {
        auto ret = parseExp(exp, is_cond, is_exp, is_func_param);
        if (exp -> getResType() == BaseType::B_FLOAT) ret.first = builder.createBinaryInst(InstKind::Subf, new ConstFloatValue(0.), ret.first);
        else ret.first = builder.createBinaryInst(InstKind::Sub, new ConstIntValue(0), ret.first);
        return ret;
    }
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
            else if (sym_tb.find_func(tmp -> getIdentifier()) -> _ret_type == BaseType::B_VOID && (is_exp||is_cond||is_func_param)){
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
                return pair<Value*,bool>(parseArrayLval(tmp, var_node, true), false);
            }
            else {
                // 作为函数实参时可以是数组指针
                if (tmp -> getDims().size() == var_node -> _dims.size()) return pair<Value*,bool>(parseArrayLval(tmp, var_node, true), false); 
                else if (tmp -> getDims().size() > var_node -> _dims.size()){
                    error_msg = "array " + tmp -> getIdentifier() + " expects " + std::to_string(var_node->_dims.size()) + " dimensions, but " + std::to_string(tmp -> getDims().size()) + " given";
                    error_handle();
                }
                else {
                    exp -> addResType(var_node -> _is_float ? BaseType::B_FARRAY_PTR : BaseType::B_ARRAY_PTR);
                    return pair<Value*,bool>(parseArrayLval(tmp, var_node, false, true), false);
                }
            }
            
        }
        case ExpType::ET_BIN :{
            auto tmp = dynamic_pointer_cast<BinaryExp>(exp);
            if (tmp -> getOp() == BinOpType::OP_AND) {
                if (!is_cond) {
                    error_msg = "boolean type expression is not supported";
                    error_handle();
                }
                exp -> addResType(BaseType::B_JMP);
                BBlock* par_block = builder.getChosedBBlk();
                BBlock* and_ls_true = builder.createBBlock("and_ls_true" + to_string(and_cnt), voidType);
                and_cnt++;

                builder.setChosedBBlock(par_block);
                // 解析左值
                auto left = parseExp(tmp -> getExp1(), true, false, false, and_ls_true, cond_false);
                if (tmp -> getExp1() -> getResType() != BaseType::B_JMP) {
                    // 转换成cmpInst
                    if (tmp -> getExp1() -> getResType() != BaseType::B_BOOL) {
                        if (tmp -> getExp1() -> getResType() == BaseType::B_INT) left.first = builder.createIcmpInst(ICondKind::Ne, new ConstIntValue(0), left.first);
                        if (tmp -> getExp1() -> getResType() == BaseType::B_FLOAT) left.first = builder.createFcmpInst(FCondKind::One, new ConstFloatValue(0), left.first);
                    }
                    builder.createBrInst(left.first, and_ls_true, cond_false);
                }
                builder.setChosedBBlock(and_ls_true);
                // 解析右值        cout<< "函数体解析完毕" << endl;

                auto right = parseExp(tmp -> getExp2(), true, false, false, cond_true, cond_false);
                if (tmp -> getExp2() -> getResType() != BaseType::B_JMP) {
                    // 转换成cmpInst
                    if (tmp -> getExp2() -> getResType() != BaseType::B_BOOL) {
                        if (tmp -> getExp2() -> getResType() == BaseType::B_INT) right.first = builder.createIcmpInst(ICondKind::Ne, new ConstIntValue(0), right.first);
                        if (tmp -> getExp2() -> getResType() == BaseType::B_FLOAT) right.first = builder.createFcmpInst(FCondKind::One, new ConstFloatValue(0), right.first);
                    }
                    builder.createBrInst(right.first, cond_true, cond_false);
                }
                return pair<Value*,bool>(nullptr, false);
            }



            if (tmp -> getOp() == BinOpType::OP_OR) {
                if (!is_cond) {
                    error_msg = "boolean type expression is not supported";
                    error_handle();
                }
                exp -> addResType(BaseType::B_JMP);
                BBlock* par_block = builder.getChosedBBlk();
                BBlock* or_ls_false = builder.createBBlock("or_ls_false" + to_string(or_cnt), voidType);
                or_cnt++;

                builder.setChosedBBlock(par_block);
                // 解析左值
                auto left = parseExp(tmp -> getExp1(), true, false, false, cond_true, or_ls_false);
                if (tmp -> getExp1() -> getResType() != BaseType::B_JMP) {
                    // 转换成cmpInst
                    if (tmp -> getExp1() -> getResType() != BaseType::B_BOOL) {
                        if (tmp -> getExp1() -> getResType() == BaseType::B_INT) left.first = builder.createIcmpInst(ICondKind::Ne, new ConstIntValue(0), left.first);
                        if (tmp -> getExp1() -> getResType() == BaseType::B_FLOAT) left.first = builder.createFcmpInst(FCondKind::One, new ConstFloatValue(0), left.first);
                    }
                    builder.createBrInst(left.first, cond_true, or_ls_false);
                }
                builder.setChosedBBlock(or_ls_false);
                // 解析右值
                auto right = parseExp(tmp -> getExp2(), true, false, false, cond_true, cond_false);
                if (tmp -> getExp2() -> getResType() != BaseType::B_JMP) {
                    // 转换成cmpInst
                    if (tmp -> getExp2() -> getResType() != BaseType::B_BOOL) {
                        if (tmp -> getExp2() -> getResType() == BaseType::B_INT) right.first = builder.createIcmpInst(ICondKind::Ne, new ConstIntValue(0), right.first);
                        if (tmp -> getExp2() -> getResType() == BaseType::B_FLOAT) right.first = builder.createFcmpInst(FCondKind::One, new ConstFloatValue(0), right.first);
                    }
                    builder.createBrInst(right.first, cond_true, cond_false);
                }
                return pair<Value*,bool>(nullptr, false);
            }

            // 二元表达式不可能返回一个array_ptr
            auto left = parseExp(tmp -> getExp1(), is_cond, is_exp, false);
            auto right = parseExp(tmp -> getExp2(), is_cond, is_exp, false);



            // 如果左右值也是一个比较表达式，是否需要类型提升? 不需要 
            // TODO:可能需要
            if (tmp -> getExp1() -> getResType() == BaseType::B_BOOL) 
                left.first = builder.createZextInst(i32Type, left.first), tmp -> getExp1() -> addResType(BaseType::B_INT);
            if (tmp -> getExp2() -> getResType() == BaseType::B_BOOL) 
                right.first = builder.createZextInst(i32Type, right.first), tmp -> getExp2() -> addResType(BaseType::B_INT);
            

            // 是否含有浮点数
            bool is_float = tmp -> getExp1() -> getResType() == BaseType::B_FLOAT || tmp -> getExp2() -> getResType() == BaseType::B_FLOAT;
            exp -> addResType(is_float ? BaseType::B_FLOAT : BaseType::B_INT);
            // 类型提升
            if (is_float) {
                if (tmp -> getExp1() -> getResType() == BaseType::B_INT) left.first = builder.createInt2FpInst(left.first);
                if (tmp -> getExp2() -> getResType() == BaseType::B_INT) right.first = builder.createInt2FpInst(right.first);
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

                // 条件比较
                case BinOpType::OP_GTE :{
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    exp -> addResType(BaseType::B_BOOL);
                    if (is_float) return pair<Value*, bool>(builder.createFcmpInst(FCondKind::Oge, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createIcmpInst(ICondKind::Sge, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_EQ :{
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    exp -> addResType(BaseType::B_BOOL);
                    if (is_float) return pair<Value*, bool>(builder.createFcmpInst(FCondKind::Oeq, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createIcmpInst(ICondKind::Eq, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_NEQ :{
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    exp -> addResType(BaseType::B_BOOL);
                    if (is_float) return pair<Value*, bool>(builder.createFcmpInst(FCondKind::One, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createIcmpInst(ICondKind::Ne, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_GT: {
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    exp -> addResType(BaseType::B_BOOL);
                    if (is_float) return pair<Value*, bool>(builder.createFcmpInst(FCondKind::Ogt, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createIcmpInst(ICondKind::Sgt, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_LT: {
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    exp -> addResType(BaseType::B_BOOL);
                    if (is_float) return pair<Value*, bool>(builder.createFcmpInst(FCondKind::Olt, left.first, right.first), left.second && right.second);
                    else return pair<Value*, bool>(builder.createIcmpInst(ICondKind::Slt, left.first, right.first), left.second && right.second);
                }
                case BinOpType::OP_LTE: {
                    if (!is_cond) {
                        error_msg = "boolean type expression is not supported";
                        error_handle();
                    }
                    exp -> addResType(BaseType::B_BOOL);
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

// TODO: add compare expression and parse it 
void parseStmt(StmtPtr _stmt, BBlock* loop_st = nullptr, BBlock* loop_ed = nullptr) {
    if (_stmt -> getType() == StmtType::ST_ASSIGN) {
        parseAssign(dynamic_pointer_cast<AssignStmt>(_stmt));
    }
    else if (_stmt -> getType() == StmtType::ST_IF) {
        parseIfElse(dynamic_pointer_cast<IfElseStmt>(_stmt), loop_st, loop_ed);
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
        parseBlock(dynamic_pointer_cast<BlockStmt>(_stmt)->getBlock(), nullptr, loop_st, loop_ed);
    }
    else if (_stmt -> getType() == StmtType::ST_EXP) {
        parseExp(dynamic_pointer_cast<ExpStmt>(_stmt)->getExp(), false, false, false);
    }
}

NumberPtr getConstExpValue(ExpPtr exp, bool array_dim = false) {
    auto ret = NumberPtr(new Number());
    if (exp -> getNegCnt() % 2 != 0) {
        ret = getConstExpValue(exp, array_dim);
        ret -> addIntVal(-ret -> getIntVal());
        ret -> addFloatVal(-ret -> getFloatVal());
        return ret;
    }
    switch (exp -> getType()) {
        case ExpType::ET_INT: {
            ret = dynamic_pointer_cast<Number>(exp);
            return ret;
        }
        case ExpType::ET_FLOAT: {
            if (array_dim) {
                error_msg = "array dimension is not a float expression";
                error_handle();
            }
            auto num = dynamic_pointer_cast<Number>(exp);
            if (num -> getIsFloat()) {
                ret -> addFloatVal(num -> getFloatVal());
                ret -> addIntVal(int(num -> getFloatVal()));
            }
            else {
                ret -> addIntVal(num -> getIntVal());
                ret -> addFloatVal(float(num -> getIntVal()));
            }
            return ret;
        }
        case ExpType::ET_LVAL: {
            auto var_node = sym_tb.find_var(dynamic_pointer_cast<LVal>(exp) -> getIdentifier());
            if (! var_node -> _is_const) {
                error_msg = "not a constant expression";
                error_handle();
            }
            if (var_node -> _is_float && array_dim) {
                error_msg = "array dimension is not a float expression";
                error_handle();
            }
            if (var_node -> _is_float) {
                ret -> addFloatVal(var_node -> _const_float);
                ret -> addIntVal(int(var_node -> _const_float));
            }
            else {
                ret -> addIntVal(var_node -> _const_int);
                ret -> addFloatVal(float(var_node -> _const_int));
            }
            return ret;
        }
        case ExpType::ET_BIN: {
            auto bin_exp = dynamic_pointer_cast<BinaryExp>(exp);
            auto left = getConstExpValue(bin_exp -> getExp1());
            auto right = getConstExpValue(bin_exp -> getExp2());
            switch (bin_exp -> getOp()){
                case BinOpType::OP_ADD: {
                    ret -> addIntVal(left -> getIntVal() + right -> getIntVal());
                    ret -> addFloatVal(left -> getFloatVal() + right -> getFloatVal());
                    return ret;
                }
                case BinOpType::OP_SUB: {
                    ret -> addIntVal(left -> getIntVal() - right -> getIntVal());
                    ret -> addFloatVal(left -> getFloatVal() - right -> getFloatVal());
                    return ret;
                }
                case BinOpType::OP_MUL: {
                    ret -> addIntVal(left -> getIntVal() * right -> getIntVal());
                    ret -> addFloatVal(left -> getFloatVal() * right -> getFloatVal());
                    return ret;
                }
                case BinOpType::OP_DIV: {
                    ret -> addIntVal(left -> getIntVal() / right -> getIntVal());
                    ret -> addFloatVal(left -> getFloatVal() / right -> getFloatVal());
                    return ret;
                }
                case BinOpType::OP_MOD: {
                    ret -> addIntVal(left -> getIntVal() % right -> getIntVal());
                    return ret;
                }
                default:
                    break;
            }
        }
        default: {
            error_msg = "unsupported constant expression";
            error_handle();
        }
    }
    return ret;
}
GlobalVar* parseGlobalArray(string name, vector<int> dims, vector<int> pos, int dep, map<vector<int>, NumberPtr> arr_val_mp, bool is_float=false) {
    vector<Value*> ret;
    auto array_ty = is_float? floatType: i32Type;
    baseTypePtr array_base = make_shared<PointerType>(array_ty, dims[dims.size()-1]);
    for (int i=dims.size()-2;i>=dep;i--) array_base = make_shared<PointerType>(array_base, dims[i]);
    for (int i = 0; i < dims[dep]; i++) {
        pos[dep] = i;
        if (dep == static_cast<int>(dims.size())-1) {
            if (arr_val_mp.find(pos) != arr_val_mp.end()) {
                if (is_float) ret.push_back(new ConstFloatValue(arr_val_mp[pos] -> getFloatVal()));
                else ret.push_back(new ConstIntValue(arr_val_mp[pos] -> getIntVal()));
            }
            else {
                if (is_float) ret.push_back(new ConstFloatValue(0.0));
                else ret.push_back(new ConstIntValue(0));
            }
        }
        else ret.push_back(parseGlobalArray(name, dims, pos, dep+1, arr_val_mp, is_float));
    }
    return builder.createGlobalVar<vector<Value*>>(name, array_base, ret);
};



int block_cnt = 1;
void parseDecl(DeclPtr decl, bool is_global) {
    if (decl -> isConst()) {
        auto const_decl = decl -> getConstDecl();
        auto const_type = const_decl -> getType() == BaseType::B_INT ? int32PointerType : floatPointerType;
        auto const_defs = const_decl -> getConstDef() -> getConstDef();
        for (auto def: const_defs) {
            if (sym_tb.check_var_current_bk(def -> getIdentifier())) {
                error_msg = "redeclared identifier: " + def -> getIdentifier();
                error_handle();
            }
            if (def -> isArray()) {
                auto array_dim = def -> getArrayDim() -> getDim();
                vector<int>dims, pos;
                for (auto dim:array_dim) dims.push_back(getConstExpValue(dim -> getExp(), true) -> getIntVal());
                pos.resize(dims.size());
                // 创建数组容器
                auto array_ty = const_type == int32PointerType? i32Type: floatType;
                baseTypePtr array_base = make_shared<PointerType>(array_ty, dims[dims.size()-1]);
                for (int i=dims.size()-2;i>=0;i--) array_base = make_shared<PointerType>(array_base, dims[i]);
                
                if (!is_global) {
                    auto alloc = builder.createAllocaInst(def->getIdentifier() + to_string(block_cnt++), array_base);
                    int array_tot_size = 1;
                    for (auto dim: dims) array_tot_size *= dim;
                    // 初始化
                    auto mem_init = builder.createInitMemInst(array_ty, alloc, array_tot_size<<2);
                    parseArrayInitVal(def -> getArrayInitVal(), pos, dims, 0, alloc, array_ty == floatType, true);
                    // 添加到符号表
                    sym_tb.add_var(def -> getIdentifier(), const_decl -> getType(), def -> isArray(), true, const_decl -> getType() == B_FLOAT, alloc, dims);
                }
                else {
                    map<vector<int>, NumberPtr> arr_val_mp;
                    parseArrayInitVal(def -> getArrayInitVal(), pos, dims, 0, const_decl -> getType() == B_FLOAT, arr_val_mp);
                    for (auto it: arr_val_mp) {
                        for (int i:it.first) cout<<i<<" ";
                        cout<<": ";
                        cout<< it.second -> getIntVal() << endl;
                    }
                    auto alloc = parseGlobalArray(def -> getIdentifier(), dims, pos, 0, arr_val_mp, const_decl -> getType() == B_FLOAT);
                    sym_tb.add_var(def -> getIdentifier(), const_decl -> getType(), def -> isArray(), true, const_decl -> getType() == B_FLOAT, alloc, dims);
                    globals -> push_back(alloc);
                }
            }
            // 非数组
            else {
                // 解析初始值
                auto init_exp = getConstExpValue(def -> getInitVal() -> getExp());
                if (!is_global) {
                    
                    auto alloc = builder.createAllocaInst(def -> getIdentifier() + to_string(block_cnt++), const_type);
                    // 添加到符号表
                    sym_tb.add_var(def -> getIdentifier(), const_decl -> getType(), def -> isArray(), true, const_decl -> getType() == B_FLOAT, alloc, init_exp -> getIntVal(), init_exp -> getFloatVal());
                    if (const_type == int32PointerType) builder.createStoreInst(new ConstIntValue(init_exp -> getIntVal()), alloc);
                    else builder.createStoreInst(new ConstFloatValue(init_exp -> getFloatVal()), alloc);
                }


                else {
                    if (const_type == int32PointerType){
                        auto alloc = builder.createGlobalVar<Value*>(def -> getIdentifier(), const_type, new ConstIntValue(init_exp -> getIntVal()));
                        sym_tb.add_var(def -> getIdentifier(), const_decl -> getType(), def -> isArray(), true, const_decl -> getType() == B_FLOAT, alloc, init_exp -> getIntVal(), init_exp -> getFloatVal());
                        globals -> push_back(alloc);
                    }
                    else {
                        
                        auto alloc = builder.createGlobalVar<Value*>(def -> getIdentifier(), const_type, new ConstFloatValue(init_exp -> getFloatVal()));
                        sym_tb.add_var(def -> getIdentifier(), const_decl -> getType(), def -> isArray(), true, const_decl -> getType() == B_FLOAT, alloc, init_exp -> getIntVal(), init_exp -> getFloatVal());
                        globals -> push_back(alloc);
                    }
                }
            }
        }
    }
    else {
        auto var_decl = decl -> getVarDecl();
        auto var_type = var_decl -> getType() == B_INT ? int32PointerType : floatPointerType;
        auto var_defs = var_decl -> getVarDefs() -> getVarDef();
        for (auto def: var_defs) {
            if (sym_tb.check_var_current_bk(def -> getIdentifier())) {
                error_msg = "redeclared identifier: " + def -> getIdentifier();
                error_handle();
            }
                // TODO: 处理数组
            if (def -> isArray()) {
                auto array_dim = def -> getArrayDim() -> getDim();
                vector<int>dims, pos;
                for (auto dim:array_dim) dims.push_back(getConstExpValue(dim -> getExp(), true) -> getIntVal());
                pos.resize(dims.size());
                // 创建数组容器
                auto array_ty = var_type == int32PointerType? i32Type: floatType;
                baseTypePtr array_base = make_shared<PointerType>(array_ty, dims[dims.size()-1]);
                for (int i=dims.size()-2;i>=0;i--){
                    array_base = make_shared<PointerType>(array_base, dims[i]);
                }
                if (!is_global) {
                    auto alloc = builder.createAllocaInst(def->getIdentifier()+ to_string(block_cnt++), array_base);
                    if (def -> isInit()){
                        int array_tot_size = 1;
                        for (auto dim: dims) array_tot_size *= dim;
                        // 初始化
                        auto mem_init = builder.createInitMemInst(array_ty, alloc, array_tot_size<<2);
                        parseArrayInitVal(def -> getArrayInitVal(), pos, dims, 0, alloc, array_ty == floatType, false);
                    }
                    sym_tb.add_var(def -> getIdentifier(), var_decl -> getType(), def -> isArray(), false, var_decl -> getType() == B_FLOAT, alloc, dims);
                }
                else {
                    map<vector<int>, NumberPtr> arr_val_mp;
                    GlobalVar* alloc = nullptr;
                    if (!def -> isInit()) alloc = parseGlobalArray(def -> getIdentifier(), dims, pos, 0, arr_val_mp, var_decl -> getType() == B_FLOAT);
                    else {
                        parseArrayInitVal(def -> getArrayInitVal(), pos, dims, 0, var_decl -> getType() == B_FLOAT, arr_val_mp);
                        for (auto it: arr_val_mp) {
                            for (int i:it.first) cout<<i<<" ";
                            cout<<": ";
                            cout<< it.second -> getIntVal() << endl;
                        }
                        alloc = parseGlobalArray(def -> getIdentifier(), dims, pos, 0, arr_val_mp, var_decl -> getType() == B_FLOAT);
                    }
                    sym_tb.add_var(def -> getIdentifier(), var_decl -> getType(), def -> isArray(), true, var_decl -> getType() == B_FLOAT, alloc, dims);
                    globals -> push_back(alloc);
                }
            }
            else {
                if (is_global) {
                    NumberPtr init_exp = nullptr;
                    
                    // 全局变量无初始值时默认为0
                    if (! def -> isInit()) {
                        if (var_decl -> getType() == B_INT) init_exp = NumberPtr(new Number(0, 0, false));
                        else init_exp = NumberPtr(new Number(0.0, 0, true));
                    }
                    else init_exp = getConstExpValue(def -> getInitVal());

                    GlobalVar* alloc = nullptr;
                    if (var_type == int32PointerType) alloc = builder.createGlobalVar<Value*>(def -> getIdentifier(), var_type,  new ConstIntValue(init_exp -> getIntVal()));
                    else alloc = builder.createGlobalVar<Value*>(def -> getIdentifier(), var_type,  new ConstFloatValue(init_exp -> getFloatVal()));
                    globals -> push_back(alloc);
                    sym_tb.add_var(def -> getIdentifier(), var_decl -> getType(), false, false, var_decl -> getType() == B_FLOAT, alloc);
                }
                else {
                    Value* init_exp = nullptr;
                    if (def -> isInit()) {
                        init_exp = parseExp(def -> getInitVal() , false, true, false).first;
                        if (def -> getInitVal() -> getResType() == BaseType::B_INT && var_decl -> getType() == B_FLOAT) init_exp = builder.createInt2FpInst(init_exp);
                        if (def -> getInitVal() -> getResType() == BaseType::B_FLOAT && var_decl -> getType() == B_INT) init_exp = builder.createFp2IntInst(init_exp);
                    }

                    auto alloc = builder.createAllocaInst(def -> getIdentifier()+ to_string(block_cnt++), var_type);
                    sym_tb.add_var(def -> getIdentifier(), var_decl -> getType(), false, false, var_decl -> getType() == B_FLOAT, alloc);
                    if (init_exp != nullptr) builder.createStoreInst(init_exp, alloc);
                }

            }
        }
    }
}

void parseAssign(AssignStmtPtr stmt){
    auto lval_inst = parseVarLval(stmt -> getLVal());
    auto exp_inst = parseExp(stmt -> getExp(), false, true, false);
    builder.createStoreInst(exp_inst.first, lval_inst);
}

int if_cnt = 1;
void parseIfElse(IfElseStmtPtr stmt, BBlock* loop_st, BBlock* loop_ed){
    BBlock* par_block = builder.getChosedBBlk();
    BBlock* if_true = builder.createBBlock("if_true" + to_string(if_cnt), voidType);
    BBlock* if_end = builder.createBBlock("if_end" + to_string(if_cnt), voidType);
    if_cnt+=1;

    // 处理基本块的跳转
    if (stmt -> getElseStmt() != nullptr) {
        BBlock* if_false = builder.createBBlock("if_false" + to_string(if_cnt-1), voidType);
        builder.setChosedBBlock(par_block);
        auto cond_exp = parseExp(stmt -> getCond(), true, false, false, if_true, if_false);
        // 如果不是and和or
        if (stmt -> getCond() -> getResType() != B_JMP ) {
            if (stmt -> getCond() -> getResType() != B_BOOL) {
                if (stmt -> getCond() -> getResType() == BaseType::B_INT) cond_exp.first = builder.createIcmpInst(ICondKind::Ne, new ConstIntValue(0), cond_exp.first);
                if (stmt -> getCond() -> getResType() == BaseType::B_FLOAT) cond_exp.first = builder.createFcmpInst(FCondKind::One, new ConstFloatValue(0), cond_exp.first);    
            }
            builder.createBrInst(cond_exp.first, if_true, if_false);
        }

        // 处理基本块
        builder.setChosedBBlock(if_false);
        parseStmt(stmt -> getElseStmt(), loop_st, loop_ed);
        builder.createBrInst(nullptr, if_end, nullptr);
    }
    else {
        builder.setChosedBBlock(par_block);
        auto cond_exp = parseExp(stmt -> getCond(), true, false, false, if_true, if_end);
        if (stmt -> getCond() -> getResType() != B_JMP ) {
            if (stmt -> getCond() -> getResType() != B_BOOL) {
                if (stmt -> getCond() -> getResType() == BaseType::B_INT) cond_exp.first = builder.createIcmpInst(ICondKind::Ne, new ConstIntValue(0), cond_exp.first);
                if (stmt -> getCond() -> getResType() == BaseType::B_FLOAT) cond_exp.first = builder.createFcmpInst(FCondKind::One, new ConstFloatValue(0), cond_exp.first);    
            }
            builder.createBrInst(cond_exp.first, if_true, if_end);
        }
    }
    builder.setChosedBBlock(if_true);
    parseStmt(stmt -> getThenStmt(), loop_st, loop_ed);
    builder.createBrInst(nullptr, if_end, nullptr);

    builder.setChosedBBlock(if_end);
    auto last = builder.getChosedBBlk();
}

//TODO: 解析循环
// 基本思路：用三个基本块实现
int loop_cnt = 1;
void parseWhile(WhileStmtPtr stmt){
    BBlock* par_block = builder.getChosedBBlk();
    BBlock* loop_st = builder.createBBlock("loop_st" + to_string(loop_cnt), voidType);
    BBlock* loop_ck = builder.createBBlock("loop_ck" + to_string(loop_cnt), voidType);
    BBlock* loop_ed = builder.createBBlock("loop_ed" + to_string(loop_cnt), voidType);
    loop_cnt += 1;
    builder.setChosedBBlock(par_block);
    builder.createBrInst(nullptr, loop_ck, nullptr);
    builder.setChosedBBlock(loop_ck);
    auto cond_exp = parseExp(stmt -> getCond(), true, false, false, loop_st, loop_ed);
    if (stmt -> getCond() -> getResType() != B_JMP ) {
        if (stmt -> getCond() -> getResType() != B_BOOL) {
            if (stmt -> getCond() -> getResType() == BaseType::B_INT) cond_exp.first = builder.createIcmpInst(ICondKind::Ne, new ConstIntValue(0), cond_exp.first);
            if (stmt -> getCond() -> getResType() == BaseType::B_FLOAT) cond_exp.first = builder.createFcmpInst(FCondKind::One, new ConstFloatValue(0), cond_exp.first);    
        }
        builder.createBrInst(cond_exp.first, loop_st, loop_ed);
    }

    builder.setChosedBBlock(loop_st);
    parseStmt(stmt -> getStmt(), loop_ck, loop_ed);
    builder.createBrInst(nullptr, loop_ck, nullptr);
    builder.setChosedBBlock(loop_ed);
}
// TODO: return void
void parseReturn(ReturnStmtPtr stmt){
    auto func = builder.getChosedFunc();
    auto type = func -> getType();
    if (stmt -> getExp() == nullptr && type != voidType) {
        error_msg = "return without value";
        error_handle();
    }
    if (stmt -> getExp() != nullptr && type == voidType) {
        error_msg = "return with value";
        error_handle();
    }
    if (stmt -> getExp() == nullptr) builder.createRetInst(&voidValue);
    else {

        auto ret_exp = parseExp(stmt -> getExp(), false, true, false).first;


        if (stmt -> getExp() -> getResType() == B_FLOAT && type == i32Type) ret_exp = builder.createFp2IntInst(ret_exp);
        else if (stmt -> getExp() -> getResType() == B_INT && type == floatType) ret_exp = builder.createInt2FpInst(ret_exp);
        builder.createRetInst(ret_exp);
    }

}

void parseBreak(StmtPtr stmt, BBlock* bBlock) {
    builder.createBrInst(nullptr, bBlock, nullptr);
}

void parseContinue(StmtPtr stmt, BBlock* bBlock){
    builder.createBrInst(nullptr, bBlock, nullptr);
}


void parseBlock(BlockPtr block, vector<VarNode*> *va_list, BBlock* loop_st, BBlock* loop_ed) {
    if (block -> getBlockItem() == nullptr) return;
    sym_tb.enter_block();
    
    // 添加形参
    if (va_list != nullptr) 
        for (auto var : *va_list) sym_tb.add_var(var);
    
    auto bk = block -> getBlockItem();
    for (int i = 0; i < bk -> getStmt().size(); i++) {

        auto stmt = bk -> getStmt()[i];
        if (stmt -> _node_type == NodeType::NT_DECL) parseDecl(dynamic_pointer_cast<Decl>(stmt));
        else {
            // std::cout << stmt -> _node_type << std::endl;
            auto _stmt = dynamic_pointer_cast<Stmt>(stmt);
            parseStmt(_stmt, loop_st, loop_ed);

        }
    }
    sym_tb.exit_block();

}



// TODO:形参加入符号表
void parseFuncDefine(FuncDefPtr func_def) {
    // 获取形参类型
    Function* func;
    vector<VarNode*> va_list;
    if (func_def -> hasParam()){
        // 有参数函数
        vector<baseTypePtr> param_types;
        for (int i = 0; i < func_def->getFuncFParams()->getFuncFParam().size(); i++) {
            if (func_def->getFuncFParams()->getFuncFParam()[i]-> isArray()) {
                if (func_def -> getFuncFParams() -> getFuncFParam()[i] -> getArrayDim() -> getDim().size() == 1) param_types.pb(func_def->getFuncFParams()->getFuncFParam()[i]->getType() == BaseType::B_INT ? int32PointerType : floatPointerType);
                else {
                    auto dims = func_def -> getFuncFParams() -> getFuncFParam()[i] -> getArrayDim() -> getDim();
                    auto fi = getConstExpValue(dims[1], true);
                    auto base = make_shared<PointerType>(func_def->getFuncFParams()->getFuncFParam()[i]->getType() == BaseType::B_INT ? i32Type : floatType, fi -> getIntVal());
                    for (int i=2;i < dims.size();i++) base = make_shared<PointerType>(base, getConstExpValue(dims[i], true) -> getIntVal());
                    param_types.pb(base);
                }
            }
            else param_types.pb(func_def->getFuncFParams()->getFuncFParam()[i]->getType() == BaseType::B_INT ? i32Type : floatType);
        }
        auto ret_ty = func_def->getReturnType() == BaseType::B_INT ? i32Type : func_def->getReturnType() == BaseType::B_FLOAT ? floatType : voidType;
        func = builder.createFunction(func_def -> getIdentifier(), ret_ty, param_types);

        BBlock* func_entry = builder.createBBlock("entry", voidType, func);
        func -> setEntry(func_entry);

        vector<Value> &params = func -> getArgus();
        for (int i = 0; i< params.size(); i++) {
            auto F_param = func_def->getFuncFParams()->getFuncFParam()[i];
            Instruction* param_ptr =nullptr;
            if (!F_param -> isArray()){
                param_ptr = builder.createAllocaInst(F_param -> getIdentifier(), F_param -> getType() == BaseType::B_INT ? int32PointerType : floatPointerType);
                auto tmp = builder.createStoreInst(&params[i], param_ptr);
                va_list.push_back(new VarNode(F_param -> getType(), F_param -> getIdentifier(), F_param -> isArray(), false, F_param -> getType() == BaseType::B_FLOAT, param_ptr));

            }
            else {
                auto _dims = func_def -> getFuncFParams() -> getFuncFParam()[i] -> getArrayDim() -> getDim();
                vector<int> dims;
                dims.resize(_dims.size());
                if (_dims.size() == 1) {
                    param_ptr = builder.createAllocaInst(F_param -> getIdentifier()+".addr", F_param -> getType() == BaseType::B_INT ? int32PointerType : floatPointerType, nullptr, true);
                    auto tmp = builder.createStoreInst(&params[i], param_ptr);
                    param_ptr = builder.createLoadInst(F_param -> getIdentifier(), F_param -> getType() == BaseType::B_INT ? int32PointerType : floatPointerType, param_ptr,  nullptr, true);
                    va_list.push_back(new VarNode(F_param -> getType(), F_param -> getIdentifier(), true, false, F_param -> getType() == BaseType::B_FLOAT, param_ptr, dims, true));
                } 
                else {
                    auto fi = getConstExpValue(_dims[1], true);
                    auto base = make_shared<PointerType>(func_def->getFuncFParams()->getFuncFParam()[i]->getType() == BaseType::B_INT ? i32Type : floatType, fi -> getIntVal());
                    for (int i=2;i < _dims.size();i++) base = make_shared<PointerType>(base, getConstExpValue(_dims[i], true) -> getIntVal());
                    param_ptr = builder.createAllocaInst(F_param -> getIdentifier()+".addr", base, nullptr, true);
                    auto tmp = builder.createStoreInst(&params[i], param_ptr);
                    param_ptr = builder.createLoadInst(F_param -> getIdentifier(), base, param_ptr,  nullptr, true);
                    va_list.push_back(new VarNode(F_param -> getType(), F_param -> getIdentifier(), true, false, F_param -> getType() == BaseType::B_FLOAT, param_ptr, dims, true));
                }
            }
            
            // TODO: 处理形参数组
        }
        sym_tb.add_func(func_def -> getIdentifier(), func_def -> getReturnType(), func_def -> getFuncFParams(), func);
    }
    else {
        // 无参数函数
        auto ret_ty = func_def->getReturnType() == BaseType::B_INT ? i32Type : func_def->getReturnType() == BaseType::B_FLOAT ? floatType : voidType;
        func = builder.createFunction(func_def -> getIdentifier(), ret_ty, Zero_Argu_Type_List);

        BBlock* func_entry = builder.createBBlock("entry", voidType, func);
        func -> setEntry(func_entry);
        sym_tb.add_func(func_def -> getIdentifier(), func_def -> getReturnType(), func_def -> getFuncFParams(), func);
    }
    
    // 解析函数体
    if (va_list.size() == 0) parseBlock(func_def -> getFuncBlock());
    else parseBlock(func_def -> getFuncBlock(), &va_list);

    auto last_block = builder.getChosedBBlk();
    if (last_block -> getInstCnt() == 0) {
        if (func_def -> getReturnType() == BaseType::B_VOID) builder.createRetInst(&voidValue);
        else if (func_def -> getReturnType() == BaseType::B_INT) builder.createRetInst(new ConstIntValue(0));
        else builder.createRetInst(new ConstFloatValue(0.0));
    }
    defs -> push_back(func);
    
} 

void parseCompUnit(CompUnitPtr rt){
    auto items = rt -> getDecl();

    sym_tb.enter_block();
    for (auto item: items) {

        if (item -> _node_type == NodeType::NT_FUNC) parseFuncDefine(dynamic_pointer_cast<FuncDef>(item));
        else parseDecl(dynamic_pointer_cast<Decl>(item), true);
    }
    sym_tb.exit_block();
}


Module* initialize(IRBuilder &builder) {
//   putch = builder.createFunction("putch", voidType, putch_arguTypes);
//   putint = builder.createFunction("putint", voidType, putint_arguTypes);
//   getch = builder.createFunction("getch", i32Type, Zero_Argu_Type_List);
//   getint = builder.createFunction("getint", i32Type, Zero_Argu_Type_List);              // getint 为零参函数，使用全局零参空向量，见 Config.cpp
//   memset_ = builder.createFunction("myMemset", voidType, memset_arguTypes);
//   putch_arguTypes.push_back(i32Type);
//   putint_arguTypes.push_back(i32Type);
//   memset_arguTypes.push_back(std::make_shared<PointerType>(i32Type));  
//   memset_arguTypes.push_back(i32Type);  
//   memset_arguTypes.push_back(i32Type); 

    auto void_f = nullptr;
    auto int_f = FuncFParamsPtr(new FuncFParams());
    int_f -> addFuncFParam(FuncFParamPtr (new FuncFParam(BaseType::B_INT, "i", false, nullptr)));
    auto float_f = FuncFParamsPtr(new FuncFParams());
    float_f -> addFuncFParam(FuncFParamPtr (new FuncFParam(BaseType::B_FLOAT, "f", false, nullptr)));

    auto i32_iptr = FuncFParamsPtr(new FuncFParams());
    i32_iptr -> addFuncFParam(FuncFParamPtr (new FuncFParam(BaseType::B_INT, "i", false, nullptr)));
    i32_iptr -> addFuncFParam(FuncFParamPtr (new FuncFParam(BaseType::B_INT, "i", true, nullptr)));

    auto i32_fptr = FuncFParamsPtr(new FuncFParams());
    i32_fptr -> addFuncFParam(FuncFParamPtr (new FuncFParam(BaseType::B_INT, "i", false, nullptr)));
    i32_fptr -> addFuncFParam(FuncFParamPtr (new FuncFParam(BaseType::B_FLOAT, "f", true, nullptr)));

    auto iptr = FuncFParamsPtr(new FuncFParams());
    iptr -> addFuncFParam(FuncFParamPtr (new FuncFParam(BaseType::B_INT, "i", true, nullptr)));

    auto fptr = FuncFParamsPtr(new FuncFParams());
    fptr -> addFuncFParam(FuncFParamPtr (new FuncFParam(BaseType::B_FLOAT, "f", true, nullptr)));

  // 初始化一个 Module
    auto ret = builder.createModule("start", voidType);
    globals = ret->getGlobalVars();
    defs = ret->getFuncDefs();
    declares = ret->getFuncDeclares();

  // 添加库函数到符号表
    for (auto decl : *declares) {
        if (decl -> getName() == "putch" || decl -> getName() == "putint" || decl -> getName() == "_sysy_starttime" || decl -> getName() == "_sysy_stoptime") sym_tb.add_func(decl -> getName(), decl -> getType() == i32Type ? BaseType::B_INT : decl -> getType() == floatType ? BaseType::B_FLOAT : BaseType::B_VOID, int_f, decl);
        else if (decl -> getName() == "getch" || decl -> getName() == "getint" || decl -> getName() == "getfloat" || decl -> getName() == "before_main" || decl -> getName() == "after_main") sym_tb.add_func(decl -> getName(), decl -> getType() == i32Type ? BaseType::B_INT : decl -> getType() == floatType ? BaseType::B_FLOAT : BaseType::B_VOID, void_f, decl);
        else if (decl -> getName() == "putfloat") sym_tb.add_func(decl -> getName(), decl -> getType() == i32Type ? BaseType::B_INT : decl -> getType() == floatType ? BaseType::B_FLOAT : BaseType::B_VOID, float_f, decl);
        else if (decl -> getName() == "putarray") sym_tb.add_func(decl -> getName(), decl -> getType() == i32Type ? BaseType::B_INT : decl -> getType() == floatType ? BaseType::B_FLOAT : BaseType::B_VOID, i32_iptr, decl);
        else if (decl -> getName() == "putfarray") sym_tb.add_func(decl -> getName(), decl -> getType() == i32Type ? BaseType::B_INT : decl -> getType() == floatType ? BaseType::B_FLOAT : BaseType::B_VOID, i32_fptr, decl);
        else if (decl -> getName() == "getarray") sym_tb.add_func(decl -> getName(), decl -> getType() == i32Type ? BaseType::B_INT : decl -> getType() == floatType ? BaseType::B_FLOAT : BaseType::B_VOID, iptr, decl);
        else if (decl -> getName() == "getfarray") sym_tb.add_func(decl -> getName(), decl -> getType() == i32Type ? BaseType::B_INT : decl -> getType() == floatType ? BaseType::B_FLOAT : BaseType::B_VOID, fptr, decl);
        
    }
    return ret;
}

void checkPosValid(vector<int> &pos, vector<int> dims) {
    bool flg = true;
    while (flg) {
        flg = false;
        for (int i = 1; i < pos.size(); i++) {
            if (pos[i] >= dims[i]) {
                pos[i-1]++;
                pos[i]=0;
                flg = true;
                break;
            }
        }
    }
}

void parseArrayInitVal(ArrayInitValPtr arr_init, vector<int> &pos, vector<int> dims, int depth, Instruction* array_base, bool is_float, bool is_const) {
    if (depth >= pos.size()) {
        error_msg = "数组初始化错误";
        error_handle();
        return;
    }
    if (arr_init -> getDimVal() == nullptr) {
        cout<< "初始化为0"  << endl;
        return;
    }
    // 是否解析完了所有表达式
    bool fin_flg=false;
    for (int i=0; i< arr_init -> getDimVal() -> getInitVal().size();) {
        auto dim = arr_init -> getDimVal() -> getInitVal()[i];
        auto cur_ty = dim -> getType();
        while (dim -> getType() == cur_ty) {
            if (cur_ty != ExpType::ET_DIM) {
                checkPosValid(pos, dims);
                Instruction* cur_base = array_base;
                for (int ii=0;ii<=pos.size()-1;ii++) cur_base = builder.createGEPInst(cur_base, new ConstIntValue(pos[ii]));
                if (is_const) {
                    if (is_float) builder.createStoreInst( new ConstFloatValue(getConstExpValue(dim) -> getFloatVal()), cur_base);
                    else builder.createStoreInst( new ConstIntValue(getConstExpValue(dim) -> getIntVal()), cur_base);
                }
                else {
                    auto exp = parseExp(dim, false, true, false).first;
                    if (is_float && dim -> getResType() == BaseType::B_INT) exp = builder.createInt2FpInst(exp);
                    else if (!is_float && dim -> getResType() == BaseType::B_FLOAT) exp = builder.createFp2IntInst(exp);
                    builder.createStoreInst(exp, cur_base);
                }
                pos[pos.size()-1]++;
                
            }
            else{
                parseArrayInitVal(dynamic_pointer_cast<ArrayInitVal>(dim), pos, dims, depth + 1, array_base, is_float, is_const);
                pos[depth]++;
                for (int j = depth + 1; j < pos.size(); j++) pos[j] = 0;
            }
            if (i == arr_init -> getDimVal() -> getInitVal().size() - 1){
                fin_flg=true;
                break;
            }
            dim = arr_init -> getDimVal() -> getInitVal()[++i];
        }
        if (i == arr_init -> getDimVal() -> getInitVal().size() - 1 && fin_flg) break;
        if (cur_ty != ExpType::ET_DIM) {
            pos[depth]++;
            for (int j = depth + 1; j < pos.size(); j++) pos[j] = 0;
        }
    }
}


void parseArrayInitVal(ArrayInitValPtr arr_init, vector<int> &pos, vector<int> dims, int depth, bool is_float, map<vector<int>, NumberPtr>& arr_val_mp) {
    if (depth >= pos.size()) {
        error_msg = "数组初始化错误";
        error_handle();
        return;
    }
    if (arr_init -> getDimVal() == nullptr) {
        cout<< "初始化为0"  << endl;
        return;
    }
    // 是否解析完了所有表达式
    bool fin_flg=false;
    for (int i=0; i< arr_init -> getDimVal() -> getInitVal().size();) {
        auto dim = arr_init -> getDimVal() -> getInitVal()[i];
        auto cur_ty = dim -> getType();
        while (dim -> getType() == cur_ty) {
            if (cur_ty != ExpType::ET_DIM) {
                checkPosValid(pos, dims);
                if (is_float) {
                    auto num = getConstExpValue(dim);
                    arr_val_mp[pos] = num;
                }
                else {
                    auto num = getConstExpValue(dim);
                    arr_val_mp[pos] = num;
                }
                pos[pos.size()-1]++;
            }
            else{
                parseArrayInitVal(dynamic_pointer_cast<ArrayInitVal>(dim), pos, dims, depth + 1, is_float, arr_val_mp);
                pos[depth]++;
                for (int j = depth + 1; j < pos.size(); j++) pos[j] = 0;
            }
            if (i == arr_init -> getDimVal() -> getInitVal().size() - 1){
                fin_flg=true;
                break;
            }
            dim = arr_init -> getDimVal() -> getInitVal()[++i];
        }
        if (i == arr_init -> getDimVal() -> getInitVal().size() - 1 && fin_flg) break;
        if (cur_ty != ExpType::ET_DIM) {
            pos[depth]++;
            for (int j = depth + 1; j < pos.size(); j++) pos[j] = 0;
        }
    }
}



void arrayDebug(DeclPtr decl,int offset =0 ) {
    auto var_decl = decl -> getConstDecl();
    auto var_defs = var_decl -> getConstDef() -> getConstDef();
    for (auto var_def : var_defs) {
        if (var_def -> isArray() == false) exit(0);
        auto arrayDim = var_def -> getArrayDim() -> getDim();
        cout<< "解析维度信息: "  << endl;
        vector<int>dims;vector<int>pos;
        for (auto dim : arrayDim) {
            cout<< getConstExpValue(dim -> getExp(), true) -> getIntVal() << " ";
            dims.push_back(getConstExpValue(dim -> getExp(), true) -> getIntVal());
        }
        cout<< endl;
        pos.resize(dims.size());
        map<vector<int>, NumberPtr> arr_val_mp;
        parseArrayInitVal(var_def -> getArrayInitVal(), pos, dims, 0, var_decl -> getType() == B_FLOAT, arr_val_mp);
        for (auto it: arr_val_mp) {
            for (int i:it.first) cout<<i<<" ";
            cout<<": ";
            cout<< it.second -> getIntVal() << endl;
        }

        auto alloc = parseGlobalArray(var_def -> getIdentifier(), dims, pos, 0, arr_val_mp, var_decl -> getType() == B_FLOAT);
    }
}

int main(int argc, char* argv[]){
    ++ argv;
    if (argc > 0) {
        module = initialize(builder);
        auto rt = parse(argv[0]);
        parseCompUnit(CompUnitPtr(rt));
        // arrayDebug(dynamic_pointer_cast<Decl>(CompUnitPtr(rt)->getDecl()[0]));
        // cout<< "解析完毕"  << endl;
        builder.emitIRModule(module);
        builder.close();
        return 0;
    }
    else {
        printf("No input file\n");
        return 0;
    }
}
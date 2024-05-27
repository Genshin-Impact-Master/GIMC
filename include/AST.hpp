
#ifndef _AST_HPP
#define _AST_HPP  
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include "Define.hpp"
// #include "Token.hpp"

enum BaseType {
    B_VOID,B_INT,B_FLOAT
};
enum StmtType {
    ST_IF,ST_WHILE,ST_BREAK,ST_CONTINUE,ST_RETURN,ST_EXP
};

using namespace std;
class BaseNode;
class CompUnit;
class Decl;
class ConstDecl;
class VarDecl;
class ConstDef;
class ConstInitVal;
class VarDef;
class VarDefs;
class InitVal;
class FuncDef;
class FuncFParams;
class FuncFParam;
class Block;
class BlockItem;
class Stmt;
class Exp;
class Cond;
class LVal;
class PrimaryExp;
class Number;
class UnaryExp;
class UnaryOp;
class FuncRParams;
class MulExp;
class AddExp;
class RelExp;
class EqExp;
class LAndExp;
class LOrExp;
class ConstExp;
class BlockItems;
class ConstDefs;
class ConstArrayInitVal;
class ArrayDim;
class ConstInitVals;
class ArrayInitVal;
class InitVals;
class ParamArrayDim;

class Visitor;


#define CompUnitPtr shared_ptr<CompUnit>
#define DeclPtr shared_ptr<Decl>
#define ConstDeclPtr shared_ptr<ConstDecl>
#define VarDeclPtr shared_ptr<VarDecl>
#define ConstDeclPtr shared_ptr<ConstDecl>
#define ConstDefPtr shared_ptr<ConstDef>
#define ConstInitValPtr shared_ptr<ConstInitVal>
#define VarDefPtr shared_ptr<VarDef>
#define InitValPtr shared_ptr<InitVal>
#define FuncDefPtr shared_ptr<FuncDef>
#define FuncFParamsPtr shared_ptr<FuncFParams>
#define FuncFParamPtr shared_ptr<FuncFParam>
#define BlockPtr shared_ptr<Block>
#define BlockItemPtr shared_ptr<BlockItem>
#define StmtPtr shared_ptr<Stmt>
#define ExpPtr shared_ptr<Exp>
#define CondPtr shared_ptr<Cond>
#define LValPtr shared_ptr<LVal>
#define PrimaryExpPtr shared_ptr<PrimaryExp>
#define NumberPtr shared_ptr<Number>
#define UnaryOpPtr shared_ptr<UnaryOp>
#define FuncRParamsPtr shared_ptr<FuncRParams>
#define MulExpPtr shared_ptr<MulExp>
#define AddExpPtr shared_ptr<AddExp>
#define RelExpPtr shared_ptr<RelExp>
#define EqExpPtr shared_ptr<EqExp>
#define LAndExpPtr shared_ptr<LAndExp>
#define LOrExpPtr shared_ptr<LOrExp>
#define ConstExpPtr shared_ptr<ConstExp>
#define BlockItemsPtr shared_ptr<BlockItems>
#define ConstDefsPtr shared_ptr<ConstDefs>
#define ConstArrayInitValPtr shared_ptr<ConstArrayInitVal>
#define ArrayDimPtr shared_ptr<ArrayDim>
#define ConstInitValsPtr shared_ptr<ConstInitVals>
#define VarDefsPtr shared_ptr<VarDefs>
#define InitValsPtr shared_ptr<InitVals>
#define ArrayInitValPtr shared_ptr<ArrayInitVal>
#define ParamArrayDimPtr shared_ptr<ParamArrayDim>

class BaseNode {
public:
    BaseNode(){};
    ~BaseNode(){};
    void traverse(Visitor vis);

};

class CompUnit {
private:
    vector<DeclPtr> _decls;
    vector<FuncDefPtr> _func_defs;
public:
    void addDecl (DeclPtr decl){_decls.pb(decl);};
    void addFuncDef (FuncDefPtr fun_def){_func_defs.pb(fun_def);};
    vector<DeclPtr> getDecl(){return _decls;};
    vector<FuncDefPtr> getFuncDef(){return _func_defs;};
};

class Decl {
private:
    ConstDeclPtr _const_decl;
    VarDeclPtr _var_decl;
    bool _const;
public:
    void addConstDecl (ConstDeclPtr const_decl){_const_decl=const_decl;_const=true;};
    void addVarDecl (VarDeclPtr var_decl){_var_decl=var_decl;_const=false;};
    bool isConst(){return _const;}
    ConstDeclPtr getConstDecl(){return _const_decl;};
    VarDeclPtr getVarDecl(){return _var_decl;};
};

class ConstDecl {
private:
    ConstDefsPtr _const_defs;
    BaseType _type;
public:
    void addConstDef(ConstDefsPtr const_defs){_const_defs=const_defs;};
    void addType(BaseType type){_type=type;};
    ConstDefsPtr getConstDef(){return _const_defs;};
    BaseType getType(){return _type;};
};

class ConstDef {
private:
    string _identifier;
    ConstExpPtr _init_val;
    bool _array;
    ArrayDimPtr _array_dim;
    ConstArrayInitValPtr _array_init_val;
public:
    void addIdentifier(string* identity){_identifier=(*identity);}
    bool isArray(){return _array;};
    void addArray(bool array){_array=array;}
    void addArrayDim(ArrayDimPtr array_dim){_array_dim=array_dim;};
    void addInitVal(ConstExpPtr init_val){_init_val=init_val;};
    ArrayDimPtr getArrayDim(){return _array_dim;};
    ConstExpPtr getInitVal(){return _init_val;};
    string getIdentifier(){return _identifier;}; 
    void addArrayInitVal(ConstArrayInitValPtr array_init_val){_array_init_val=array_init_val;}
    ConstArrayInitValPtr getArrayInitVal(){return _array_init_val;};
};

class ArrayDim {
private:
    vector<ConstExpPtr> _dims;
public:
    void addDim(ConstExpPtr dim){_dims.pb(dim);};
    vector<ConstExpPtr> getDim(){return _dims;};
};

class ConstDefs {
private:
    vector<ConstDefPtr> _const_defs;
public:
    void addConstDef(ConstDefPtr const_def){_const_defs.pb(const_def);};
    vector<ConstDefPtr> getConstDef(){return _const_defs;};   
};

class ConstInitVals {
private: 
    vector<ConstExpPtr> _const_init_vals;
public:
    vector<ConstExpPtr> getConstInitVal(){return _const_init_vals;};
    void addConstExp(ConstExpPtr const_exp){_const_init_vals.pb(const_exp);}; 
};

class ConstArrayInitVal {
private:
    vector<ConstInitValsPtr> _dim_vals;
public:
    void addDimVal (ConstInitValsPtr dim_val){_dim_vals.pb(dim_val);}
    vector<ConstInitValsPtr> getDimVal(){return _dim_vals;}
};

class VarDecl {
private:
    BaseType _type;
    VarDefsPtr _var_defs;
public: 
    void addType(BaseType type){_type=type;}
    BaseType getType(){return _type;}
    void addVarDefs(VarDefsPtr var_defs){_var_defs=var_defs;}
    VarDefsPtr getVarDefs(){return _var_defs;}
};

class VarDef {
private:
    string _identifier;
    bool _is_init;
    bool _is_array;
    ArrayDimPtr _array_dim;
    ExpPtr _init_val;
    ArrayInitValPtr _array_init_val;
public:
    bool isArray(){return _is_array;}
    void addArrayDim(ArrayDimPtr array_dim){_array_dim=array_dim;}
    void addInitVal(ExpPtr init_val){_init_val=init_val;}
    void addArray(bool array){_is_array=array;}
    void addIdentifier(string* id){_identifier=*id;}
    void addArrayInitVal(ArrayInitValPtr array_init_val){_array_init_val=array_init_val;}
    void addInit(bool is_init){_is_init=is_init;}
    
    ArrayDimPtr getArrayDim(){return _array_dim;}
    ExpPtr getInitVal(){return _init_val;}
    string getIdentifier(){return _identifier;}
    ArrayInitValPtr getArrayInitVal(){return _array_init_val;}
    
};

class InitVals {
private:
    vector<ExpPtr> _exps;
public:
    void addExp(ExpPtr exp) {_exps.pb(exp);}
    vector<ExpPtr> getInitVal() {return _exps;}
};

class ArrayInitVal{
private:
    vector<InitValsPtr> _dim_vals;
public:
    void addDimVal(InitValsPtr dim_val) {_dim_vals.pb(dim_val);}
    vector<InitValsPtr> getDimVal() {return _dim_vals;}
};

class VarDefs {
private:
    vector<VarDefPtr> _var_defs;
public:
    void addVarDef(VarDefPtr var_def) {_var_defs.pb(var_def);}
    vector<VarDefPtr> getVarDef() {return _var_defs;}
};

class FuncDef {
private:
    BaseType _return_type;
    string _identifier;
    bool _has_param;
    FuncFParamsPtr _func_params;
    BlockPtr _block;
public:
    void addReturnType(BaseType type){_return_type=type;}
    void addIdentifier(string* id){_identifier=*id;}
    void addParam(bool has_param){_has_param=has_param;}
    void addFuncFParams(FuncFParamsPtr func_params){_func_params=func_params;}
    void addBlock(BlockPtr block){_block=block;}
    BaseType getReturnType(){return _return_type;}
    string getIdentifier(){return _identifier;}
    FuncFParamsPtr getFuncFParams(){return _func_params;}
    BlockPtr getFuncBlock() {return _block;}
};

class FuncFParams {
private:
    vector<FuncFParamPtr> _func_f_params;
public:
    void addFuncFParam(FuncFParamPtr func_f_param) {_func_f_params.pb(func_f_param);}
    vector<FuncFParamPtr> getFuncFParam() {return _func_f_params;}
};
class FuncFParam {
private:
    BaseType _type;
    string _identifier;
    bool _is_array;
    ParamArrayDimPtr _dims;
public:
    void addType(BaseType type){_type=type;}
    void addArray(bool is_array){_is_array=is_array;}
    void addArrayDim(ParamArrayDimPtr dims) {_dims=dims;}
    void addIdentifier(string* id){_identifier=*id;}
    BaseType getType(){return _type;}
    string getIdentifier(){return _identifier;}
    bool isArray(){return _is_array;}
    ParamArrayDimPtr getArrayDim(){return _dims;}
};

class ParamArrayDim {
private:
    vector<ExpPtr> _dims;
public:
    void addDim(ExpPtr dim) {_dims.pb(dim);}
    vector<ExpPtr> getDim() {return _dims;}
};

class BlockItem {
private:
    vector<StmtPtr> _stmts;
    vector<DeclPtr> _decls;
public:
    void addStmt(StmtPtr stmt) {_stmts.pb(stmt);}
    vector<StmtPtr> getStmt() {return _stmts;}  
    void addDecl(DeclPtr decl) {_decls.pb(decl);}
    vector<DeclPtr> getDecl() {return _decls;}
};
class Block {
private:
    BlockItemPtr _block_items;
public:
    void addBlockItem(BlockItemPtr block_items) {_block_items = block_items;}
    BlockItemPtr getBlockItem() {return _block_items;}
};

class Stmt {
    StmtType _type;  
};
class ConstExp {

};
class Exp {

};
#endif
#include "AST.hpp"

void CompUnit::dump(std::ostream& out, size_t n){
    out<< "CompUnit: \n";
    for (auto &decl: _decls) decl->dump(out,n+1);
    for (auto &func: _funcs) func->dump(out,n+1);
}

void ConstDecl::dump(std::ostream& out, size_t n){
    out<< "ConstDecl: BType " << _type << std::endl;
    for (auto &def: _defs) def->dump(out,n+1);
}

void VarDecl::dump(std::ostream& out, size_t n){
    out<< "VarDecl: BType " << _type << std::endl;
    for (auto &def: _defs) def->dump(out,n+1);
}

void FuncDef::setScope(){}

void FuncDef::dump(std::ostream& out, size_t n){
    
}
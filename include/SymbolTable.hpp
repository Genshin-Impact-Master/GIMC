#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include "AST.hpp"
#include "IRBuilder.h"

struct VarNode {
    BaseType _type;
    string _identifier;
    bool _is_array;
    bool _is_float;
    bool _is_const;
    Value* _inst;
    VarNode(BaseType type, string identifier, bool is_array,  bool is_const, bool is_float, Value* inst):
        _type(type), _identifier(identifier), _is_array(is_array), _is_const(is_const), _is_float(is_float), _inst(inst) {}
};
struct FuncNode {
    BaseType _ret_type;
    string _identifier;
    FuncFParamsPtr _func_params;
    Function* _entry;
    
    FuncNode(BaseType ret_type, string identifier, FuncFParamsPtr func_params, Function* entry):
        _ret_type(ret_type), _identifier(identifier), _func_params(func_params), _entry(entry) {}
};

struct SymbolTable {
    list<unordered_map<string, VarNode*>> _var_list;
    unordered_map<string, FuncNode*> _func_mp;
    SymbolTable() {
        _var_list = list<unordered_map<string, VarNode*>>();
        _func_mp = unordered_map<string, FuncNode*>();
    }
    void enter_block() {
        _var_list.push_front(unordered_map<string, VarNode*>());
    }
    void add_func(string identifier, BaseType ret_type, FuncFParamsPtr func_params, Function* entry) {
        _func_mp[identifier] = new FuncNode(ret_type, identifier, func_params, entry);
    }
    void add_var(string identifier, BaseType type, bool is_array, bool is_const, bool is_float, Value* _inst) {
        _var_list.front().insert(pair<string, VarNode*>(identifier, new VarNode(type, identifier, is_array, is_const, is_float, _inst)));
        
    }
    VarNode* find_var(string identifier){
        for (auto mp: _var_list) 
            if (mp.find(identifier) != mp.end()) return mp[identifier];
    }
    
    FuncNode* find_func(string identifier) {return _func_mp[identifier];}
    bool check_var(string identifier) {
        for (auto mp: _var_list) 
            if (mp.find(identifier) != mp.end()) return true;
        return false;
    }

    bool check_var_current_bk(string identifier) {
        return _var_list.front().find(identifier) != _var_list.front().end();
    }
    
    bool check_func(string identifier) {return _func_mp.find(identifier) != _func_mp.end();}
};
#endif

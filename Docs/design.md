# 1. 词法分析
## 1.1 词法分析整体框架说明
为了方便后续抽象语法树（AST）的生成，我们使用flex和bison进行编译器前端的处理，包括词法分析和语法分析
## 1.2 Token说明
+ 基本类型: ```int```, ```void```, ```float```
+ 关键字: ```if```, ```else```, ```while```, ```continue```, ```break```, ```return```, ```const```
+ 特殊符号: ```{}```, ```;```
+ 操作符: ```()```, ```[]```, ```!```, ```-```, ```+```, ```-```, ```*```, ```/```, ```%```, ```+```, ```-```, ```<```,
```<=```, ```>```, ```>=```, ```==```, ```!=```, ```&&```, ```||```, ```=```, ```,```  
上述Token在flex中的定义如下:
```c
"+"         return ADD;
"*"         return MUL;
"-"         return SUB;
"/"         return DIV;
"%"         return MOD;

"if"        return IF;
"else"      return ELSE;
"while"     return WHILE;
"break"     return BREAK;
"continue"  return CONTINUE;
"return"    return RETURN;

"const"     return CONST;
"int"       return INT;
"float"     return FLOAT;
"void"      return VOID;
"="         return ASSIGN;
"=="        return EQ;
"!="        return NEQ;

">"         return GT;
">="        return GTE;
"<"         return LT;
"<="        return LTE;

"&&"        return AND;
"||"        return OR;
"!"         return NOT;

"("         return LEFT_PARENTHESES;
")"         return RIGHT_PARENTHESES;
"["         return LEFT_BRACKETS;
"]"         return RIGHT_BRACKETS;
"{"         return LEFT_BRACES;
"}"         return RIGHT_BRACES;

","         return COMMA;
";"         return SEMICOLON;
```
## 1.3 正则表达式说明
为了实现对SysY语言中```Ident```, ```IntConst```, ```floatConst```等的识别，我们可以在flex中定义如下正则表达式: 
```c
// IntConst 和 floatConst 的识别
DIGIT [0-9]
NONZERO_DIGIT [1-9]
HEX_PREFIX (0x)|(0X)
HEX_DIGIT [0-9a-fA-F]
OCT_PREFIX 0
OCT_DIGIT [0-7]
DEC_INTEGER ({NONZERO_DIGIT}{DIGIT}*|0)
OCT_INTEGER {OCT_PREFIX}{OCT_DIGIT}+
HEX_INTEGER {HEX_PREFIX}{HEX_DIGIT}+
DEC_FLOAT_VALUE [0-9]*\.[0-9]*
HEX_FLOAT_VALUE ((0x)|(0X))[0-9a-zA-Z]*"."[0-9a-zA-Z]+(([+-]){DIGIT}+)?
E_FLOAT_VALUE   ({DIGIT}\.|\.|\.|{DIGIT})+[eE](([+-])?{DIGIT}+)?

// Ident
LETTER [a-zA-Z]
TOKEN_IDENTIFIER ({LETTER}|_)({DIGIT}|{LETTER}|_)*

// SysY中的注释
\/\/.*      ; // 单行注释
"/*"        {
                int c;
                while ((c=yyinput())!=0){
                    if (c=='\n') yylineno++;
                    else if (c=='*'){
                        if ((c=yyinput())=='/') break;
                        else unput(c);
                    }
                }
            } //多行注释
```
## 1.4 词法分析器的输出
词法分析器会将输入的文件按照在flex中义规则进行**最长匹配**，最后输出是一系列的```tokens```，每一个```token```都包含token的类型（如关键字、标识符、字面量等）和token的值（如IntConst和floatConst），这些token将被传递给语法分析器，进行AST的构建，在SysY语言编译器的设计中，词法分析器是构建整个编译器的重要基石之一，它的正确性和效率对后续步骤有着直接的影响。

# 2. 语法分析
## 2.1 SysY语法分析器框架
在SysY语法的基础上使用**bison**对**flex**输出的```token```进行AST的构建以及语法错误的识别
## 2.2 SysY语法的改造
由于SysY的语法官方给的文法是**EBNF**（Extend Backus-Naur Form）范式，对于我们所使用的bison语法分析器而言并不能识别，因此我们需要将SysY的部分语法改造成**BNF**（Backus-Naur Form）  
改造主要集中在两个方面:  
+ 对于EBNF的**可选项**，我们可以将其展开为不选和必选两种语法，例如:
```c
CompUnit -> [CompUnit] (Decl | FuncDef)
//可以展开为
CompUnit → CompUnit Decl | CompUnit FuncDef | Decl | FuncDef
```
+ 对于EBNF中的**可重复0次或者多次**的部分，我们可以通过增加一个左递归的产生式来改造，例如:
```c
ConstDecl -> 'const' BType ConstDef {',' ConstDef} ';'
// 增加一个左递归项 ConstDefs
ConstDefs -> ConstDef | ConstDefs ',' ConstDef
ConstDecl -> 'const' BType ConstDefs ';'
```
通过上述方式，我们便可以将所有EBNF语法转换成BNF语法，完成bison语法分析器的规则部分

## 2.3 抽象语法树（AST）的设计
我们为所有非终结符的语法符号设计了对应的AST节点，例如```CompUnit```对应的AST节点:
```c++
class CompUnit {
private:
    vector<BaseNodePtr> _decls;
public:
    void addDecl (DeclPtr decl){_decls.push_back(dynamic_pointer_cast<BaseNode>(decl));};
    void addFuncDef (FuncDefPtr fun_def){_decls.push_back(dynamic_pointer_cast<BaseNode>(fun_def));};
    vector<BaseNodePtr> getDecl(){return _decls;};
};
```
+ 这样设计的主要问题在于解决有**多种不同的派生语法**且需要区分**子节点派生顺序**的情况  
例如 ```CompUnit``` 可以派生出 ```Decl``` 和 ```FuncDef``` 两种不同的非终结符号，且在后续的语义分析中我们需要```Decl```和```FuncDef```的派生顺序，我们可以使 ```Decl``` 和 ```FuncDef``` 继承同一个基类，并在基类设置token用于区别二者
```c++
class BaseNode {
public:
    BaseNode(){};
    virtual ~BaseNode() = default;
    // _node_type 用于区别 Decl 和 FuncDef
    NodeType _node_type;
};
class Decl: public BaseNode, public ErrorInfo {...};
class FuncDef: public BaseNode, public ErrorInfo {...};

```
最后我们在bison的规则部分为一个产生式增加对应的AST构建代码即可

# 3. 语义分析
## 3.1 符号表的设计
符号表是语义分析的核心数据结构，为此我们针对**函数**和**变量**设计了两种数据结构  
+ 变量的数据结构如下:
```c++
struct VarNode {
    // 变量类型和变量名
    BaseType _type;
    string _identifier;
    // 判断变量类型
    bool _is_array;
    bool _is_float;
    bool _is_const;
    bool _is_param;
    // 对于常量且非数组，存储其值
    int _const_int;
    float _const_float;
    // 对于数组，存储其维度信息
    vector<int> _dims;
    // IR中变量的指针地址
    Value* _inst;
}
```
+ 函数的数据结构如下
```c++
struct FuncNode {
    // 函数返回值类型和函数名
    BaseType _ret_type;
    string _identifier;
    // 函数形参信息
    FuncFParamsPtr _func_params;
    // IR中函数调用的入口
    Function* _entry;
}
```
符号表需要支持根据变量或者函数名获取对应节点信息的功能，对此我们可以利用 ```unordered_map<string, VarNode*>``` 和```unordered_map<string, FuncNode*>``` 来实现，同时考虑到变量有**作用域**的限制，我们结合 ```list``` 实现了该功能，因此最终符号表的实现如下:
```c++
struct SymbolTable {
    list<unordered_map<string, VarNode*>> _var_list;
    unordered_map<string, FuncNode*> _func_mp;
}
```
通过符号表，我们实现了以下语义检查:
| | reason | info |
| --------- | ---------------------------------------------- | ------------------------------------------------------------ |
| 1         | 函数不能在常量表达式中调用                     | 不支持的常量表达式 |
| 2         | 数组的维度必须是正数                           | 数组维度不能小于等于0   |
| 3         | 数组的维度必须是整形                           | 数组下标必须为整数  |
| 4        | 声明数值变量，初始化类型是数组                 | syntax error    |
| 5         | 声明数组变量，初始化类型是数值                 | syntax error           |
| 6         | 变量还未声明                                   | 变量 ```Ident``` 未定义       |
| 7         | 数组变量初始化，大括号嵌套层数超过数组维数     | 数组初始化错误                    |
| 8         | 需要是const的地方类型不是const                 |  需要常量表达式                     |
| 9        | 数组变量初始化，同一维度元素数量超过限制       | 数组初始化数量太多                       |
| 10        | 变量/常量/函数重复定义                         | 变量/函数 ```Ident``` 重复定义    |
| 11        | continue或者break语句不在循环体内              | break/continue不在循环体内            |
| 12        | bool表达式只能出现在条件中                        | 布尔值表达式不支持  |
| 13        | 函数实参和函数形参类型不一致                   | 调用函数 ```Ident``` 时，传递参数错误 |
| 14        | 变量类型/函数声明时的形参类型不能是void          | syntax error                       |
| 15        | return类型和函数返回类型对不上                 | 函数返回值错误 |
| 16    | 左值作为赋值语句调用，数组类型必须取到一个元素    | 数组 ```Ident``` 一共有 ```...``` 个维度，但只给了 ```...``` 个下标  |
| 17        | 函数调用时参数过多  | 调用函数 ```Ident``` 时，传递参数太多|
| 18        | 函数调用时未定义              |     函数 ```Ident``` 未定义             |
| 19        | 函数调用时缺少参数         | 调用函数 ```Ident``` 时，传递参数太少              |  
| 20        | 取模运算中有浮点数                             | 浮点数取模操作不支持    |  
| 21        |  表达式中函数调用返回void                           | 函数 ```Ident``` 无返回值   |  
检测到语义错误时，除了上述错误信息的输出，还会输出对应的**行列信息**
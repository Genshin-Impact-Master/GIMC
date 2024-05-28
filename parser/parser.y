
/* %skeleton "lalr1.cc" */

%{
    #include "../include/AST.hpp"
    #define m_s make_shared
    // #include <cstdio>
    extern int yylex(void);
    extern void yyerror(const char *s);
    extern FILE *yyin;
%}
/* %option c++ */

%union{
    
    CompUnit* compUnit;
    Decl* decl;
    ConstDecl* constDecl; 
    VarDecl* varDecl;
    ConstDef* constDef;
    VarDef* varDef;
    VarDefs* varDefs;
    // InitVal* initVal;
    FuncDef* funcDef;
    // FuncType funcType;
    FuncFParams* funcFParams;
    FuncFParam* funcFParam;
    Block* block;
    // BlockItem* blockItem;
    Stmt* stmt;
    Exp* exp;
    Cond* cond;
    LVal* lVal;
    PrimaryExp* primaryExp;
    Number* number;
    UnaryExp* unaryExp;
    UnaryOp* unaryOp;
    FuncRParams* funcRParams;
    MulExp* mulExp;
    AddExp* addExp;
    RelExp* relExp;
    EqExp* eqExp;
    LAndExp* lAndExp;
    LOrExp* lOrExp;
    ConstExp* constExp;
    BlockItems* blockItems;
    ConstDefs* constDefs;
    ArrayDim* arrayDim;
    ConstArrayInitVal* constArrayInitVal;
    ConstInitVals* constInitVals;
    InitVals* initVals;
    ArrayInitVal* arrayInitVal;
    ParamArrayDim* paramArrayDim;
    BaseType type;
    int32_t intVal;
    float floatVal;
    string* identifier;
}

%token ADD SUB MUL DIV MOD
%token ASSIGN EQ NEQ LT LTE GT GTE
%token AND OR NOT
%token IF ELSE WHILE BREAK CONTINUE RETURN
%token CONST INT VOID FLOAT
%token LEFT_PARENTHESES RIGHT_PARENTHESES
%token LEFT_BRACKETS RIGHT_BRACKETS
%token LEFT_BRACES RIGHT_BRACES
%token COMMA SEMICOLON
%token <identifier> IDENTIFIER
%token <intVal> INTVAL
%token <floatVal> FLOATVAL

%type <paramArrayDim> ParamArrayDim
%type <arrayInitVal> ArrayInitVal
%type <initVals> InitVals
%type <constInitVals> ConstInitVals
%type <constArrayInitVal> ConstArrayInitVal
%type <arrayDim> ArrayDim
%type <constDefs> ConstDefs 
%type <blockItems> BlockItems
%type <funcFParam> FuncFParam 
%type <compUnit> CompUnit
%type <decl> Decl
%type <constDecl> ConstDecl
%type <varDecl> VarDecl
%type <constDef> ConstDef
%type <varDef> VarDef
%type <funcDef> FuncDef
%type <funcFParams> FuncFParams
%type <block> Block
%type <stmt> Stmt
%type <exp> Exp
%type <cond> Cond
%type <lVal> LVal
%type <primaryExp> PrimaryExp
%type <number> Number
%type <unaryExp> UnaryExp
%type <unaryOp> UnaryOp
%type <funcRParams> FuncRParams
%type <mulExp> MulExp
%type <addExp> AddExp
%type <relExp> RelExp
%type <eqExp> EqExp
%type <lAndExp> LAndExp
%type <lOrExp> LOrExp
%type <constExp> ConstExp
%type <type> BaseType
%type <varDefs> VarDefs

%left ASSIGN
%left OR AND
%left EQ NEQ
%left GTE LTE GT LT
%left ADD SUB
%left MOD MUL DIV
%right NOT


%start CompUnit


%%

CompUnit: CompUnit Decl{
        $$ = $1;
        $1 -> addDecl(DeclPtr($2));
        printf("CompUnit Decl Find\n");
    }
    | CompUnit FuncDef{
        $$ = $1;
        $1 -> addFuncDef(FuncDefPtr($2));
        printf("CompUnit FuncDef Find\n");
    }
    | Decl{
        $$ = new CompUnit();
        $$ -> addDecl(DeclPtr($1));
        printf("Decl Find\n");
    }
    | FuncDef{
        $$ = new CompUnit();
        $$ -> addFuncDef(FuncDefPtr($1));
        printf("FuncDef Find\n");
    };

Decl: ConstDecl{
        $$ = new Decl();
        $$ -> addConstDecl(ConstDeclPtr($1));
        printf("ConstDecl Find\n");
    }
    | VarDecl {
        $$ = new Decl();
        $$ -> addVarDecl(VarDeclPtr($1));
        printf("VarDecl Find\n");
    };

/* ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';' */
ConstDecl: CONST BaseType ConstDefs SEMICOLON{
        $$ = new ConstDecl();
        $$ -> addType($2);
        $$ -> addConstDef(ConstDefsPtr($3));
        printf("ConstDecl Find\n");
    };

ConstDefs: ConstDef {
        $$ = new ConstDefs();
        $$->addConstDef(ConstDefPtr($1));
        printf("ConstDefs Find\n");
    }
    | ConstDefs COMMA ConstDef {
        $$ = $1;
        $1 -> addConstDef(ConstDefPtr($3));
        printf("ConstDefs Find\n");
    };

BaseType: INT{
        $$ = BaseType::B_INT;
        printf("INT Token Find\n");
    }
    |FLOAT {
        $$ = BaseType::B_FLOAT;
        printf("FLOAT Token Find\n");
    }
    | VOID {
        $$ = BaseType::B_VOID;
        printf("VOID Token Find\n");

    };

/* ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal*/
ConstDef: IDENTIFIER ASSIGN ConstExp{
        $$ = new ConstDef();
        $$ -> addIdentifier($1);
        $$ -> addArray(false);
        $$ -> addInitVal(ConstExpPtr($3));
        printf("ConstDef Find\n");
    }
    | IDENTIFIER ArrayDim ASSIGN ConstArrayInitVal {
        $$ = new ConstDef();
        // $$ -> addIdentifier($1);
        $$ -> addArray(true);
        $$ -> addArrayDim(ArrayDimPtr($2));
        // $$ -> addArrayInitVal(ConstArrayInitValPtr($4));
        printf("ConstDef Find\n");
    };

ArrayDim: LEFT_BRACKETS ConstExp RIGHT_BRACKETS {
        $$ = new ArrayDim();
        $$ -> addDim (ConstExpPtr($2));
        printf("ArrayDim Find\n");
    }
    | ArrayDim LEFT_BRACKETS ConstExp RIGHT_BRACKETS {
        $$ = $1;
        $$ -> addDim(ConstExpPtr($3));
        printf("ArrayDim Find\n");
    };

/* ConstInitVal → ConstExp 
                | '{' [ ConstInitVal { ',' ConstInitVal } ] '}' */
/* ConstInitVal: ConstExp {

        printf("ConstInitVal Find\n");
    }; */
ConstInitVals: ConstExp {
        $$ = new ConstInitVals();
        $$ -> addConstExp(ConstExpPtr($1));
        printf("ConstInitVals Find\n");
    }
    | ConstInitVals COMMA ConstExp {
        $$ = $1;
        $$ -> addConstExp(ConstExpPtr($3));
        printf("ConstInitVals Find\n");
    };

ConstArrayInitVal: LEFT_BRACES ConstInitVals RIGHT_BRACES {
        $$ = new ConstArrayInitVal();
        $$ -> addDimVal(ConstInitValsPtr($2));
        printf("ConsttInitVal Find\n");
    }
    | LEFT_BRACES RIGHT_BRACES {
        $$ = new ConstArrayInitVal();
        $$ -> addDimVal(ConstInitValsPtr(nullptr));
        printf("ConstArrayInitVal Find\n");
    }
    | LEFT_BRACES ConstInitVals COMMA ConstArrayInitVal RIGHT_BRACES {
        $$ = new ConstArrayInitVal();
        $$ -> addDimVal(ConstInitValsPtr($2));
        auto tmp = $4 -> getDimVal();
        for (auto initvals: tmp) $$ -> addDimVal(initvals);
        delete $4;
        printf("ConstArrayInitVal Find\n");
    }
    | LEFT_BRACES ConstArrayInitVal COMMA ConstInitVals RIGHT_BRACES {
        $$ = $2;
        $2 -> addDimVal(ConstInitValsPtr($4));
        printf("ConstArrayInitVal Find\n");
    };

/* VarDecl → BType VarDef { ',' VarDef } ';' */
VarDecl: BaseType VarDefs SEMICOLON{
         $$ = new VarDecl();
         $$ -> addType($1);
         $$ -> addVarDefs(VarDefsPtr($2));
        printf("VarDecl Find\n");
    };

VarDefs: VarDef {
        $$ = new VarDefs();
        $$ -> addVarDef(VarDefPtr($1));
        printf("VarDefs Find\n");
    }
    | VarDefs COMMA VarDef {
        $$ = $1;
        $$ -> addVarDef(VarDefPtr($3)); 
        printf("VarDefs Find\n");
    };
/* VarDef → Ident { '[' ConstExp ']' }
            | Ident { '[' ConstExp ']' } '=' InitVal
*/
VarDef: IDENTIFIER {
        // cout<<*($1)<<endl;
        $$ = new VarDef();
        $$ -> addIdentifier($1);
        $$ -> addInit(false);
        $$ -> addArray(false);
        printf("VarDef Find\n");
    }
    | IDENTIFIER ASSIGN Exp{
        $$ = new VarDef();
        $$ -> addIdentifier($1);
        $$ -> addInit(true);
        $$ -> addInitVal(ExpPtr($3));
        $$ -> addArray(false);
        printf("VarDef Find\n");
    }
    | IDENTIFIER ArrayDim {
        $$ = new VarDef();
        $$ -> addIdentifier($1);
        $$ -> addArrayDim(ArrayDimPtr($2));
        $$ -> addInit(false);
        $$ -> addArray(true);
        printf("VarDef Find\n");
    }
    | IDENTIFIER ArrayDim ASSIGN ArrayInitVal{
        $$ = new VarDef();
        $$ -> addIdentifier($1);
        $$ -> addArrayDim(ArrayDimPtr($2));
        $$ -> addArrayInitVal(ArrayInitValPtr($4));
        $$ -> addInit(true);
        $$ -> addArray(true);
        printf("VarDef Find\n");
    };



/* InitVal → Exp 
            | '{' [ InitVal { ',' InitVal } ] '}' */
/* InitVal: Exp{
        printf("InitVal Find\n");
    }
    |; */

InitVals: Exp {
        $$ = new InitVals();
        $$ -> addExp(ExpPtr($1));
        printf("InitVals Find\n");  
    }
    | InitVals COMMA Exp {
        $$ = $1;
        $$ -> addExp(ExpPtr($3));
        printf("InitVals Find\n");
    };
ArrayInitVal: LEFT_BRACES InitVals RIGHT_BRACES {
        $$ = new ArrayInitVal();
        $$ -> addDimVal(InitValsPtr($2));
        printf("ArrayInitVal Find\n");
    }
    | LEFT_BRACES RIGHT_BRACES {
        $$ = new ArrayInitVal();
        $$ -> addDimVal(InitValsPtr(nullptr));
        printf("ArrayInitVal Find\n");
    }
    | LEFT_BRACES InitVals COMMA ArrayInitVal RIGHT_BRACES {
        $$ = new ArrayInitVal();
        $$ -> addDimVal(InitValsPtr($2));
        auto tmp = $4 -> getDimVal();
        for (auto initvals: tmp) $$ -> addDimVal(initvals);
        delete $4;
        printf("ArrayInitVal Find\n");
    }
    | LEFT_BRACES ArrayInitVal COMMA InitVals RIGHT_BRACES {
        $$ = $2;
        $2 -> addDimVal(InitValsPtr($4));
        printf("ArrayInitVal Find\n");
    };

 /* FuncDef → FuncType Ident '(' [FuncFParams] ')' Block */
FuncDef: BaseType IDENTIFIER LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block{
        $$ = new FuncDef();
        $$ -> addReturnType($1);
        $$ -> addIdentifier($1);
        $$ -> addParam(true);
        $$ -> addFuncFParams(FuncFParamsPtr($4));
        $$ -> addBlock(BlockPtr($7));
        printf("FuncDef Find\n");
    }
    | BaseType IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES Block{
        $$ = new FuncDef();
        $$ -> addReturnType($1);
        $$ -> addIdentifier($1);
        $$ -> addParam(false);
        $$ -> addBlock(BlockPtr($7));
        printf("FuncDef Find\n");
    };

/* FuncType → 'void' | 'int' | 'float' */

/* FuncFParams → FuncFParam { ',' FuncFParam } */
FuncFParams: FuncFParam {
        $$ = new FuncFParams();
        $$ -> addFuncFParam(FuncFParamPtr($1));
        printf("FuncFParams Find\n");
    }
    | FuncFParams COMMA FuncFParam{
        $$ = $1;
        $$ -> addFuncFParam(FuncFParamPtr($3));
        printf("FuncFParams Find\n");
    };

/* FuncFParam → BType Ident ['[' ']' { '[' Exp ']' }] */
FuncFParam: BaseType IDENTIFIER {
        $$ = new FuncFParam();
        $$ -> addType($1);
        $$ -> addIdentifier($2);
        $$ -> addArray(false);
        printf("FuncFParam Find\n");
    }
    | BaseType IDENTIFIER ParamArrayDim {
        $$ = new FuncFParam();
        $$ -> addType($1);
        $$ -> addIdentifier($2);
        $$ -> addArray(true);
        $$ -> addParamArrayDim(ParamArrayDimPtr($3));
        printf("FuncFParam Find\n");
    };

ParamArrayDim: LEFT_BRACKETS RIGHT_BRACKETS {
        $$ -> addDim(nullptr);
        printf("ParamArrayDim Find\n");
    }
    | ParamArrayDim LEFT_BRACKETS Exp RIGHT_BRACKETS {
        $$ -> addDim(ExpPtr($3));
        printf("ParamArrayDim Find\n");
    };

/* Block → '{' { BlockItem } '}' */
Block: LEFT_BRACES BlockItems RIGHT_BRACES{
        $$ = new Block();
        $$ -> addBlockItem(BlockItemPtr($2));
        printf("Block Find\n");
    };

BlockItems: Decl {
        $$ = new BlockItem();
        $$ -> addDecl(DeclPtr($1));
        printf("BlockItems Find\n");
    }
    | Stmt {
        $$ = new BlockItem();
        $$ -> addStmt(StmtPtr($1));
        printf("BlockItems Find\n");
    }
    | BlockItems Decl {
        $$ = $1;
        $$ -> addDecl(DeclPtr($2));
        printf("BlockItems Find\n");
    }
    | BlockItems Stmt {
        $$ = $1;
        $$ -> addStmt(StmtPtr($2));
        printf("BlockItems Find\n");
    }
    | BlockItems SEMICOLON {
        $$ = $1;
        printf("BlockItems Find\n");
    };

/* BlockItem → Decl | Stmt */


/* Stmt → LVal '=' Exp ';' | [Exp] ';' | Block
| 'if' '( Cond ')' Stmt [ 'else' Stmt ]
| 'while' '(' Cond ')' Stmt
| 'break' ';' | 'continue' ';'
| 'return' [Exp] ';' */
Stmt: LVal ASSIGN Exp SEMICOLON {
        
        printf("Stmt Find\n");
    }   
    | Exp {
        printf("Stmt Find\n");
    }
    | Block {
        printf("Stmt Find\n");
    }
    | IF LEFT_PARENTHESES Cond RIGHT_PARENTHESES Stmt {
        printf("Stmt Find\n");
    }
    | WHILE LEFT_PARENTHESES Cond RIGHT_PARENTHESES Stmt {
        printf("Stmt Find\n");
    }
    | BREAK SEMICOLON{
        printf("Stmt Find\n");
    }
    | CONTINUE SEMICOLON {
        printf("Stmt Find\n");
    }
    | RETURN SEMICOLON {
        printf("Stmt Find\n");
    }
    | RETURN Exp SEMICOLON {
        printf("Stmt Find\n");
    };

/* Exp → AddExp */
Exp: AddExp {
        printf("Exp Find\n");
    };

/* Cond → LOrExp */
Cond: LOrExp{
        printf("Cond Find\n");
    };

/* LVal → Ident {'[' Exp ']'} */
LVal: IDENTIFIER {
        printf("Identifier Find\n");
    };

/* PrimaryExp → '(' Exp ')' | LVal | Number */
PrimaryExp: LEFT_PARENTHESES Exp RIGHT_PARENTHESES {
        printf("PrimaryExp Find\n");
    }
    | LVal {
        printf("PrimaryExp Find\n");
    }
    | Number {
        printf("PrimaryExp Find\n");
    };

/* Number → IntConst | floatConst */
Number: INTVAL  {
        printf("Number Find\n");
    }
    | FLOATVAL {
        printf("Number Find\n");
    };

/* UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' 
            | UnaryOp UnaryExp */
UnaryExp: PrimaryExp {
        printf("UnaryExp Find\n");
    }
    | IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES {
        printf("UnaryExp Find\n");
    }
    | IDENTIFIER LEFT_PARENTHESES FuncRParams RIGHT_PARENTHESES{
        printf("UnaryExp Find\n");
    }
    | UnaryOp UnaryExp{
        printf("UnaryExp Find\n");
    };

/* UnaryOp → '+' | '−' | '!'  */
UnaryOp: ADD {
        printf("UnaryOp Find\n");
    }    
    | SUB {
        printf("UnaryOp Find\n");
    }
    | NOT {
        printf("UnaryOp Find\n");
    };

/* FuncRParams → Exp { ',' Exp } */
FuncRParams: Exp {
        printf("FuncRParams Find\n");
    }
    | FuncRParams COMMA Exp {
        printf("FuncRParams Find\n");
    };

/* MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp */
MulExp: UnaryExp {
        printf("UnaryExp Find\n");
    }
    | MulExp MUL UnaryOp {
        printf("MulExp Find\n");
    }
    | MulExp DIV UnaryExp {
        printf("MulExp Find\n");
    }
    | MulExp MOD UnaryExp {
        printf("MulExp Find\n");
    };

/* AddExp → MulExp | AddExp ('+' | '−') MulExp */
AddExp: MulExp {
        printf("AddExp Find\n");
    }
    | AddExp ADD MulExp {
        printf("MulExp Find\n");
    }
    | AddExp SUB MulExp {
        printf("MulExp Find\n");
    };

/* RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp */
RelExp: AddExp {
        printf("RelExp Find\n");
    }
    | RelExp LT AddExp {
        printf("RelExp Find\n");
    }
    | RelExp GT AddExp {
        printf("RelExp Find\n");
    }
    | RelExp LTE AddExp {
        printf("RelExp Find\n");
    }
    | RelExp GTE AddExp {
        printf("RelExp Find\n");
    };

/* EqExp → RelExp | EqExp ('==' | '!=') RelExp */
EqExp: RelExp {
        printf("EqExp Find\n");
    }
    | EqExp EQ RelExp {
        printf("EqExp Find\n");
    }
    | EqExp NEQ RelExp {
        printf("EqExp Find\n");
    };

/* LAndExp → EqExp | LAndExp '&&' EqExp */
LAndExp: EqExp {
        printf("LAndExp Find\n");
    }
    | LAndExp AND EqExp {
        printf("LAndExp Find\n");
    };

/* LOrExp → LAndExp | LOrExp '||' LAndExp */
LOrExp: LAndExp {
        printf("LOrExp Find\n");
    }
    | LOrExp OR LAndExp {
        printf("LOrExp Find\n");
    };

/* ConstExp → AddExp  */
ConstExp: AddExp {
        printf("ConstExp Find\n");
    };
%%

void yyerror(const char* s) {
    printf("ERROR: %s\n", s);
}

int main(int argc, char *argv[]){
    /* int c; */
    ++argv;
    if (argc>0){yyin=fopen(argv[0], "r");}
    return yyparse();
}












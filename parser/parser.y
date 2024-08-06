
/* %skeleton "lalr1.cc" */

%{
    #include "../include/AST.hpp"
    #define m_s make_shared
    // #include <cstdio>
    extern int yylex(void);
    extern void yyerror(const char *s);
    extern FILE *yyin;
    extern YYLTYPE yylloc;
    extern CompUnit* root;
    CompUnit* root = nullptr;
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
    // Cond* cond;

    LVal* lVal;
    // PrimaryExp* primaryExp;
    Number* number;
    Exp* unaryExp;
    // UnaryOpType unaryOp;
    FuncRParams* funcRParams;
    Exp* mulExp;
    Exp* addExp;
    Exp* relExp;
    Exp* eqExp;
    Exp* lAndExp;
    Exp* lOrExp;
    ConstExp* constExp;
    BlockItems* blockItems;
    ConstDefs* constDefs;
    ArrayDim* arrayDim;
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
/* %type <cond> Cond */
%type <lVal> LVal
/* %type <primaryExp> PrimaryExp */
%type <number> Number
%type <unaryExp> UnaryExp
/* %type <unaryOp> UnaryOp */
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
    }
    | CompUnit FuncDef{
        $$ = $1;
        $1 -> addFuncDef(FuncDefPtr($2));
    }
    | Decl{
        root = new CompUnit();
        $$ = root;
        $$ -> addDecl(DeclPtr($1));
    }
    | FuncDef{
        root = new CompUnit();
        $$ = root;
        $$ -> addFuncDef(FuncDefPtr($1));
    };

Decl: ConstDecl{
        $$ = new Decl();
        $$ -> _node_type = NodeType::NT_DECL;
        $$ -> addConstDecl(ConstDeclPtr($1));
    }
    | VarDecl {
        $$ = new Decl();
        $$ -> _node_type = NodeType::NT_DECL;
        $$ -> addVarDecl(VarDeclPtr($1));
    };

/* ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';' */
ConstDecl: CONST BaseType ConstDefs SEMICOLON{
        $$ = new ConstDecl();
        $$ -> addType($2);
        $$ -> addConstDef(ConstDefsPtr($3));
    };

ConstDefs: ConstDef {
        $$ = new ConstDefs();
        $$->addConstDef(ConstDefPtr($1));
    }
    | ConstDefs COMMA ConstDef {
        $$ = $1;
        $1 -> addConstDef(ConstDefPtr($3));
    };

BaseType: INT{
        $$ = BaseType::B_INT;
    }
    |FLOAT {
        $$ = BaseType::B_FLOAT;
    }
    | VOID {
        $$ = BaseType::B_VOID;

    };

/* ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal*/
ConstDef: IDENTIFIER ASSIGN ConstExp{
        $$ = new ConstDef();
        $$ -> addIdentifier($1);
        $$ -> addArray(false);
        $$ -> addInitVal(ConstExpPtr($3));
    }
    | IDENTIFIER ArrayDim ASSIGN ArrayInitVal {
        $$ = new ConstDef();
        $$ -> addIdentifier($1);
        $$ -> addArray(true);
        $$ -> addArrayDim(ArrayDimPtr($2));
        $$ -> addArrayInitVal(ArrayInitValPtr($4));
    };

ArrayDim: LEFT_BRACKETS ConstExp RIGHT_BRACKETS {
        $$ = new ArrayDim();
        $$ -> addDim (ConstExpPtr($2));
    }
    | ArrayDim LEFT_BRACKETS ConstExp RIGHT_BRACKETS {
        $$ = $1;
        $$ -> addDim(ConstExpPtr($3));
    };

/* ConstInitVal → ConstExp 
                | '{' [ ConstInitVal { ',' ConstInitVal } ] '}' */
/* ConstInitVal: ConstExp {

        printf("ConstInitVal Find\n");
    }; */
/* ConstInitVals: ConstExp {
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
    | LEFT_BRACES ConstArrayInitVal RIGHT_BRACES{
        $$ = new ConstArrayInitVal();
        $$ -> addDimVal(ConstInitValsPtr(nullptr));
        printf("ConstArrayInitVal Find\n");
    }
    | LEFT_BRACES ConstInitVals COMMA ConstArrayInitVal RIGHT_BRACES {
        $$ = new ConstArrayInitVal();
        $$ -> addDimVal(ConstInitValsPtr($2));
        auto tmp = $4 -> getDimVal();
        for (auto initvals: tmp) $$ -> addDimVal(initvals);
        printf("ConstArrayInitVal Find\n");
    }
    | LEFT_BRACES ConstArrayInitVal COMMA ConstInitVals RIGHT_BRACES {
        $$ = $2;
        $2 -> addDimVal(ConstInitValsPtr($4));
        printf("ConstArrayInitVal Find\n");
    }; */

/* VarDecl → BType VarDef { ',' VarDef } ';' */
VarDecl: BaseType VarDefs SEMICOLON{
         $$ = new VarDecl();
         $$ -> addType($1);
         $$ -> addVarDefs(VarDefsPtr($2));
    };

VarDefs: VarDef {
        $$ = new VarDefs();
        $$ -> addVarDef(VarDefPtr($1));
    }
    | VarDefs COMMA VarDef {
        $$ = $1;
        $$ -> addVarDef(VarDefPtr($3)); 
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
    }
    | IDENTIFIER ASSIGN Exp{
        $$ = new VarDef();
        $$ -> addIdentifier($1);
        $$ -> addInit(true);
        $$ -> addInitVal(ExpPtr($3));
        $$ -> addArray(false);
    }
    | IDENTIFIER ArrayDim {
        $$ = new VarDef();
        $$ -> addIdentifier($1);
        $$ -> addArrayDim(ArrayDimPtr($2));
        $$ -> addInit(false);
        $$ -> addArray(true);
    }
    | IDENTIFIER ArrayDim ASSIGN ArrayInitVal{
        $$ = new VarDef();
        $$ -> addIdentifier($1);
        $$ -> addArrayDim(ArrayDimPtr($2));
        $$ -> addArrayInitVal(ArrayInitValPtr($4));
        $$ -> addInit(true);
        $$ -> addArray(true);
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
    }
    | ArrayInitVal {
        $$ = new InitVals();
        $$ -> addExp(ExpPtr($1));
    }
    | InitVals COMMA Exp {
        $$ = $1;
        $$ -> addExp(ExpPtr($3));
        
    }
    | InitVals COMMA ArrayInitVal {
        $$ = $1;
        $$ -> addExp(ExpPtr($3));
    };


ArrayInitVal: LEFT_BRACES InitVals RIGHT_BRACES {
        $$ = new ArrayInitVal();
        $$ -> addDimVal(InitValsPtr($2));
        $$ -> addType(ExpType::ET_DIM);
    }
    | LEFT_BRACES RIGHT_BRACES {
        $$ = new ArrayInitVal();
        $$ -> addDimVal(InitValsPtr(nullptr));
        $$ -> addType(ExpType::ET_DIM);
    };

 /* FuncDef → FuncType Ident '(' [FuncFParams] ')' Block */
FuncDef: BaseType IDENTIFIER LEFT_PARENTHESES FuncFParams RIGHT_PARENTHESES Block{
        $$ = new FuncDef();
        $$ -> _node_type = NodeType::NT_FUNC;
        $$ -> addReturnType($1);
        $$ -> addIdentifier($2);
        $$ -> addParam(true);
        $$ -> addFuncFParams(FuncFParamsPtr($4));
        $$ -> addBlock(BlockPtr($6));
    }
    | BaseType IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES Block{
        $$ = new FuncDef();
        $$ -> _node_type = NodeType::NT_FUNC;
        $$ -> addReturnType($1);
        $$ -> addIdentifier($2);
        $$ -> addParam(false);
        $$ -> addBlock(BlockPtr($5));
        $$ -> addFuncFParams(nullptr);
    };

/* FuncType → 'void' | 'int' | 'float' */

/* FuncFParams → FuncFParam { ',' FuncFParam } */
FuncFParams: FuncFParam {
        $$ = new FuncFParams();
        $$ -> addFuncFParam(FuncFParamPtr($1));
    }
    | FuncFParams COMMA FuncFParam{
        $$ = $1;
        $$ -> addFuncFParam(FuncFParamPtr($3));
    };

/* FuncFParam → BType Ident ['[' ']' { '[' Exp ']' }] */
FuncFParam: BaseType IDENTIFIER {
        $$ = new FuncFParam();
        $$ -> addType($1);
        $$ -> addIdentifier($2);
        $$ -> addArray(false);
    }
    | BaseType IDENTIFIER ParamArrayDim {
        $$ = new FuncFParam();
        $$ -> addType($1);
        $$ -> addIdentifier($2);
        $$ -> addArray(true);
        $$ -> addArrayDim(ParamArrayDimPtr($3));
    };

ParamArrayDim: LEFT_BRACKETS RIGHT_BRACKETS {
        $$ = new ParamArrayDim();
        $$ -> addDim(nullptr);
    }
    | ParamArrayDim LEFT_BRACKETS Exp RIGHT_BRACKETS {
        $$ = $1;
        $$ -> addDim(ExpPtr($3));
    };

/* Block → '{' { BlockItem } '}' */
Block: LEFT_BRACES RIGHT_BRACES {
        $$ = new Block();
        $$ -> addBlockItem(BlockItemsPtr(nullptr));
    }
    | LEFT_BRACES BlockItems RIGHT_BRACES{
        $$ = new Block();
        $$ -> addBlockItem(BlockItemsPtr($2));
    };

BlockItems: Decl {
        $$ = new BlockItems();
        $$ -> addDecl(DeclPtr($1));
    }
    | Stmt {
        $$ = new BlockItems();
        $$ -> addStmt(StmtPtr($1));
    }
    | BlockItems Decl {
        $$ = $1;
        $$ -> addDecl(DeclPtr($2));
    }
    | BlockItems Stmt {
        $$ = $1;
        $$ -> addStmt(StmtPtr($2));
    }
    | BlockItems SEMICOLON {
        $$ = $1;
    };

/* BlockItem → Decl | Stmt */


/* Stmt → LVal '=' Exp ';' | [Exp] ';' | Block
| 'if' '( Cond ')' Stmt [ 'else' Stmt ]
| 'while' '(' Cond ')' Stmt
| 'break' ';' | 'continue' ';'
| 'return' [Exp] ';' */
Stmt: LVal ASSIGN Exp SEMICOLON {
        AssignStmt* assign = new AssignStmt();
        assign -> addLVal(LValPtr($1));
        assign -> addExp(ExpPtr($3));
        $$ = (Stmt*)(assign);
        $$ -> addType(StmtType::ST_ASSIGN);
        $$ -> _node_type = NodeType::NT_STMT;
    }   
    | Exp SEMICOLON {
        ExpStmt* exp = new ExpStmt();
        exp -> addExp(ExpPtr($1));
        $$ = (Stmt*)(exp);
        $$ -> addType(StmtType::ST_EXP);
        $$ -> _node_type = NodeType::NT_STMT;
    }
    | SEMICOLON {
        $$ = new Stmt();
        $$ -> addType(StmtType::ST_BLANK);
        $$ -> _node_type = NodeType::NT_STMT;
    }
    | Block {
        BlockStmt* block = new BlockStmt();
        block -> addBlock(BlockPtr($1));
        $$ = (Stmt*)(block);
        $$ -> addType(StmtType::ST_BLOCK);
        $$ -> _node_type = NodeType::NT_STMT;
    }
    | IF LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt {
        IfElseStmt* ifelsestmt = new IfElseStmt();
        ifelsestmt -> addCond(ExpPtr($3));
        ifelsestmt -> addThenStmt(StmtPtr($5));
        ifelsestmt -> addElseStmt(StmtPtr(nullptr));
        $$ = (Stmt*)(ifelsestmt);
        $$ -> addType(StmtType::ST_IF);
        $$ -> _node_type = NodeType::NT_STMT;
    }
    | IF LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt ELSE Stmt {
        IfElseStmt* ifelsestmt = new IfElseStmt();
        ifelsestmt -> addCond(ExpPtr($3));
        ifelsestmt -> addThenStmt(StmtPtr($5));
        ifelsestmt -> addElseStmt(StmtPtr($7));
        $$ = (Stmt*)(ifelsestmt);
        $$ -> addType(StmtType::ST_IF);
        $$ -> _node_type = NodeType::NT_STMT;
    }
    | WHILE LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt {
        WhileStmt* whilestmt = new WhileStmt();
        whilestmt -> addCond(ExpPtr($3));
        whilestmt -> addStmt(StmtPtr($5));
        $$ = (Stmt*)(whilestmt);
        $$ -> addType(StmtType::ST_WHILE);
        $$ -> _node_type = NodeType::NT_STMT;
    }
    | BREAK SEMICOLON{
        $$ = new Stmt();
        $$ -> addType(StmtType::ST_BREAK);
        $$ -> _node_type = NodeType::NT_STMT;
    }
    | CONTINUE SEMICOLON {
        $$ = new Stmt();
        $$ -> addType(StmtType::ST_CONTINUE);
        $$ -> _node_type = NodeType::NT_STMT;
    }
    | RETURN SEMICOLON {
        ReturnStmt* returnstmt = new ReturnStmt();
        returnstmt -> addExp(nullptr);
        $$ = (Stmt*)(returnstmt);
        $$ -> addType(StmtType::ST_RETURN);
        $$ -> _node_type = NodeType::NT_STMT;
    }
    | RETURN Exp SEMICOLON {
        ReturnStmt* returnstmt = new ReturnStmt();
        returnstmt -> addExp(ExpPtr($2));
        $$ = (Stmt*)(returnstmt);
        $$ -> addType(StmtType::ST_RETURN);
        $$ -> _node_type = NodeType::NT_STMT;
    };

/* Exp → AddExp */
Exp: AddExp {
        $$ = $1;
    };

/* Cond → LOrExp */

/* LVal → Ident {'[' Exp ']'} */
LVal: IDENTIFIER {
        $$ = new LVal();
        $$ -> addIdentifier($1);
        $$ -> addIsArray(false);
        $$ -> addType(ExpType::ET_LVAL);
    }
    | LVal LEFT_BRACKETS Exp RIGHT_BRACKETS {
        $$ = $1;
        $$ -> addIsArray(true);
        $$ -> addDims(ExpPtr($3));
        $$ -> addType(ExpType::ET_LVAL);
    };

/* PrimaryExp → '(' Exp ')' | LVal | Number */

/* Number → IntConst | floatConst */
Number: INTVAL  {
        $$ = new Number(0, 0, false);
        $$ -> addIntVal($1);
        $$ -> addFloatVal(float($1));
        $$ -> addIsFloat(false);
        $$ -> addType(ExpType::ET_INT);
    }
    | FLOATVAL {
        $$ = new Number(0, 0, false);
        $$ -> addFloatVal($1);
        $$ -> addIntVal(int($1));
        $$ -> addIsFloat(true);
        $$ -> addType(ExpType::ET_FLOAT);
        
    };

/* UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' 
            | UnaryOp UnaryExp */
UnaryExp: LEFT_PARENTHESES Exp RIGHT_PARENTHESES {
        $$ = $2;
    }
    | LVal {
        $$ = (Exp*)($1);
    }
    | Number {
        $$ = (Exp*)($1);
    }
    | IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES {
        auto tmp = new FuncCall();
        tmp -> addIdentifier($1);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_FUNC); 

        
    }
    | IDENTIFIER LEFT_PARENTHESES FuncRParams RIGHT_PARENTHESES{
        auto tmp = new FuncCall();
        tmp -> addIdentifier($1);
        tmp -> addArgs(FuncRParamsPtr($3));
        $$ = (Exp*)(tmp); 
        $$ -> addType(ExpType::ET_FUNC); 
    }
    | ADD UnaryExp{
        $$ = $2;
    }
    | SUB UnaryExp{
        $$ = $2;
        $$ -> addNeg();
        
    }
    | NOT UnaryExp{
        $$ = $2;
        $$ -> addNot();
    };

/* UnaryOp → '+' | '−' | '!'  */
/* UnaryOp: ADD {
        $$ = UnaryOpType::UO_POS;
        printf("UnaryOp Find\n");
    }    
    | SUB {
        $$ = UnaryOpType::UO_NEG;
        printf("UnaryOp Find\n");
    }
    | NOT {
        $$ = UnaryOpType::UO_NOT;
        printf("UnaryOp Find\n");
    }; */

/* FuncRParams → Exp { ',' Exp } */
FuncRParams: Exp {
        $$ = new FuncRParams();
        $$ -> addArgs(ExpPtr($1));
    }
    | FuncRParams COMMA Exp {
        $$ = $1;
        $$ -> addArgs(ExpPtr($3));
    };

/* MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp */
MulExp: UnaryExp {
        $$ = $1;
    }
    | MulExp MUL UnaryExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_MUL);
        tmp -> addType(ExpType::ET_BIN);
        $$ = (Exp*)(tmp);
    }
    | MulExp DIV UnaryExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_DIV);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    }
    | MulExp MOD UnaryExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_MOD);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    };

/* AddExp → MulExp | AddExp ('+' | '−') MulExp */
AddExp: MulExp {
         $$ = $1;
    } 
    | AddExp ADD MulExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_ADD);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    }
    | AddExp SUB MulExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_SUB);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    };

/* RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp */
RelExp: AddExp {
        $$ = $1;
    }
    | RelExp LT AddExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_LT);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    }
    | RelExp GT AddExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_GT);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    }
    | RelExp LTE AddExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_LTE);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    }
    | RelExp GTE AddExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_GTE);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    };

/* EqExp → RelExp | EqExp ('==' | '!=') RelExp */
EqExp: RelExp {
        $$ = $1;
    }
    | EqExp EQ RelExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_EQ);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    }
    | EqExp NEQ RelExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_NEQ);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    };

/* LAndExp → EqExp | LAndExp '&&' EqExp */
LAndExp: EqExp {
        $$ = $1;
    }
    | LAndExp AND EqExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_AND);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    };

/* LOrExp → LAndExp | LOrExp '||' LAndExp */
LOrExp: LAndExp {
        $$ = $1;
    }
    | LOrExp OR LAndExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_OR);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
    };

/* ConstExp → AddExp  */
ConstExp: AddExp {
        $$ = new ConstExp();
        $$ -> addExp(ExpPtr($1));
    };
%%


/* int main(int argc, char *argv[]){
    ++ argv;
    if (argc > 0) yyin = fopen(argv[0], "r");
    else {
        printf("No input file\n");
        return 0;
    }
    yyparse();
    std::cout << root << std::endl;
    return 0;
} */

CompUnit* parse(char *filename) {
    yyin = fopen(filename, "r");
    yyparse();
    return root;
}

void yyerror(const char* s) {
    printf("line:%d\tcolumn:%d\n", yylloc.first_line, yylloc.first_column);
    /* char line[1024]={0};
    for (int i=1;i<=yylloc.first_line;i++) {
        fgets(line, 1024, yyin);
    }
    printf("%s\n", line); */
    printf("ERROR: %s\n", s);
}









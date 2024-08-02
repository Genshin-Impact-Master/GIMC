
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
        printf("CompUnit Decl Find\n");
    }
    | CompUnit FuncDef{
        $$ = $1;
        $1 -> addFuncDef(FuncDefPtr($2));
        printf("CompUnit FuncDef Find\n");
    }
    | Decl{
        root = new CompUnit();
        $$ = root;
        $$ -> addDecl(DeclPtr($1));
        printf("Decl Find\n");
    }
    | FuncDef{
        root = new CompUnit();
        $$ = root;
        $$ -> addFuncDef(FuncDefPtr($1));
        printf("FuncDef Find\n");
    };

Decl: ConstDecl{
        $$ = new Decl();
        $$ -> _node_type = NodeType::NT_DECL;
        $$ -> addConstDecl(ConstDeclPtr($1));
        printf("ConstDecl Find\n");
    }
    | VarDecl {
        $$ = new Decl();
        $$ -> _node_type = NodeType::NT_DECL;
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
        $$ -> _node_type = NodeType::NT_FUNC;
        $$ -> addReturnType($1);
        $$ -> addIdentifier($2);
        $$ -> addParam(true);
        $$ -> addFuncFParams(FuncFParamsPtr($4));
        $$ -> addBlock(BlockPtr($6));
        printf("FuncDef Find\n");
    }
    | BaseType IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES Block{
        $$ = new FuncDef();
        $$ -> _node_type = NodeType::NT_FUNC;
        $$ -> addReturnType($1);
        $$ -> addIdentifier($2);
        $$ -> addParam(false);
        $$ -> addBlock(BlockPtr($5));
        $$ -> addFuncFParams(nullptr);
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
        $$ -> addArrayDim(ParamArrayDimPtr($3));
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
Block: LEFT_BRACES RIGHT_BRACES {
        $$ = new Block();
        $$ -> addBlockItem(BlockItemsPtr(nullptr));
        printf("Empty Block Find\n");
    }
    | LEFT_BRACES BlockItems RIGHT_BRACES{
        $$ = new Block();
        $$ -> addBlockItem(BlockItemsPtr($2));
        printf("Block Find\n");
    };

BlockItems: Decl {
        $$ = new BlockItems();
        $$ -> addDecl(DeclPtr($1));
        printf("BlockItems Find\n");
    }
    | Stmt {
        $$ = new BlockItems();
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
        AssignStmt* assign = new AssignStmt();
        assign -> addLVal(LValPtr($1));
        assign -> addExp(ExpPtr($3));
        $$ = (Stmt*)(assign);
        $$ -> addType(StmtType::ST_ASSIGN);
        $$ -> _node_type = NodeType::NT_STMT;
        printf("Assign Stmt Find\n");
    }   
    | Exp SEMICOLON {
        ExpStmt* exp = new ExpStmt();
        exp -> addExp(ExpPtr($1));
        $$ = (Stmt*)(exp);
        $$ -> addType(StmtType::ST_EXP);
        $$ -> _node_type = NodeType::NT_STMT;
        printf("Exp Stmt Find\n");
    }
    | SEMICOLON {
        $$ = new Stmt();
        $$ -> addType(StmtType::ST_BLANK);
        $$ -> _node_type = NodeType::NT_STMT;
        printf("Blank Stmt Find\n");
    }
    | Block {
        BlockStmt* block = new BlockStmt();
        block -> addBlock(BlockPtr($1));
        $$ = (Stmt*)(block);
        $$ -> addType(StmtType::ST_BLOCK);
        $$ -> _node_type = NodeType::NT_STMT;
        printf("Block Stmt Find\n");
    }
    | IF LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt {
        IfElseStmt* ifelsestmt = new IfElseStmt();
        ifelsestmt -> addCond(ExpPtr($3));
        ifelsestmt -> addThenStmt(StmtPtr($5));
        ifelsestmt -> addElseStmt(StmtPtr(nullptr));
        $$ = (Stmt*)(ifelsestmt);
        $$ -> addType(StmtType::ST_IF);
        $$ -> _node_type = NodeType::NT_STMT;
        printf("If Stmt Find\n");
    }
    | IF LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt ELSE Stmt {
        IfElseStmt* ifelsestmt = new IfElseStmt();
        ifelsestmt -> addCond(ExpPtr($3));
        ifelsestmt -> addThenStmt(StmtPtr($5));
        ifelsestmt -> addElseStmt(StmtPtr($7));
        $$ = (Stmt*)(ifelsestmt);
        $$ -> addType(StmtType::ST_IF);
        $$ -> _node_type = NodeType::NT_STMT;
        printf("If Else Stmt Find\n");
    }
    | WHILE LEFT_PARENTHESES LOrExp RIGHT_PARENTHESES Stmt {
        WhileStmt* whilestmt = new WhileStmt();
        whilestmt -> addCond(ExpPtr($3));
        whilestmt -> addStmt(StmtPtr($5));
        $$ = (Stmt*)(whilestmt);
        $$ -> addType(StmtType::ST_WHILE);
        $$ -> _node_type = NodeType::NT_STMT;
        printf("While Stmt Find\n");
    }
    | BREAK SEMICOLON{
        $$ = new Stmt();
        $$ -> addType(StmtType::ST_BREAK);
        $$ -> _node_type = NodeType::NT_STMT;
        printf("Break Stmt Find\n");
    }
    | CONTINUE SEMICOLON {
        $$ = new Stmt();
        $$ -> addType(StmtType::ST_CONTINUE);
        $$ -> _node_type = NodeType::NT_STMT;
        printf("Continue Stmt Find\n");
    }
    | RETURN SEMICOLON {
        ReturnStmt* returnstmt = new ReturnStmt();
        returnstmt -> addExp(nullptr);
        $$ = (Stmt*)(returnstmt);
        $$ -> addType(StmtType::ST_RETURN);
        $$ -> _node_type = NodeType::NT_STMT;
        printf("Return Stmt Find\n");
    }
    | RETURN Exp SEMICOLON {
        ReturnStmt* returnstmt = new ReturnStmt();
        returnstmt -> addExp(ExpPtr($2));
        $$ = (Stmt*)(returnstmt);
        $$ -> addType(StmtType::ST_RETURN);
        $$ -> _node_type = NodeType::NT_STMT;
        printf("Return Stmt Find\n");
    };

/* Exp → AddExp */
Exp: AddExp {
        $$ = $1;
        printf("Exp Find\n");
    };

/* Cond → LOrExp */

/* LVal → Ident {'[' Exp ']'} */
LVal: IDENTIFIER {
        $$ = new LVal();
        $$ -> addIdentifier($1);
        $$ -> addIsArray(false);
        $$ -> addType(ExpType::ET_LVAL);
        printf("LVal Find\n");
    }
    | LVal LEFT_BRACKETS Exp RIGHT_BRACKETS {
        $$ = $1;
        $$ -> addIsArray(true);
        $$ -> addDims(ExpPtr($3));
        $$ -> addType(ExpType::ET_LVAL);
        printf("LVal Find\n");
    };

/* PrimaryExp → '(' Exp ')' | LVal | Number */
/* PrimaryExp: LEFT_PARENTHESES Exp RIGHT_PARENTHESES {
        printf("PrimaryExp Find\n");
    }
    | LVal {
        printf("PrimaryExp Find\n");
    }
    | Number {
        printf("PrimaryExp Find\n");
    }; */

/* Number → IntConst | floatConst */
Number: INTVAL  {
        $$ = new Number(0, 0, false);
        $$ -> addIntVal($1);
        $$ -> addFloatVal(float($1));
        $$ -> addIsFloat(false);
        $$ -> addType(ExpType::ET_INT);
        printf("%d, %f, Number Find\n", $$ -> getIntVal(), $$ -> getFloatVal());
    }
    | FLOATVAL {
        $$ = new Number(0, 0, false);
        $$ -> addFloatVal($1);
        $$ -> addIntVal(int($1));
        $$ -> addIsFloat(true);
        $$ -> addType(ExpType::ET_FLOAT);
        printf("%d, %f, Number Find\n", $$ -> getIntVal(), $$ -> getFloatVal());
        
    };

/* UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' 
            | UnaryOp UnaryExp */
UnaryExp: LEFT_PARENTHESES Exp RIGHT_PARENTHESES {
        $$ = $2;
        printf("UnaryExp Find\n");
    }
    | LVal {
        $$ = (Exp*)($1);
        printf("UnaryExp Find\n");
    }
    | Number {
        $$ = (Exp*)($1);
        printf("UnaryExp Find\n");
    }
    | IDENTIFIER LEFT_PARENTHESES RIGHT_PARENTHESES {
        auto tmp = new FuncCall();
        tmp -> addIdentifier($1);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_FUNC); 

        
        printf("UnaryExp Find\n");
    }
    | IDENTIFIER LEFT_PARENTHESES FuncRParams RIGHT_PARENTHESES{
        auto tmp = new FuncCall();
        tmp -> addIdentifier($1);
        tmp -> addArgs(FuncRParamsPtr($3));
        $$ = (Exp*)(tmp); 
        $$ -> addType(ExpType::ET_FUNC); 
        printf("UnaryExp Find\n");
    }
    | ADD UnaryExp{
        $$ = $2;
        printf("UnaryExp Find\n");
    }
    | SUB UnaryExp{
        $$ = $2;
        $$ -> addNeg();
        printf("UnaryExp Find\n");
        
    }
    | NOT UnaryExp{
        $$ = $2;
        $$ -> addNot();
        printf("UnaryExp Find\n");
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
        printf("FuncRParams Find\n");
    }
    | FuncRParams COMMA Exp {
        $$ = $1;
        $$ -> addArgs(ExpPtr($3));
        printf("FuncRParams Find\n");
    };

/* MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp */
MulExp: UnaryExp {
        $$ = $1;
        printf("MulExp Find\n");
    }
    | MulExp MUL UnaryExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_MUL);
        tmp -> addType(ExpType::ET_BIN);
        $$ = (Exp*)(tmp);
        printf("MulExp Find\n");
    }
    | MulExp DIV UnaryExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_DIV);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
        printf("MulExp Find\n");
    }
    | MulExp MOD UnaryExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_MOD);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
        printf("MulExp Find\n");
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
        printf("AddExp Find\n");
    }
    | AddExp SUB MulExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_SUB);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
        printf("AddExp Find\n");
    };

/* RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp */
RelExp: AddExp {
        $$ = $1;
        printf("RelExp Find\n");
    }
    | RelExp LT AddExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_LT);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    }
    | RelExp GT AddExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_GT);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    }
    | RelExp LTE AddExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_LTE);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    }
    | RelExp GTE AddExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_GTE);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
        printf("RelExp Find\n");
    };

/* EqExp → RelExp | EqExp ('==' | '!=') RelExp */
EqExp: RelExp {
        $$ = $1;
        printf("EqExp Find\n");
    }
    | EqExp EQ RelExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_EQ);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
        printf("EqExp Find\n");
    }
    | EqExp NEQ RelExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_NEQ);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
        printf("EqExp Find\n");
    };

/* LAndExp → EqExp | LAndExp '&&' EqExp */
LAndExp: EqExp {
        $$ = $1;
        printf("LAndExp Find\n");
    }
    | LAndExp AND EqExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_AND);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
        printf("LAndExp Find\n");
    };

/* LOrExp → LAndExp | LOrExp '||' LAndExp */
LOrExp: LAndExp {
        $$ = $1;
        printf("LOrExp Find\n");
    }
    | LOrExp OR LAndExp {
        auto tmp = new BinaryExp();
        tmp -> addExp1(ExpPtr($1));
        tmp -> addExp2(ExpPtr($3));
        tmp -> addOp(BinOpType::OP_OR);
        $$ = (Exp*)(tmp);
        $$ -> addType(ExpType::ET_BIN);
        printf("LOrExp Find\n");
    };

/* ConstExp → AddExp  */
ConstExp: AddExp {
        $$ = new ConstExp();
        $$ -> addExp(ExpPtr($1));
        printf("ConstExp Find\n");
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









/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ADD = 258,                     /* ADD  */
    SUB = 259,                     /* SUB  */
    MUL = 260,                     /* MUL  */
    DIV = 261,                     /* DIV  */
    MOD = 262,                     /* MOD  */
    ASSIGN = 263,                  /* ASSIGN  */
    EQ = 264,                      /* EQ  */
    NEQ = 265,                     /* NEQ  */
    LT = 266,                      /* LT  */
    LTE = 267,                     /* LTE  */
    GT = 268,                      /* GT  */
    GTE = 269,                     /* GTE  */
    AND = 270,                     /* AND  */
    OR = 271,                      /* OR  */
    NOT = 272,                     /* NOT  */
    IF = 273,                      /* IF  */
    ELSE = 274,                    /* ELSE  */
    WHILE = 275,                   /* WHILE  */
    BREAK = 276,                   /* BREAK  */
    CONTINUE = 277,                /* CONTINUE  */
    RETURN = 278,                  /* RETURN  */
    CONST = 279,                   /* CONST  */
    INT = 280,                     /* INT  */
    VOID = 281,                    /* VOID  */
    FLOAT = 282,                   /* FLOAT  */
    LEFT_PARENTHESES = 283,        /* LEFT_PARENTHESES  */
    RIGHT_PARENTHESES = 284,       /* RIGHT_PARENTHESES  */
    LEFT_BRACKETS = 285,           /* LEFT_BRACKETS  */
    RIGHT_BRACKETS = 286,          /* RIGHT_BRACKETS  */
    LEFT_BRACES = 287,             /* LEFT_BRACES  */
    RIGHT_BRACES = 288,            /* RIGHT_BRACES  */
    COMMA = 289,                   /* COMMA  */
    SEMICOLON = 290,               /* SEMICOLON  */
    IDENTIFIER = 291,              /* IDENTIFIER  */
    INTVAL = 292,                  /* INTVAL  */
    FLOATVAL = 293                 /* FLOATVAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "parser.y"

    
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

#line 149 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

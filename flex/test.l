%option noyywrap

%{
    #include <string>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <assert.h>
    #include <stdbool.h>
    #include "../include/Token.hpp"    
    int totline=0;
    enum TokenType{
        VOID =258,
        INT,
        FLOAT,
        INT_VALUE,
        FLOAT_VALUE,
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        ASSIGN,
        EQ,
        NEQ,
        LT,
        LTE,
        GT,
        GTE,
        AND,
        OR,
        NOT,
        IF,
        ELSE,
        WHILE,
        BREAK,
        CONTINUE,
        RETURN,
        CONST,
        LEFT_PARENTHESIS,
        RIGHT_PARENTHESIS,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        LEFT_BRACE,
        RIGHT_BRACE,
        IDENTIFIER,
        COMMA,
        SEMICOLON
    };
    
%}

DIGIT [0-9]
NONZERO_DIGIT [1-9]


HEX_PREFIX (0x)|(0X)
HEX_DIGIT [0-9a-fA-F]

OCT_PREFIX 0
OCT_DIGIT [0-7]

DEC_INTEGER ({NONZERO_DIGIT}{DIGIT}*|0)
OCT_INTEGER {OCT_PREFIX}{OCT_DIGIT}+
HEX_INTEGER {HEX_PREFIX}{HEX_DIGIT}+

DEC_FLOAT_VALUE ({DIGIT}*[.]{DIGIT}+|{DIGIT}+[.])([eE][+-]?{DIGIT}+)
HEX_FLOAT_VALUE {HEX_PREFIX}({HEX_DIGIT}*[.]{HEX_DIGIT}+|{HEX_DIGIT}+[.])([pP][+-]?{DIGIT}+)|{HEX_DIGIT}({HEX_DIGIT}+)([pP][+-]?{DIGIT}+)

TOKEN_INT_VALUE {DEC_INTEGER}|{OCT_INTEGER}|{HEX_INTEGER}
TOKEN_FLOAT_VALUE  {DEC_FLOAT_VALUE}|{HEX_FLOAT_VALUE}    

LETTER [a-zA-Z]
TOKEN_IDENTIFIER ({LETTER}|_)({DIGIT}|{LETTER}|_)*

%%
\/\/.*      ;
"/*"        {
                int c;
                while ((c=yyinput())!=0){
                    if (c=='\n') yylineno++;
                    else if (c=='*'){
                        if ((c=yyinput())=='/') break;
                        else unput(c);
                    }
                }
            }
[ \n\t\r]   ;

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

{TOKEN_IDENTIFIER} return IDENTIFIER;
{TOKEN_INT_VALUE}  return INT_VALUE;
{TOKEN_FLOAT_VALUE} return FLOAT_VALUE;

"="                 return ASSIGN;
"=="                return EQ;
"!="                return NEQ;

">"                 return GT;
">="                return GTE;
"<"                 return LT;
"<="                return LTE;

"&&"                return AND;
"||"                return OR;
"!"                 return NOT;

"("                 return LEFT_PARENTHESIS;
")"                 return RIGHT_PARENTHESIS;
"["                 return LEFT_BRACKET;
"]"                 return RIGHT_BRACKET;
"{"                 return LEFT_BRACE;
"}"                 return RIGHT_BRACE;

","                 return COMMA;
";"                 return SEMICOLON;

<<EOF>>             return -1;
.                   printf("%s\n", (std::string("Unknown token: ") + yytext).c_str()); yyterminate();

%%

int main(int argc, char *argv[]){
    int c;
    ++argv;
    if (argc>0){yyin=fopen(argv[0], "r");}
    while ((c=yylex())!=-1){
        printf("(%s %s)\n",getTokenName(c),yytext);
    }
    return 0;
}
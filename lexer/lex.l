%option noyywrap

%{
    #include <string>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <assert.h>
    #include <stdbool.h>
    #include "../include/AST.hpp" 
    #include "../parser/parser.hpp"

    int yycolumn = 1;
    /* Location type.  */
    // extern YYLTYPE yylloc;
	YYLTYPE yylloc = {1,0,0,0};
    #define YY_USER_ACTION yylloc.first_line = yylineno;            \
                       yylloc.first_column = yycolumn;          \
                       for (auto i : std::string(yytext_ptr)) { \
                           if (i == '\n') {                     \
                               yylineno++;                      \
                               yycolumn = 1;                    \
                           } else {                             \
                               yycolumn++;                      \
                           }                                    \
                       }
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

{TOKEN_IDENTIFIER} {
                        yylval.identifier= new std::string(yytext,yyleng);
                        // cout<<yylval.string<<endl;
                        return IDENTIFIER;
                    }
{TOKEN_INT_VALUE}  {
                        yylval.intVal = static_cast<int32_t>(strtol(yytext, NULL, 0));
                        return INTVAL;
                   }
{TOKEN_FLOAT_VALUE} {
    yylval.floatVal = static_cast<float>(strtod(yytext, NULL));
    return FLOATVAL;
    }

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

"("                 return LEFT_PARENTHESES;
")"                 return RIGHT_PARENTHESES;
"["                 return LEFT_BRACKETS;
"]"                 return RIGHT_BRACKETS;
"{"                 return LEFT_BRACES;
"}"                 return RIGHT_BRACES;

","                 return COMMA;
";"                 return SEMICOLON;

<<EOF>>             return -1;
.                   printf("%s\n", (std::string("Unknown token: ") + yytext).c_str()); yyterminate();

%%

/* int main(int argc, char *argv[]){
    int c;
    ++argv;
    if (argc>0){yyin=fopen(argv[0], "r");}
    while ((c=yylex())!=-1){
        printf("(%s %s)\n",getTokenName(c),yytext);
    }
    return 0;
} */
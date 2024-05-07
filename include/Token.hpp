
#ifndef TOKEN_HPP
#define TOKEN_HPP  
#include <string.h>
#include <stdio.h>
const char *TokenName[]={"VOID",
"INT",
"FLOAT",
"INT_VALUE",
"FLOAT_VALUE",
"ADD",
"SUB",
"MUL",
"DIV",
"MOD",
"ASSIGN",
"EQ",
"NEQ",
"LT",
"LTE",
"GT",
"GTE",
"AND",
"OR",
"NOT",
"IF",
"ELSE",
"WHILE",
"BREAK",
"CONTINUE",
"RETURN",
"CONST",
"LEFT_PARENTHESIS",
"RIGHT_PARENTHESIS",
"LEFT_BRACKET",
"RIGHT_BRACKET",
"LEFT_BRACE",
"RIGHT_BRACE",
"IDENTIFIER",
"COMMA",
"SEMICOLON"
};
const char* getTokenName(int c){
    return TokenName[c-258];
}
#endif
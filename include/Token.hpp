
#ifndef _TOKEN_HPP
#define _TOKEN_HPP  
#include <memory>
#include <iostream>
#include <string>
#include <vector>
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
// enum yytokentype
// {
//     ADD = 258,
//     SUB = 259,
//     MUL = 260,
//     DIV = 261,
//     MOD = 262,
//     ASSIGN = 263,
//     EQ = 264,
//     NEQ = 265,
//     LT = 266,
//     LTE = 267,
//     GT = 268,
//     GTE = 269,
//     AND = 270,
//     OR = 271,
//     NOT = 272,
//     IF = 273,
//     ELSE = 274,
//     WHILE = 275,
//     BREAK = 276,
//     CONTINUE = 277,
//     RETURN = 278,
//     CONST = 279,
//     INT = 280,
//     VOID = 281,
//     FLOAT = 282,
//     LEFT_PARENTHESES = 283,
//     RIGHT_PARENTHESES = 284,
//     LEFT_BRACKETS = 285,
//     RIGHT_BRACKETS = 286,
//     LEFT_BRACES = 287,
//     RIGHT_BRACES = 288,
//     COMMA = 289,
//     SEMICOLON = 290,
//     IDENTIFIER = 291,
//     INTVAL = 292,
//     FLOATVAL = 293
//   };
const char* getTokenName(int c){
    return TokenName[c-258];
}
#endif
#ifndef GLOBALS_H
#define GLOBALS_H

using namespace std;
#include <iostream>
#include <string>
#include <algorithm>

#define N 100 //number of tokens

//Criar classe Global with enumeration

// enum tokens
// {   ID = 0,
//     INT = 1,
//     MAIN = 2,
//     FLOAT = 3,

// };

// enum types { int 1, float 2, char 3, void 4}

///Tipos de dados permitidos na linguagem
#define INT_     1
#define FLOAT_   2
#define CHAR_    3
#define VOID_ 4

///Tokens da linguagem
#define ID  0
#define INT 1
#define MAIN 2
#define FLOAT 3
#define IF  4
#define ELSE 5
#define WHILE 6
#define READ  7
#define PRINT 8
#define LBRACE  9
#define RBRACE  10
#define COMMA  11
#define PCOMMA  12
#define LBRACKET  13
#define RBRACKET  14
#define ATTR 15
#define OR  16
#define AND 17
#define EQ  18
#define NE  19
#define LT  20
#define LE  21
#define GT  22
#define GE  23
#define PLUS 24
#define MINUS 25
#define MULT 26
#define DIV  27
#define INTEGER_CONST 28
#define FLOAT_CONST 29
#define FOR 30
#define LCOL 31
#define RCOL 32
#define CHAR 33
#define VOID 34
#define INC 35
#define DEC 36
#define NUM 37

#define VARS 38
#define PARAMS 39
#define INI 40
#define TO 41
#define DIFF 42 //'
#define D 43 //d

#endif

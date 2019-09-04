#include "global.h"

std::string tokensNames[N];

void initializeConstants()
{
  tokensNames[FOR] = "FOR";
  tokensNames[MAIN] = "MAIN";
  tokensNames[ID] = "ID";
  tokensNames[INT] = "INT";
  tokensNames[FLOAT] = "FLOAT";
  tokensNames[IF] = "IF";
  tokensNames[ELSE] = "ELSE";
  tokensNames[WHILE] = "WHILE";
  tokensNames[READ] = "READ";
  tokensNames[PRINT] = "PRINT";
  tokensNames[LBRACE] = "LBRACE";
  tokensNames[RBRACE] = "RBRACE";
  tokensNames[COMMA] = "COMMA";
  tokensNames[PCOMMA] = "PCOMMA";
  tokensNames[LBRACKET] = "LBRACKET";
  tokensNames[RBRACKET] = "RBRACKET";
  tokensNames[ATTR] = "ATTR";
  tokensNames[OR] = "OR";
  tokensNames[AND] = "AND";
  tokensNames[EQ] = "EQ";
  tokensNames[NE] = "NE";
  tokensNames[LT] = "LT";
  tokensNames[LE] = "LE";
  tokensNames[GT] = "GT";
  tokensNames[GE] = "GE";
  tokensNames[PLUS] = "PLUS";
  tokensNames[MINUS] = "MINUS";
  tokensNames[MULT] = "MULT";
  tokensNames[DIV] = "DIV";
  tokensNames[INTEGER_CONST] = "INTEGER_CONST";
  tokensNames[FLOAT_CONST] = "FLOAT_CONST";
  tokensNames[LCOL] = "LCOL";
  tokensNames[RCOL] = "RCOL";
  tokensNames[CHAR] = "CHAR";
}

#ifndef NUM_H
#define NUM_H

using namespace std;
#include "Expr.h"

class Num: public Expr
{
  public:
    string lexema;
    Num();
    Num(string name, string lexema, int type);
    string getLexema();
    void printNode(int level);
    float evaluate();
    void generateCode();
    void generateRValueCode();
    void generateBranchCode();
    void generatePythonCode(int level);
};

#endif

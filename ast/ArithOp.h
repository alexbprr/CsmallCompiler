#ifndef ARITHOP_H
#define ARITHOP_H

using namespace std;
#include "Expr.h"

class ArithOp: public Expr
{
  public:
    ArithOp();
    ArithOp(string name, string op);
    float evaluate();
    void generateCode();
    void generateBranchCode();
    void generateRValueCode();
};

#endif

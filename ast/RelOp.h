#ifndef RELOP_H
#define RELOP_H

using namespace std;
#include "Expr.h"

class RelOp: public Expr
{
  public:
    RelOp();
    RelOp(string name, string op);
    // void printNode(int level);
    float evaluate();
    void generateCode();
    void generateBranchCode();
    void generateRValueCode();
};

#endif

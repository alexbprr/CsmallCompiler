#ifndef LOGICALOP_H
#define LOGICALOP_H

using namespace std;
#include "Expr.h"

class LogicalOp: public Expr
{
  public:
    LogicalOp();
    LogicalOp(string name, string op);
    float evaluate();
    //void generateCode();
    void generateBranchCode();
    void generateRValueCode();
    void generatePythonCode(int level);
};

#endif

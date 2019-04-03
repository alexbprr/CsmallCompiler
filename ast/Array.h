#ifndef ARRAY_H
#define ARRAY_H

using namespace std;
#include "Arrayt.h"
#include "Id.h"

class Array: public Expr
{
  public:
    Id* id;
    Arrayt* arrayt;
    bool isDecl;
    Array();
    Array(string name, Id *id, Arrayt* arrayt);
    void printNode(int level);
    float evaluate();
    void generateCode();
    void generateRValueCode();
    void generateBranchCode();
    void generatePythonCode(int level);
};

#endif

#ifndef ID_H
#define ID_H

using namespace std;
#include "Expr.h"

class Id: public Expr
{
  public:
    TableEntry* tableEntryRef;
    Id();
    Id(string name);
    Id(const Id &id);
    float evaluate();
    void generateCode();
    void generateRValueCode();
    void generateBranchCode();
    void generatePythonCode(int level);
    void printNode(int level);
};

#endif

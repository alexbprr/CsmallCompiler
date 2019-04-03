#ifndef PRINT_H
#define PRINT_H

using namespace std;
#include "Astnode.h"
#include "Id.h"

class Print: public Astnode
{
  public:
    Print();
    Print(string name);
    float evaluate();
    void generateCode();
    void generatePythonCode(int level);
};

#endif

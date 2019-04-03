#ifndef WHILE_H
#define WHILE_H

using namespace std;
#include "Astnode.h"

class While: public Astnode
{
  public:
    While();
    While(string name);
    //void printNode(int level);
    float evaluate();
    void generateCode();
    void generatePythonCode(int level);
};

#endif

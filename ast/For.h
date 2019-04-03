#ifndef FOR_H
#define FOR_H

using namespace std;
#include "Astnode.h"

class For: public Astnode
{
  public:
    For();
    For(string name);
    float evaluate();
    void generateCode();
    void generatePythonCode(int level);
};

#endif

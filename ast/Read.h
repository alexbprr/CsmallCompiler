#ifndef READ_H
#define READ_H

using namespace std;
#include "Astnode.h"

class Read: public Astnode
{
  public:
    Read();
    Read(string name);
    float evaluate();
    void generateCode();
    void generatePythonCode(int level);
};

#endif

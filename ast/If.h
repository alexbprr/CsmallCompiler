#ifndef IF_H
#define IF_H

using namespace std;
#include "Astnode.h"

class If: public Astnode
{
  public:
      int generateIfTab;
      If();
      If(string name);
      float evaluate();
      void generateCode();      
      void generatePythonCode(int level);
};

#endif

#ifndef ATTR_H
#define ATTR_H

using namespace std;
#include <string>
#include "Astnode.h"
#include "Id.h"

class Attr: public Astnode
{
  public:
      Attr(string name);
      Attr(string name, Astnode* id, Astnode* expr);
      //void printNode(int level);
      float evaluate();
      void generateCode();
      void generatePythonCode(int level);
};

#endif

#ifndef EXPR_H
#define EXPR_H
using namespace std;
#include "Astnode.h"

class Expr: public Astnode
{
  protected:

  public:
      vector<Expr*> indices; //Referência para o indice do array. O indice pode ser Id ou Num
      Expr();
      Expr(string name);
      virtual void printNode(int level);
      string generateBranches(string test);
      void generatePythonCode(int level);
};

#endif

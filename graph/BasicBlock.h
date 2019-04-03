#ifndef BASICBLOCK_H
#define BASICBLOCK_H
using namespace std;
#include <vector>

class BasicBlock: public Vertex
{
  public:
    int leader; //Líder do bloco básico: é a primeira instrução do bloco básico.
    vector<int> tac_numbers; //Números identificadores da sequência de instruções desse bloco básico.
    //List<Tac*> tacList;
};

#endif

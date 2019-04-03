#ifndef OPERAND_H
#define OPERAND_H
using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include "Temp.h"

class Operand
{
  private:
  public:
    string name;
    //List<string> locations;
    //int reg; //referência para um registrador do MIPS
    //int memPos; //Posição de memória calculada a partir do stack pointer e do offset da declaração
    Temp* temporary;
    TableEntry *tableEntry;
    int type;
    string const_value; //valor de constantes numéricas
    int live; //Indica se a variável está viva no comando atual. 0: não está viva, 1: está viva
    int next_use; //Guarda o número/índice do próximo comando onde essa variável é utilizada. Caso não tenha próximo uso, next_use = -1.  
    Operand();
    virtual string getName();
    Temp* getTemporary();
    virtual void setName(string name); //Nome do operando impresso no arquivo de saída
    void setType(int type);
    void setTableEntry(TableEntry *tableEntry);
    void setTemporary(Temp* temp);
    void setContValue(string const_value);
};

#endif

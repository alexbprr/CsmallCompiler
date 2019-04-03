#ifndef TAC_H
#define TAC_H
using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include "Temp.h"
#include "Label.h"
#include "Operand.h"
#include "../symbol_table/TableEntry.h"

/*
Formatos das intruções:
0	z = x
1	z = x op y
2	if x oprel y goto L
3	ifnot x oprel y goto L
4	goto L
*/

class Tac
{
  private:
  public:
    int number; //Número Identificador da instrução de três endereços
    string name;
    int format; //Especificado acima
    Operand* dst; //O operando de destino pode ser um label também considerando que a classe Label é subclasse de Operand
    Operand* src1;
    Operand* src2;
    Label* label;
    Label* dstGoto;
    vector<string> lista_vivas; //Vetor que guarda a lista de variáveis vivas nesse comando.
    Tac();
    Tac(int format, Operand* dst, Operand* src1, Operand* src2);
    Tac(int format, Label* dstGoto, Operand* src1, Operand* src2);
    void setLabel(Label* label); //Define o label que inicia a instrução.
    //Por exemplo,
};

#endif

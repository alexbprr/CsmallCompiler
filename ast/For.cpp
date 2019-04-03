using namespace std;
#include "For.h"

For::For(){}

For::For(string name)
{
  this->name = name;
}

float For::evaluate()
{
    this->children[0]->evaluate();
    while(this->children[1]->evaluate() != 0)
    {
        this->children[3]->evaluate();
        this->children[2]->evaluate();
    }
    return 0;
}

void For::generateCode()
{
}

void For::generatePythonCode(int level)
{
  (*Astnode::pythonfile) << pythonTab(level);
  this->children[0]->generatePythonCode(level); //Gera código para inicialização
  (*Astnode::pythonfile) << "while ";
  this->children[1]->generatePythonCode(level); //Gera código para a expressão
  (*Astnode::pythonfile) << ":\n";
  this->children[3]->generatePythonCode(level+1);//Gera código para o comando
  this->children[2]->generatePythonCode(level+1);//Gera código para o incremento
  // (*Astnode::pythonfile) << "for ";
  // //O valor inicial do for é o lado direito da 1ª atribuição. Criar uma variável que não foi definida no código
  // string vars[6] = {"i","j","k","l","m","n"};
  // //string var = "i";
  // //TableEntry* te = symbolTable->getTableEntry(var);
  // //if (te != NULL)
  // //if (this->children[0]->children[0]->tableEntryRef != NULL)
  // (*Astnode::pythonfile) << "j in range(";
  //   //(*Astnode::pythonfile) << "i in range( ";
  // this->children[0]->children[1]->generatePythonCode(level);
  // (*Astnode::pythonfile) << ",";
  // //O valor final do for é a constante numérica da expressão do meio
  // if (this->children[1]->op == "<" || this->children[1]->op == "<=")
  // {
  //   this->children[1]->children[1]->generatePythonCode(level);
  //   (*Astnode::pythonfile) << "):\n";
  // }
  // this->children[3]->generatePythonCode(level+1);
}

//Definir constantes numéricas como os limites inferior e superior.  Problema complicado
//O ideal seria ter alguma indicação do programador
//Solução mais fácil: implementar com o while

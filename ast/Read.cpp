using namespace std;
#include "Read.h"
#include "Id.h"

Read::Read(){}

Read::Read(string name)
{
  this->name = name;
}

// void Read::printNode(int level)
// {
//   string deslocamento = this->tabs(level);
//   cout << deslocamento << "<Read>" << endl;
//   if (this->children.size() == 1)
//   {
//     if (this->children.at(0) != NULL)
//     {
//       this->children.at(0)->printNode(level+1);
//       cout << endl;
//     }
//     else
//        cerr << "[Read node] Referência nula para nó filho do tipo Id." << endl;
//   }
//   else cerr << "[Read node] Não foram criados todos os filhos do nó Read." << endl;
//   cout << deslocamento << "</Read>" << endl;
// }

float Read::evaluate()
{
}

void Read::generateCode()
{

}

void Read::generatePythonCode(int level)
{
  (*Astnode::pythonfile) << pythonTab(level);
  Id* id = (Id*) this->children.at(0);
  if (id->tableEntryRef->type == 0)
    (*Astnode::pythonfile) << id->tableEntryRef->getLexema() + " = int(input(\"Digite o valor da variável " + id->tableEntryRef->getLexema() + ":\"))\n";
  else
    (*Astnode::pythonfile) << id->tableEntryRef->getLexema() + " = float(input(\"Digite o valor da variável " + id->tableEntryRef->getLexema() + ":\"))\n";
}

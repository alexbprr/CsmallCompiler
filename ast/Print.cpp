using namespace std;
#include "Print.h"

Print::Print(){}

Print::Print(string name)
{
  this->name = name;
}

// void Print::printNode(int level)
// {
//   string deslocamento = this->tabs(level);
//   cout << deslocamento << "<Print>" << endl;
//   if (this->children.size() == 1)
//   {
//     if (this->children.at(0) != NULL)
//     {
//       this->children.at(0)->printNode(level+1);
//       cout << endl;
//     }
//     else
//        cerr << "[Print node] Referência nula para nó filho do tipo Expr." << endl;
//   }
//   else cerr << "[Print node] Não foram criados todos os filhos do nó Print." << endl;
//   cout << deslocamento << "</Print>" << endl;
// }

float Print::evaluate()
{
  cout << this->children[0]->evaluate() << endl;
}

void Print::generateCode()
{
  this->children[0]->generateRValueCode();
}

void Print::generatePythonCode(int level)
{
    (*Astnode::pythonfile) << pythonTab(level);
    Id* idptr = dynamic_cast<Id*>(this->children.at(0));
    if (idptr != NULL)
        (*Astnode::pythonfile) << "print(\"Valor da variável " <<
        idptr->tableEntryRef->getLexema() << ": \" + str(";
    else
        (*Astnode::pythonfile) << "print(str(";
    this->children.at(0)->generatePythonCode(level);
    (*Astnode::pythonfile) << "))\n";
}

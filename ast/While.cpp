using namespace std;
#include "While.h"

While::While(){}

While::While(string name)
{
  this->name = name;
}

// void While::printNode(int level)
// {
//   string deslocamento = this->tabs(level);
//   cout << deslocamento << "<While>" << endl;
//   if (this->children.size() == 2)
//   {
//     if (this->children.at(0) != NULL)
//     {
//       this->children.at(0)->printNode(level+1);
//       cout << endl;
//     }
//     else
//        cerr << "[While node] Referência nula para nó filho do tipo Expr." << endl;
//     if (this->children.at(1) != NULL)
//     {
//       this->children.at(1)->printNode(level+1);
//       cout << endl;
//     }
//     else
//       cerr << "[While node] Referência nula para nó filho do tipo Comando." << endl;
//   }
//   else cerr << "[While node] Não foram criados todos os filhos do nó While." << endl;
//   cout << deslocamento << "</While>" << endl;
// }

float While::evaluate()
{
  float expr_value = this->children[0]->evaluate();
  while(expr_value != 0)
  {
    this->children[1]->evaluate();
    expr_value = this->children[0]->evaluate();
  }
}

void While::generateCode()
{
  this->begin = new Label();
  this->children[0]->true_label = new Label();
  this->children[0]->false_label = this->next = new Label();
  this->children[1]->next = this->begin;
  (*Astnode::tac_file) << this->begin->getName() << ":";
  this->children[0]->generateBranchCode(); //Gera código para a expressão
  if (this->children[0]->getAddress() != NULL)
    (*Astnode::tac_file) << "if " << this->children[0]->getAddress()->getName() << " == 0 goto " <<  this->children[0]->false_label->getName() << endl;
  else
    (*Astnode::tac_file) << this->children[0]->true_label->getName() << ":";
  this->children[1]->generateCode(); //Gera código para a lista de comandos
  (*Astnode::tac_file) << "goto " << this->begin->getName() << endl;
  (*Astnode::tac_file) << this->next->getName() << ":";
}

void While::generatePythonCode(int level)
{
  (*Astnode::pythonfile) << pythonTab(level);
  (*Astnode::pythonfile) << "while ";
  this->children.at(0)->generatePythonCode(level);
  (*Astnode::pythonfile) << ":\n";
  this->children.at(1)->generatePythonCode(level+1);
}

using namespace std;
#include "If.h"

If::If(){}

If::If(string name)
{
  this->name = name;
  this->generateIfTab = 1;
}

// void If::printNode(int level)
// {
//   string deslocamento = this->tabs(level);
//   cout << deslocamento << "<If>" << endl;
//   (*Astnode::ast_file) << deslocamento << "<If>" << endl;
//   if (this->children.size() >= 2)
//   {
//     if (this->children.at(0) != NULL)
//       this->children.at(0)->printNode(level+1);
//     else
//        cerr << "[If node] Referência nula para nó filho do tipo Expr." << endl;
//     if (this->children.at(1) != NULL)
//       this->children.at(1)->printNode(level+1);
//     else
//       cerr << "[If node] Referência nula para nó filho True do tipo Comando." << endl;
//     if (this->children.size() == 3)
//     {
//       if (this->children.at(2) != NULL)
//         this->children.at(2)->printNode(level+1);
//       else
//         cerr << "[If node] Referência nula para nó filho False do tipo Comando." << endl;
//     }
//   }
//   else cerr << "[If node] Não foram criados todos os filhos do nó If." << endl;
//   cout << deslocamento << "</If>" << endl;
//   (*Astnode::ast_file) <<  deslocamento << "</If>" << endl;
// }

float If::evaluate()
{
  float expr_value = this->children[0]->evaluate();
  if (expr_value != 0 && this->children.size() == 2)
    this->children[1]->evaluate();
  else if (this->children.size() == 3)
    this->children[2]->evaluate();
}

void If::generateCode()
{
  this->next = new Label();
  if (this->children.size() == 3) //Tem else
  {
    this->children[0]->true_label = new Label();
    this->children[0]->false_label = new Label();
    this->children[0]->next = this->children[1]->next = this->next;
    this->children[0]->generateBranchCode(); //Gera código da expressão
    if (this->children[0]->getAddress() != NULL)
      (*Astnode::tac_file) << "if " << this->children[0]->getAddress()->getName() << " == 0 goto " <<  this->children[0]->false_label->getName() << endl;
    else
    {
      (*Astnode::tac_file) << this->children[0]->true_label->getName() << ": ";
    }
    this->children[1]->generateCode();
    (*Astnode::tac_file) << "goto " << this->next->getName() << endl;
    (*Astnode::tac_file) << this->children[0]->false_label->getName() << ": ";
    this->children[2]->generateCode();
  }
  else
  {
    this->children[0]->true_label = new Label();
    this->children[0]->false_label = this->children[1]->next = this->next;
    this->children[0]->generateBranchCode(); //Gera código da expressão
    if (this->children[0]->getAddress() != NULL)
      (*Astnode::tac_file) << "if " << this->children[0]->getAddress()->getName() << " == 0 goto " <<  this->children[0]->false_label->getName() << endl;
    else
    {
      (*Astnode::tac_file) << this->children[0]->true_label->getName() << ": ";
    }
    this->children[1]->generateCode();
  }
  (*Astnode::tac_file) << this->next->getName() << ": ";
}

void If::generatePythonCode(int level)
{
    if (this->generateIfTab)
    {
        (*Astnode::pythonfile) << pythonTab(level);
        (*Astnode::pythonfile) << "if ";
    }
    this->children.at(0)->generatePythonCode(level);
    (*Astnode::pythonfile) << ":\n";
    this->children.at(1)->generatePythonCode(level + 1);
    if (this->children.size() == 3)
    {
        if (this->children.at(2)->getName() == "If")
        {
            (*Astnode::pythonfile) <<  pythonTab(level) << "elif ";
            If* ifnode = (If*) this->children.at(2);
            ifnode->generateIfTab = 0;
            ifnode->generatePythonCode(level);
        }
        else
        {
            (*Astnode::pythonfile) << pythonTab(level)  << "else:\n";
            this->children.at(2)->generatePythonCode(level + 1);
        }
    }
}

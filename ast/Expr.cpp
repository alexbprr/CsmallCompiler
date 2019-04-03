using namespace std;
#include "Expr.h"

Expr::Expr(){}

Expr::Expr(string name)
{
  this->name = name;
}

void Expr::printNode(int level)
{
  string deslocamento = this->tabs(level);
  cout << deslocamento <<  "<" << this->name <<" op='" << this->op << "'> " << endl;
  (*Astnode::ast_file) << deslocamento <<  "<" << this->name <<" op='" << this->op << "'> " << endl;
  for (vector<Astnode*>::iterator it = this->children.begin(); it != this->children.end(); ++it)
  {
    (*it)->printNode(level+1);
  }
  cout << deslocamento << "</" << this->name << ">" << endl;
  (*Astnode::ast_file) << deslocamento << "</" << this->name << ">" << endl;
}

string Expr::generateBranches(string test)
{
  string s;
  Label* trueLabel = new Label();
  Label* nextLabel = new Label();

  Temp* temp = new Temp();
  this->address = new Operand();
  this->address->setTemporary(temp);
  this->address->setName(temp->getName());
  //if (this->true_label->getName() != "fall" && this->false_label->getName() != "fall")
  //{
  (*Astnode::tac_file) << "if " << test << " goto " <<  trueLabel->getName();
  (*Astnode::tac_file) << temp->name << " =  0" << endl;
  (*Astnode::tac_file) << "goto " <<  nextLabel << endl;
  (*Astnode::tac_file) << trueLabel->getName() << ":";
  (*Astnode::tac_file) << temp->name << " =  1" << endl;
  (*Astnode::tac_file) << nextLabel->getName() << ":";
  //}
  // else if (this->true_label->getName() != "fall")
  //   s = "if " + test + " goto " +  this->true_label->getName() + "\n";
  // else if (this->false_label->getName() != "fall")
  // {
  //   cout << "true label == fall" << endl;
  //   s = "ifnot " + test + " goto " +  this->false_label->getName() + "\n";
  // }
  return s;
}

// void Expr::generateRValueCode()
// {
//   // this->children.at(0)->generateRValueCode();
//   // this->children.at(1)->generateRValueCode();
//   // Temp* temp = new Temp();
//   // this->address = new Operand();
//   // this->address->setTemporary(temp);
//   // this->address->setName(temp->name);
//   // (*Astnode::tac_file) << temp->name << " = " << this->children.at(0)->getAddress()->getName() << this->op << \
//   // this->children.at(1)->getAddress()->getName() << endl;
//   // Tac* tac = new Tac(1, this->address, this->children.at(0)->getAddress(), this->children.at(1)->getAddress());
// }

// float Expr::evaluate(){}
//
// void Expr::generateCode(){}

void Expr::generatePythonCode(int level)
{
    this->children.at(0)->generatePythonCode(level);
    (*Astnode::pythonfile) << " " << this->op << " ";
    this->children.at(1)->generatePythonCode(level);
}

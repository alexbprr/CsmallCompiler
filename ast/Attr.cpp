#include <iostream>
#include "Attr.h"
using namespace std;

Attr::Attr(string name)
{
  this->name = name;
}

Attr::Attr(string name, Astnode* id, Astnode* expr)
{
  this->name = name;
  if (id != NULL)
    this->children.push_back(id);
  //if (expr != NULL)
    this->children.push_back(expr);
}

float Attr::evaluate()
{
  float expr_value = this->children[1]->evaluate();
  Id* id_node = (Id*) this->children[0];
  id_node->tableEntryRef->setValue(expr_value);
  id_node->setFloatValue(expr_value);
}

void Attr::generateCode()
{
  //Em uma atribuição, eu defino o endereço do id do lado esquerdo como sendo o endereço do temporário no lado direito
  this->children.at(0)->generateCode();
  this->children.at(1)->generateRValueCode();
  this->children.at(0)->getAddress()->setTemporary(this->children.at(1)->getAddress()->getTemporary());
  (*Astnode::tac_file) << this->children.at(0)->getAddress()->getName() << " = " << \
  this->children.at(1)->getAddress()->getName() << endl;
}

void Attr::generatePythonCode(int level)
{
  (*Astnode::pythonfile) << pythonTab(level);
  this->children.at(0)->generatePythonCode(level);
  (*Astnode::pythonfile) << " = ";
  this->children.at(1)->generatePythonCode(level);
  (*Astnode::pythonfile) << "\n";
}

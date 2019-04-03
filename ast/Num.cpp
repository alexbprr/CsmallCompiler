using namespace std;
#include "Num.h"

Num::Num(){}

Num::Num(string name, string lexema, int type)
{
  this->name = name;
  this->lexema = lexema;
  this->type = type;
  this->value = atof(this->lexema.c_str());
}

string Num::getLexema()
{
  return this->lexema;
}

void Num::printNode(int level)
{
  string deslocamento = this->tabs(level);
  if (this->type == 0)
  {
    cout << deslocamento << "<Num value=" << this->intValue << " type='integer' />" << endl;
    (*Astnode::ast_file) << deslocamento << "<Num value=" << this->intValue << " type='integer' />" << endl;
  }
  else if(this->type == 1)
  {
    cout << deslocamento << "<Num value=" << this->value << " type='float' />" << endl;
    (*Astnode::ast_file) << deslocamento << "<Num value=" << this->value << " type='float' />" << endl;
  }
}

float Num::evaluate()
{
  return this->value;
}

void Num::generateCode()
{
  Operand* operand = new Operand();
  operand->setName(this->getLexema());
  this->address = operand;
}

void Num::generateRValueCode()
{
  this->generateCode();
}

void Num::generateBranchCode()
{
  this->generateCode();
}

void Num::generatePythonCode(int level)
{
    (*Astnode::pythonfile) << this->getLexema();
}

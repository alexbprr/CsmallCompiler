using namespace std;
#include "Operand.h"

Operand::Operand()
{

}

string Operand::getName()
{
  return this->name;
}

Temp* Operand::getTemporary()
{
  return this->temporary;
}

void Operand::setName(string name)
{
  this->name = name;
}

void Operand::setType(int type)
{
  this->type = type;
}

void Operand::setTableEntry(TableEntry* te)
{
  this->tableEntry = te;
}

void Operand::setTemporary(Temp* temp)
{
  this->temporary = temp;
}

void Operand::setContValue(string const_value)
{
  this->const_value = const_value;
}

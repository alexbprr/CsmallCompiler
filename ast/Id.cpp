using namespace std;
#include "Id.h"

//copy_constructor
// Id::Id(const Id &obj) {
//    cout << "Copy constructor allocating memory." << endl;
//    //ptr = new Id();
//    tableEntryRef = *obj->tableEntryRef;
//
//    //*ptr = *obj.ptr; // copy the value
// }

Id::Id(){}

Id::Id(string name)
{
  this->name = name;
}

void Id::printNode(int level)
{
  string deslocamento = this->tabs(level);
  cout << deslocamento << "<Id";
  (*Astnode::ast_file) << deslocamento << "<Id";
  if(this->tableEntryRef != NULL)
  {
   cout << " lexema='" << this->tableEntryRef->getLexema() << "' type='" << this->tableEntryRef->getTypeName() << "' />" << endl;
   (*Astnode::ast_file) << " lexema='" << this->tableEntryRef->getLexema() << "' type='" << this->tableEntryRef->getTypeName() << "' />" << endl;
  }
  else
  {
    cout << "/>" << endl;
    (*Astnode::ast_file) << "/>" << endl;
    cerr << "Referência nula para entrada da tabela de símbolos." << endl;
  }
}

float Id::evaluate()
{
  return this->tableEntryRef->getValue();
}

void Id::generateCode()
{
  Operand* operand = new Operand();
  operand->setTableEntry(this->tableEntryRef);
  operand->setName(this->tableEntryRef->getLexema());
  this->address = operand;
}

void Id::generateRValueCode()
{
  this->generateCode();
}

void Id::generateBranchCode()
{
  this->generateCode();
}

void Id::generatePythonCode(int level)
{
  (*Astnode::pythonfile) << this->tableEntryRef->getLexema();
}

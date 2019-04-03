using namespace std;
#include "Array.h"

Array::Array()
{}

Array::Array(string name, Id* id, Arrayt* arrayt)
{
  this->name = name;
  this->arrayt = arrayt;
  this->id = id;
}

void Array::printNode(int level)
{
  Arrayt* atype;
  string deslocamento = this->tabs(level);
  cout << deslocamento << "<Array lexema=\"" << this->id->tableEntryRef->getLexema() << "\">"<< endl;
  //dimensions= " <<
    //while(atype = this->arrayt->type)
  //->dim << " >" << endl;
  string d2 = this->tabs(level + 1);
  for(vector<Expr*>::iterator it = this->indices.begin(); it != this->indices.end(); ++it)
  {
    cout << d2 << "<Indice type=\"" << (*it)->getName() << "\" value=\"" << (*it)->getValue() << "\"/>" << endl;
  }
  cout << deslocamento << "</Array>" << endl;
}

float Array::evaluate()
{
  return 0;
}

void Array::generateCode()
{

}

void Array::generateBranchCode()
{

}

void Array::generateRValueCode()
{

}

void Array::generatePythonCode(int level)
{
  (*Astnode::pythonfile) << pythonTab(level);
  if (this->isDecl)
  {
    //while (this->arrayt != )
    (*Astnode::pythonfile) << this->id->tableEntryRef->getLexema() << "";
    for(vector<Expr*>::iterator it = this->indices.begin(); it != this->indices.end(); ++it) //percorrer os indices na ordem reversa para gerar os for 
    {
      (*Astnode::pythonfile) << "[ for i in range(" << (*it)->getValue() << ")]";
    }
    (*Astnode::pythonfile) << endl;
  }
  else
  {
    (*Astnode::pythonfile) << this->id->tableEntryRef->getLexema();
    for(vector<Expr*>::iterator it = this->indices.begin(); it != this->indices.end(); ++it)
    {
      (*Astnode::pythonfile) << "[" << (*it)->getValue() << "]";
    }
    (*Astnode::pythonfile) << endl;
  }
}

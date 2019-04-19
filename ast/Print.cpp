using namespace std;
#include "Print.h"

Print::Print(){}

Print::Print(string name)
{
    this->name = name;
}

float Print::evaluate()
{
    cout << this->children[0]->evaluate() << endl;
}

void Print::generateCode()
{
    if (this->children.at(0) != NULL)
        this->children.at(0)->generateRValueCode();
}

void Print::generatePythonCode(int level)
{
    if (this->children.at(0) == NULL)
        return;
    (*Astnode::pythonfile) << pythonTab(level);
    Id* idptr = dynamic_cast<Id*>(this->children.at(0));
    if (idptr != NULL)
        (*Astnode::pythonfile) << "print(\"Valor da variável " <<
        idptr->tableEntryRef->getLexema() << ": \" + str(";
    else
        (*Astnode::pythonfile) << "print(str("; this->children.at(0)->generatePythonCode(level);
    (*Astnode::pythonfile) << "))\n";
}

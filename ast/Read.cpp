using namespace std;
#include "Read.h"
#include "Id.h"

Read::Read(){}

Read::Read(string name)
{
    this->name = name;
}

float Read::evaluate()
{}

void Read::generateCode()
{}

void Read::generatePythonCode(int level)
{
    if (this->children.at(0) == NULL)
        return;
    (*Astnode::pythonfile) << pythonTab(level);
    Id* id = (Id*) this->children.at(0);
    if (id->tableEntryRef == NULL)
        return;
    if (id->tableEntryRef->type == 0)
        (*Astnode::pythonfile) << id->tableEntryRef->getLexema() + " = int(input(\"Digite o valor da variável " + id->tableEntryRef->getLexema() + ":\"))\n";
    else
        (*Astnode::pythonfile) << id->tableEntryRef->getLexema() + " = float(input(\"Digite o valor da variável " + id->tableEntryRef->getLexema() + ":\"))\n";
}

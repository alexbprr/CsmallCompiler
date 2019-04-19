using namespace std;
#include "Id.h"

Id::Id(){}

Id::Id(string name)
{
    this->name = name;
}

Id::Id(const Id &obj)
{
    //this->tableEntryRef = obj.tableEntryRef;
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
        cerr << "{Id::printNode}: Referência nula para entrada da tabela de símbolos." << endl;
    }
}

float Id::evaluate()
{
    if(this->tableEntryRef != NULL)
        return this->tableEntryRef->getValue();
    else
        cerr << "{Id::evaluate}: Referência nula para entrada da tabela de símbolos." << endl;
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
    if(this->tableEntryRef != NULL)
        (*Astnode::pythonfile) << this->tableEntryRef->getLexema();
    else
        cerr << "{Id::generatePythonCode}: Referência nula para entrada da tabela de símbolos." << endl;

}

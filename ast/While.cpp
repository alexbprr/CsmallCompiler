using namespace std;
#include "While.h"

While::While(){}

While::While(string name)
{
  this->name = name;
}

float While::evaluate()
{
    float expr_value;
    if (this->children.at(0) != NULL)
        expr_value = this->children.at(0)->evaluate();
    else
    {
        cerr << "{While::evaluate} Expression has a NULL value" << endl;
        return 0;
    }
    int i = 0;
    while(expr_value != 0)
    {
        if (this->children.at(1) != NULL)
            this->children.at(1)->evaluate();
        else
        {
            cerr << "{While::evaluate} Command has a NULL value" << endl;
            break;
        }
        expr_value = this->children.at(0)->evaluate();
        if (i == 1000000)
            break;
        i++;
    }
    return 0;
}

void While::generateCode()
{
    if (this->children.at(0) == NULL)
        return;
    if (this->children.at(1) == NULL)
        return;
    this->begin = new Label();
    this->children[0]->true_label = new Label();
    this->children[0]->false_label = this->next = new Label();
    this->children[1]->next = this->begin;
    (*Astnode::tac_file) << this->begin->getName() << ":";
    this->children[0]->generateBranchCode(); //Gera código para a expressão
    if (this->children[0]->getAddress() != NULL)
        (*Astnode::tac_file) << "if " << this->children[0]->getAddress()->getName() << " == 0 goto " <<  this->children[0]->false_label->getName() << endl;
    else
        (*Astnode::tac_file) << this->children[0]->true_label->getName() << ":";
    this->children[1]->generateCode(); //Gera código para a lista de comandos
    (*Astnode::tac_file) << "goto " << this->begin->getName() << endl;
    (*Astnode::tac_file) << this->next->getName() << ":";
}

void While::generatePythonCode(int level)
{
    if (this->children.at(0) == NULL)
        return;
    if (this->children.at(1) == NULL)
        return;
    (*Astnode::pythonfile) << pythonTab(level);
    (*Astnode::pythonfile) << "while ";
    this->children.at(0)->generatePythonCode(level);
    (*Astnode::pythonfile) << ":\n";
    this->children.at(1)->generatePythonCode(level+1);
}

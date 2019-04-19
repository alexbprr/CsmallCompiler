using namespace std;
#include "If.h"

If::If(){}

If::If(string name)
{
    this->name = name;
    this->generateIfTab = 1;
}

float If::evaluate()
{
    if (this->children.at(0) == NULL)
        return 0;
    if (this->children.at(1) == NULL)
        return 0;
    float expr_value = this->children.at(0)->evaluate();
    if (expr_value != 0)
        this->children.at(1)->evaluate();
    else if (this->children.size() == 3) //Avalia o filho else
        if (this->children.at(2) != NULL)
            this->children.at(2)->evaluate();
}

void If::generateCode()
{
    if (this->children.at(0) == NULL)
        return;
    if (this->children.at(1) == NULL)
        return;
    this->next = new Label();
    if (this->children.size() == 3) //Tem else
    {
        if (this->children.at(2) == NULL)
            return;
        this->children[0]->true_label = new Label();
        this->children[0]->false_label = new Label();
        this->children[0]->next = this->children[1]->next = this->next;
        this->children[0]->generateBranchCode(); //Gera código da expressão
        if (this->children[0]->getAddress() != NULL)
        (*Astnode::tac_file) << "if " << this->children[0]->getAddress()->getName() << " == 0 goto " <<  this->children[0]->false_label->getName() << endl;
        else
        {
            (*Astnode::tac_file) << this->children[0]->true_label->getName() << ": ";
        }
        this->children[1]->generateCode();
        (*Astnode::tac_file) << "goto " << this->next->getName() << endl;
        (*Astnode::tac_file) << this->children[0]->false_label->getName() << ": ";
        this->children[2]->generateCode();
    }
    else
    {
        this->children[0]->true_label = new Label();
        this->children[0]->false_label = this->children[1]->next = this->next;
        this->children[0]->generateBranchCode(); //Gera código da expressão
        if (this->children[0]->getAddress() != NULL)
            (*Astnode::tac_file) << "if " << this->children[0]->getAddress()->getName() << " == 0 goto " <<  this->children[0]->false_label->getName() << endl;
        else
        {
            (*Astnode::tac_file) << this->children[0]->true_label->getName() << ": ";
        }
        this->children[1]->generateCode();
    }
    (*Astnode::tac_file) << this->next->getName() << ": ";
}

void If::generatePythonCode(int level)
{
    if (this->children.at(0) == NULL)
        return;
    if (this->children.at(1) == NULL)
        return;
    if (this->generateIfTab)
    {
        (*Astnode::pythonfile) << pythonTab(level);
        (*Astnode::pythonfile) << "if ";
    }
    this->children.at(0)->generatePythonCode(level);
    (*Astnode::pythonfile) << ":\n";
    this->children.at(1)->generatePythonCode(level + 1);
    if (this->children.size() == 3)
    {
        if (this->children.at(2) == NULL)
            return;
        if (this->children.at(2)->getName() == "If")
        {
            (*Astnode::pythonfile) <<  pythonTab(level) << "elif ";
            If* ifnode = (If*) this->children.at(2);
            ifnode->generateIfTab = 0;
            ifnode->generatePythonCode(level);
        }
        else
        {
            (*Astnode::pythonfile) << pythonTab(level)  << "else:\n";
            this->children.at(2)->generatePythonCode(level + 1);
        }
    }
}

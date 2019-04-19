using namespace std;
#include "RelOp.h"

RelOp::RelOp(){}

RelOp::RelOp(string name, string op)
{
  this->name = name;
  this->op = op;
}

float RelOp::evaluate()
{
    if (this->children.at(0) == NULL)
        return 0;
    if (this->children.at(1) == NULL)
        return 0;
    if (this->op == "==")
    {
        if (this->children.at(0)->evaluate() == this->children.at(1)->evaluate())
            return 1;
        else
            return 0;
    }
    else if (this->op == "!=")
    {
        if (this->children.at(0)->evaluate() != this->children.at(1)->evaluate())
            return 1;
        else
            return 0;
    }
    else if (this->op == ">")
    {
        if (this->children.at(0)->evaluate() > this->children.at(1)->evaluate())
            return 1;
        else
            return 0;
    }
    else if (this->op == ">=")
    {
        if (this->children.at(0)->evaluate() >= this->children.at(1)->evaluate())
            return 1;
        else
            return 0;
    }
    else if (this->op == "<")
    {
        if (this->children.at(0)->evaluate() < this->children.at(1)->evaluate())
            return 1;
        else
            return 0;
    }
    else if (this->op == "<=")
    {
        if (this->children.at(0)->evaluate() <= this->children.at(1)->evaluate())
            return 1;
        else
            return 0;
    }
}

void RelOp::generateCode(){}

void RelOp::generateRValueCode()
{
    if (this->children.at(0) == NULL)
        return;
    if (this->children.at(1) == NULL)
        return;
    Label* trueLabel = new Label();
    Label* nextLabel = new Label();
    Temp* temp = new Temp();
    this->address = new Operand();
    this->address->setTemporary(temp);
    this->address->setName(temp->getName());
    this->children[0]->generateRValueCode();
    this->children[1]->generateRValueCode();
    string test = this->children[0]->getAddress()->getName() + " " + this->op + " " + this->children[1]->getAddress()->getName();
    (*Astnode::tac_file) << "if " << test << " goto " <<  trueLabel->getName() << endl;
    (*Astnode::tac_file) << this->address->getName() << " = 0" << endl;
    (*Astnode::tac_file) << "goto " <<  nextLabel->getName() << endl;
    (*Astnode::tac_file) << trueLabel->getName() << ":" << this->address->getName() << " = 1" << endl;
    (*Astnode::tac_file) << nextLabel->getName() << ":";
}

void RelOp::generateBranchCode()
{
    if (this->children.at(0) == NULL)
        return;
    if (this->children.at(1) == NULL)
        return;
    this->children[0]->generateBranchCode();
    this->children[1]->generateBranchCode();
    string test = this->children[0]->getAddress()->getName() + " " + this->op + " " + this->children[1]->getAddress()->getName();
    if (this->true_label->getName() != "fall" && this->false_label->getName() != "fall")
    {
        (*Astnode::tac_file) << "if " << test << " goto " <<  this->true_label->getName() << endl;
        (*Astnode::tac_file) << "goto " << this->false_label->getName() << endl;
    }
    else if (this->true_label->getName() != "fall")
        (*Astnode::tac_file) << "if " << test << " goto " <<  this->true_label->getName() << endl;
    else if (this->false_label->getName() != "fall")
        (*Astnode::tac_file) << "ifnot " << test << " goto " <<  this->false_label->getName() << endl;
}

using namespace std;
#include "LogicalOp.h"

LogicalOp::LogicalOp(){}

LogicalOp::LogicalOp(string name, string op)
{
  this->name = name;
  this->op = op;
}

float LogicalOp::evaluate()
{
    if (this->children.at(0) == NULL)
        return 0;
    if (this->children.at(1) == NULL)
        return 0;
    if (this->op == "||")
        return this->children.at(0)->evaluate() || this->children.at(1)->evaluate();
    else if (this->op == "&&")
        return this->children.at(0)->evaluate() && this->children.at(1)->evaluate();
}

void LogicalOp::generateRValueCode()
{
    if (this->children.at(0) == NULL)
        return;
    if (this->children.at(1) == NULL)
        return;
    Temp* temp = new Temp();
    this->address = new Operand();
    this->address->setTemporary(temp);
    this->address->setName(temp->getName());
    this->children[0]->generateRValueCode();
    this->children[1]->generateRValueCode();
    if (this->op == "||")
    {
        Label* trueLabel = new Label();
        Label* nextLabel = new Label();
        (*Astnode::tac_file) << "if " << this->children[0]->getAddress()->getName() << " != 0 goto " <<  trueLabel->getName() << endl;
        (*Astnode::tac_file) << "if " << this->children[1]->getAddress()->getName() << " != 0 goto " <<  trueLabel->getName() << endl;
        (*Astnode::tac_file) << this->address->getName() << " = 0" << endl;
        (*Astnode::tac_file) << "goto " <<  nextLabel->getName() << endl;
        (*Astnode::tac_file) << trueLabel->getName() << ": " << this->address->getName() << " = 1" << endl;
        (*Astnode::tac_file) << nextLabel->getName() << ": ";
    }
    else if (this->op == "&&")
    {
        Label* falseLabel = new Label();
        Label* nextLabel = new Label();
        (*Astnode::tac_file) << "if " << this->children[0]->getAddress()->getName() << " == 0 goto " <<  falseLabel->getName() << endl;
        (*Astnode::tac_file) << "if " << this->children[1]->getAddress()->getName() << " == 0 goto " <<  falseLabel->getName() << endl;
        (*Astnode::tac_file) << this->address->getName() << " = 1" << endl;
        (*Astnode::tac_file) << "goto " <<  nextLabel->getName() << endl;
        (*Astnode::tac_file) << falseLabel->getName() << ": " << this->address->getName() << " = 0" << endl;
        (*Astnode::tac_file) << nextLabel->getName() << ": ";
    }
}

void LogicalOp::generateBranchCode()
{
    if (this->children.at(0) == NULL)
        return;
    if (this->children.at(1) == NULL)
        return;
    if (this->op == "||")
    {
        if (this->true_label->getName() != "fall")
            this->children[0]->true_label = this->true_label;
        else
            this->children[0]->true_label = new Label();

        this->children[0]->false_label = new Label();
        this->children[1]->true_label = this->true_label;
        this->children[1]->false_label = this->false_label;
        this->children[0]->generateBranchCode();
        if (this->children[0]->getAddress() != NULL)
            (*Astnode::tac_file) << "if " << this->children[0]->getAddress()->getName() << " != 0 goto " <<  this->children[0]->true_label->getName() << endl;
        else
        {
            //if (this->children[0]->false_label->getName() != "fall")
            (*Astnode::tac_file) << this->children[0]->false_label->getName() << ": ";
        }
        this->children[1]->generateBranchCode();
        if (this->children[1]->getAddress() != NULL)
        {
            (*Astnode::tac_file) << "if " << this->children[1]->getAddress()->getName() << " == 0 goto " <<  this->children[1]->false_label->getName() << endl;
            if (this->true_label->getName() != "fall")
                (*Astnode::tac_file) << "goto " << this->children[1]->true_label->getName() << endl;
        }
    }
    else if (this->op == "&&")
    {
        this->children[0]->true_label = new Label();
        if (this->false_label->getName() != "fall")
            this->children[0]->false_label = this->false_label;
        else
            this->children[0]->false_label = new Label();

        this->children[1]->true_label = this->true_label;
        this->children[1]->false_label = this->false_label;
        this->children[0]->generateBranchCode();
        if (this->children[0]->getAddress() != NULL) //Verifica se o nó filho é um Id, Num ou ArithOp verificando se ele possui endereço
            (*Astnode::tac_file) << "if " << this->children[0]->getAddress()->getName() << " == 0 goto " <<  this->children[0]->false_label->getName() << endl;
        else
        {
            //if (this->children[0]->true_label->getName() != "fall")
            (*Astnode::tac_file) << this->children[0]->true_label->getName() << ": ";
        }
        this->children[1]->generateBranchCode();
        if (this->children[1]->getAddress() != NULL)
        {
            (*Astnode::tac_file) << "if " << this->children[1]->getAddress()->getName() << " == 0 goto " <<  this->children[1]->false_label->getName() << endl;
            (*Astnode::tac_file) << "goto " << this->children[1]->true_label->getName() << endl;
        }
    }
}

void LogicalOp::generatePythonCode(int level)
{
    if (this->children.at(0) == NULL)
        return;
    if (this->children.at(1) == NULL)
        return;
    this->children.at(0)->generatePythonCode(level);
    if (this->op == "||")
        (*Astnode::pythonfile) << " or ";
    else
        (*Astnode::pythonfile) << " and ";
    this->children.at(1)->generatePythonCode(level);
}

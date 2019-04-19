using namespace std;
#include "ArithOp.h"

ArithOp::ArithOp(){}

ArithOp::ArithOp(string name, string op)
{
  this->name = name;
  this->op = op;
}

float ArithOp::evaluate()
{
    if (this->children.at(0) == NULL || this->children.at(1) == NULL)
        return 0;
    if (this->op == "+")
        return this->children[0]->evaluate() + this->children[1]->evaluate();
    else if (this->op == "-")
        return this->children[0]->evaluate() - this->children[1]->evaluate();
    else if (this->op == "*")
        return this->children[0]->evaluate() * this->children[1]->evaluate();
    else if (this->op == "/")
        return this->children[0]->evaluate() / this->children[1]->evaluate();
}


//   Tac* tac = new Tac(1, this->address, this->children.at(0)->getAddress(), this->children.at(1)->getAddress());
//   //coloca na lista global static list<Tac*>
void ArithOp::generateCode()
{
}

//Podemos juntar generateRValueCode e generateBranchCode em um único método
void ArithOp::generateRValueCode()
{
    if (this->children.at(0) == NULL || this->children.at(1) == NULL)
        return;
    this->children[0]->generateRValueCode();
    this->children[1]->generateRValueCode();
    Temp* temp = new Temp();
    this->address = new Operand();
    this->address->setTemporary(temp);
    this->address->setName(temp->name);
    (*Astnode::tac_file) << temp->name << " = " << this->children[0]->getAddress()->getName() << " " << this->op << " " << \
    this->children[1]->getAddress()->getName() << endl;
}

void ArithOp::generateBranchCode()
{
    if (this->children.at(0) == NULL || this->children.at(1) == NULL)
        return;
    this->children[0]->generateBranchCode();
    this->children[1]->generateBranchCode();
    Temp* temp = new Temp();
    this->address = new Operand();
    this->address->setTemporary(temp);
    this->address->setName(temp->name);
    (*Astnode::tac_file) << temp->name << " = " << this->children.at(0)->getAddress()->getName() << " " << this->op << " " << \
    this->children.at(1)->getAddress()->getName() << endl;
    //Cria um novo objeto tac definindo os operandos e os labels
}

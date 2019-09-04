#include "odemodel.h"

//Odemodel
Odemodel::Odemodel()
{
}

std::map<std::string, Equation* > Odemodel::getInitialization() const
{
    return this->initialization;
}

std::map<std::string, Equation* > Odemodel::getEquations() const
{
    return this->equations;
}

void Odemodel::printOdeModel()
{

}

//Equation
Equation::Equation()
{}

Term* Equation::getExprTreeRoot()
{
    return this->treeroot;
}

void Equation::setExprTreeRoot(Term* t)
{
    this->treeroot = t;
}

//Term
Term::Term(){}

void Term::setTName(std::string s)
{
    this->t_name = s;
}

void Term::setSignal(char s)
{
    this->t_signal = s;
}

void Term::setOp(char op)
{
    this->op = op;
}

void Term::setLeft(Term* l)
{
    this->left = l;
}

void Term::setRight(Term* r)
{
    this->right = r;
}

void Term::setType(char t)
{
    this->type = t;
}

void Term::setRepr(std::string r)
{
    this->repr = r;
}

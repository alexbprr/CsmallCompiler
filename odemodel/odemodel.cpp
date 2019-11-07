#include "odemodel.h"

//Odemodel
Odemodel::Odemodel(){}

Odemodel::~Odemodel()
{
    for (auto const &m: this->initialization)
        delete m.second;
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
    //cout << "Variables: ";
    cout << "Repr of the system of ODEs:" <<endl;
    for (vector<string>::iterator it = this->varNames.begin(); it != this->varNames.end(); ++it)
    {
        string s = *it;
        map<string,Equation*>::iterator it2 = this->getEquations().find(s);
        if(it2 != this->getEquations().end())
        {
            printf("chave found\n");
            if (it2->second->getExprTreeRoot() != NULL)
                it2->second->getExprTreeRoot()->print(0);
        }
        else
            cout << "Equation not defined for " << s << endl;
    }
    cout << "\n" << endl;
}

//Equation
Equation::Equation()
{
    this->treeroot = NULL;
}

Equation::~Equation()
{
    //delete this->treeroot;
}

Term* Equation::getExprTreeRoot()
{
    return this->treeroot;
}

void Equation::setExprTreeRoot(Term* t)
{
    this->treeroot = t;
}

//Term
Term::Term()
{
    this->t_name = "";
    this->t_signal = ' ';
    this->op = ' ';
    this->left = NULL;
    this->right = NULL;
    this->type = ' ';
    this->value = 0.;
    this->repr = "";
}

Term* Term::getLeft()
{
    return this->left;
}

Term* Term::getRight()
{
    return this->right;
}

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

string Term::tabs(int level)
{
    string deslocamento = "";
    while (level!=0)
    {
        level = level - 1;
        deslocamento += "    ";
    }
    return deslocamento;
}

void Term::print(int level)
{
    string deslocamento = this->tabs(level);
    cout << deslocamento << "<";
    if (! this->t_name.empty())
        cout << this->t_name;
    if (this->t_signal != ' ')
        cout <<  " signal=" << this->t_signal;
    if (this->op != ' ')
       cout << " op= " << this->op;
    cout << " />" << endl;
    if (this->getLeft() != NULL)
        this->getLeft()->print(level+1);
    if (this->getRight() != NULL)
        this->getRight()->print(level+1);
    //cout << deslocamento << endl;
}

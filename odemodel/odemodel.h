#ifndef odemodel_h
#define odemodel_h

#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include "../lexical_analyzer/Token.h"

class Term
{
private:
    std::string t_name; //Nome do termo (nome da variável, parâmetro)
    char t_signal;
    char op; //operador
    Term* left; //operando da esquerda
    Term* right; //operando da direita
    char type; //parâmetro, variável, função
    double value;
    std::string repr;

public:
    Term();
    string getTName();
    Term* getLeft();
    Term* getRight();
    void setTName(std::string s);
    void setSignal(char t_signal);
    void setOp(char op);
    void setLeft(Term* left);
    void setRight(Term* right);
    void setType(char type);
    void setRepr(std::string r);
    void generateRCode();
};


class Equation
{
private:
    //vector<Term*> terms; //Cada termo aponta para uma árvore de expressões
    Term* treeroot;
public:
    Equation();
    ~Equation();
    //void addTerm(Term* t);
    Term* getExprTreeRoot();
    void setExprTreeRoot(Term* e);
    void generateRCode();
};

class Odemodel
{
private:
    std::map<std::string, Equation* > initialization; //Equações de inicialização
    std::map<std::string, Equation* > equations;  //Cada variável está associada a uma equação //Conjunto dos lados direitos das EDOs

public:

    Odemodel();
    ~Odemodel();
    void addEquation(Equation* eq);
    //string getVarName() const;
    std::map<std::string, Equation* > getInitialization() const;
    std::map<std::string, Equation* > getEquations() const;
    //void setVarName(std::string vn);
    void generateRCode();
    void printOdeModel();
};


#endif

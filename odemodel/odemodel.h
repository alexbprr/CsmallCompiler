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
    string tabs(int level);

public:
    //Create copy constructor
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
    void print(int level);
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

public:
    std::map<std::string, Term*> initialization; //Equações de inicialização
    std::map<std::string, Term*> equations;  //Cada variável está associada a uma equação //Conjunto dos lados direitos das EDOs

    vector<string> varNames;
    vector<string> paramNames;
    Odemodel();
    ~Odemodel();
    //void addEquation(Equation* eq);
    //string getVarName() const;
    std::map<std::string, Term* >& getInitialization();
    std::map<std::string, Term* >& getEquations();
    //void setVarName(std::string vn);
    void generateRCode();
    void printOdeModel();
};


#endif

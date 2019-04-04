#ifndef ASTNODE_H
#define ASTNODE_H

using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <ostream>
#include <sstream>
#include <typeinfo>
#include <cstdlib>
#include "../symbol_table/SymbolTable.h"
#include "../symbol_table/TableEntry.h"
#include "../intermediate_code/Label.h"
#include "../intermediate_code/Temp.h"
#include "../intermediate_code/Operand.h"
#include "../intermediate_code/Tac.h"
#include "../intermediate_code/Fall.h"

class Astnode
{
protected:
    std::string name;
    int intValue;
    float value;
    int type;
    int isDecl;     //Define se a atribuição aparece em uma declaração com inicialização: 0 - não e 1 - sim
    Operand *address;     //Um endereço é uma referência para um objeto da classe Operand
    std::string op;
    std::vector<Astnode*> children;    //Inicializa com o tamanho 10. Automaticamente faz resize no insert e push_back
    string tempname;
    string dotname;
public:
    string lexema;
    SymbolTable* symbolTable;
    Label* begin;     //Referência para a primeira instrução da expressão do while
    Label *next;     //Referência para o label da próxima instrução após um comando
    Label *true_label;     //Referência para o label que inicia uma lista de instruções caso a condição seja verdadeira
    Label *false_label;     //Referência para o label que inicia uma lista de instruções caso a condição seja falsa
    static ofstream *ast_file;
    static ofstream *tac_file;
    static ofstream *pythonfile;
    static ofstream *dotfile;
    Astnode();
    Astnode(std::string name);
    void addChild(Astnode* node);

    std::vector<Astnode*>* getChildren();
    std::string getName();
    float getValue();
    Operand* getAddress();
    Label* getNextLabel();
    Label* getTrueLabel();
    Label* getFalseLabel();

    void setChildren(std::vector<Astnode*> children);
    void setName(std::string name);
    void setIntValue(int value);
    void setFloatValue(float value);
    void setAddress(Operand* o);
    static void setAstFile(ofstream *ast_file);
    static void setTacFile(ofstream *tac_file);
    static void setPythonFile(ofstream *pythonfile);
    static void setDotFile(ofstream *dotfile);

    string tabs(int level);
    virtual void printNode(int level);
    virtual float evaluate();
    virtual void generateCode();
    virtual void generateRValueCode();
    virtual void generateBranchCode();
    string pythonTab(int level);
    virtual void generatePythonCode(int level);
    virtual void generateDot(int level, int *cont);
};

#endif

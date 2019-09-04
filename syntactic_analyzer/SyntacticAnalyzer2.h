#ifndef SYNTACTICANALYZER2_H
#define SYNTACTICANALYZER2_H

using namespace std;
#include <vector>
#include <iterator>
#include <string>
#include "../symbol_table/SymbolTable.h"
#include "../lexical_analyzer/LexicalAnalyzer.h"
#include "../odemodel/odemodel.h"

class SyntacticAnalyzer2
{
  private:
    std::string code;
    std::string ls_var; //Variável do lado esquerdo
    int i;
    int currentType; // 0: inteiro, 1: ponto flutuante
    std::vector<Token*> tokens;

    SymbolTable* symbolTable;
    //Astnode* astTree;
    //Id* currentIdNode;
    ofstream error_file;
    ofstream odeCodeFile;

    Odemodel* ode;
    Equation* eq;

    void match(int expectedToken);
    // void Equacao();
    // void ListaTermos();
    // void Termo();
    // void TermoOpc();
    // void UnaryOp();
    // void Operando();
    // void Operador();

  public:
      Term* t_cur;
      LexicalAnalyzer* la;

    SyntacticAnalyzer2(std::vector<Token*> tokens, LexicalAnalyzer* la);
    SyntacticAnalyzer2(std::vector<Token*> tokens);
    virtual ~SyntacticAnalyzer2();
    std::vector<Token*> getTokenVector() const;
    SymbolTable& getSymbolTable() const;
    Odemodel* getOdeModel() const;
    Equation* getEquation() const;
    //Astnode& getAstTree() const;
    Odemodel* S();
    void ListaNomes(bool isvar);
    void ListaNomes2(bool isvar);
    void ListaEq();
    void ListaEq2();
    Term* Eq();
    Term* ListaT(char t_sig);
    Term* ListaT2(Term* t);
    char Binary();
    Term* Operando();
};

#endif

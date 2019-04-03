#ifndef SYNTACTICANALYZER_H
#define SYNTACTICANALYZER_H

using namespace std;
#include <vector>
#include <iterator>
#include <string>
#include "../symbol_table/SymbolTable.h"
#include "../lexical_analyzer/Token.h"
#include "../lexical_analyzer/LexicalAnalyzer.h"
#include "../ast/Astnode.h"
#include "../ast/Id.h"
#include "../ast/Num.h"
#include "../ast/Attr.h"
#include "../ast/If.h"
#include "../ast/While.h"
#include "../ast/Read.h"
#include "../ast/Print.h"
#include "../ast/For.h"
#include "../ast/Expr.h"
#include "../ast/ArithOp.h"
#include "../ast/RelOp.h"
#include "../ast/LogicalOp.h"
#include "../ast/Arrayt.h"
#include "../ast/Array.h"

class SyntacticAnalyzer
{
  private:
    int i;
    int currentType; // 0: inteiro, 1: ponto flutuante
  public:
    std::string tokensNames[N];
    LexicalAnalyzer* la;
    std::vector<Token*> tokens;
    SymbolTable* symbolTable;
    Astnode* astTree;
    Id* currentIdNode;
    ofstream error_file;

    SyntacticAnalyzer(std::vector<Token*> tokens, LexicalAnalyzer* la);
    SyntacticAnalyzer(std::vector<Token*> tokens);
    void match(int expectedToken);
    void Programa();
    void Decl_Comando(std::vector<Astnode*> *nodeList);
    void Declaracao(std::vector<Astnode*> *nodeList);
    void Tipo();
    void Decl2(std::vector<Astnode*> *nodeList);
    void Comando(std::vector<Astnode*> *nodeList);
    void AtribuicaoFor(std::vector<Astnode*> *nodeList);
    void L(std::vector<Astnode*> *nodeList, void* type, Array* array);
    Expr* Expressao();
    Expr* ExpressaoOpc(Expr* e);
    Expr* Conjuncao();
    Expr* ConjuncaoOpc(Expr* e);
    Expr* Igualdade();
    Expr* IgualdadeOpc(Expr* e);
    Expr* Relacao();
    Expr* RelacaoOpc(Expr* e);
    Expr* Adicao();
    Expr* AdicaoOpc(Expr* e);
    Expr* Termo();
    Expr* TermoOpc(Expr* e);
    Expr* Fator();
    Expr* Arranjo(Expr* node);
    Expr* Indice();
};

#endif

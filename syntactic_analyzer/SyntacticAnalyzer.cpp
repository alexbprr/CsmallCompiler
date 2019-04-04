#include "SyntacticAnalyzer.h"

using namespace std;
SyntacticAnalyzer::SyntacticAnalyzer(std::vector<Token*> tokens, LexicalAnalyzer* la)
{
  this->tokens = tokens;
  this->symbolTable = new SymbolTable();
  this->la = la;
  i = 0; //inicializa índice do vetor de tokens
  astTree = new Astnode("AST"); //Cria o nó raiz da árvore de sintaxe abstrata
  astTree->symbolTable = this->symbolTable;
  error_file.open ("error_log.txt");
  //flag_error = 0;
}

SyntacticAnalyzer::SyntacticAnalyzer(std::vector<Token*> tokens)
{
  this->tokens = tokens;
  this->symbolTable = new SymbolTable();
  i = 0; //inicializa índice do vetor de tokens
}

std::vector<Token*> SyntacticAnalyzer::getTokenVector() const
{
    return this->tokens;
}

SymbolTable& SyntacticAnalyzer::getSymbolTable() const
{
    return *(this->symbolTable);
}

Astnode& SyntacticAnalyzer::getAstTree() const
{
    return *(this->astTree);
}

void SyntacticAnalyzer::match(int expectedToken)
{
  if(this->tokens.at(i)->getTokenConstant() == expectedToken)
  {
    cout << "Token " << this->la->getTokensNames()[this->tokens.at(i)->getTokenConstant()] << " reconhecido na entrada." << endl;
    if (i < this->tokens.size())
      i++;
    else
    {
      cout << "\033[1;31merror: \033[0m end of input reached." << endl;
      error_file << "error: end of input reached." << endl;
      //exit(1);
    }
  }
  else
  {
    cout << "\033[1;31merror: \033[0m \033[1;33mline " << this->tokens.at(i)->getLineNumber() << ":\033[0m " <<
     this->la->getTokensNames()[expectedToken] << " expected." << endl;
    error_file << "error: line " << this->tokens.at(i)->getLineNumber() << ": " <<
     this->la->getTokensNames()[expectedToken] << " expected." << endl;
  }
}

void SyntacticAnalyzer::Programa()
{
  match(INT);
  match(MAIN);
  match(LBRACKET);
  match(RBRACKET);
  match(LBRACE);
  vector<Astnode*> filhos;
  Decl_Comando(&filhos);
  match(RBRACE);
  this->astTree->setChildren(filhos);
  if(this->tokens.at(i)->getTokenConstant() == EOF)
  {
    cout << "Fim da análise sintática." << endl;
    error_file.close();
  }
  else
  {
      cout << "\033[1;31merror: \033[0m \033[1;33mline " << this->tokens.at(i)->getLineNumber() << ":\033[0m " << "eof not recognized at the end of input." << endl;
      cout << "Token EOF não reconhecido no final da entrada." << endl;
  }
}

void SyntacticAnalyzer::Decl_Comando(vector<Astnode*> *nodeList)
{
  if(this->tokens.at(i)->getTokenConstant() == INT || this->tokens.at(i)->getTokenConstant() == FLOAT)
  {
    cout << "É uma declaração na linha " << this->tokens.at(i)->getLineNumber() << "." << endl;
    Declaracao(nodeList);
    Decl_Comando(nodeList);
  }
  else if (this->tokens.at(i)->getTokenConstant() == LBRACE || this->tokens.at(i)->getTokenConstant() == ID
|| this->tokens.at(i)->getTokenConstant() == IF || this->tokens.at(i)->getTokenConstant() == WHILE
|| this->tokens.at(i)->getTokenConstant() == READ || this->tokens.at(i)->getTokenConstant() == PRINT ||
this->tokens.at(i)->getTokenConstant() == FOR)
  {
    cout << "É um comando na linha " << this->tokens.at(i)->getLineNumber() << "."  << endl;
    Comando(nodeList);
    Decl_Comando(nodeList);
  }
}

void SyntacticAnalyzer::Declaracao(vector<Astnode*> *nodeList)
{
  Tipo();
  if (this->tokens.at(i)->getTokenConstant() == ID)
  {
    this->currentIdNode = new Id("Id");
    this->currentIdNode->lexema = this->tokens.at(i)->getLexema();
    TableEntry* new_entry = this->symbolTable->insertEntry(this->tokens.at(i)->getLexema(), this->tokens.at(i)->getTokenConstant(),
  this->tokens.at(i)->getLineNumber(), this->currentType);
    if (new_entry == NULL)
      error_file << "[Erro] Redeclaração de variável na linha " << this->tokens.at(i)->getLineNumber() << \
    ". Já existe um Identificador com o nome " << this->tokens.at(i)->getLexema() << endl;
    //else
    this->currentIdNode->tableEntryRef = this->symbolTable->getTableEntry(this->tokens.at(i)->getLexema());
    match(ID);
    Decl2(nodeList);
  }
}

void SyntacticAnalyzer::Tipo()
{
  if (this->tokens.at(i)->getTokenConstant() == INT)
  {
    this->currentType = 0;
    match(INT);
  }
  else if (this->tokens.at(i)->getTokenConstant() == FLOAT)
  {
    this->currentType = 1;
    match(FLOAT);
  }
}

void SyntacticAnalyzer::Decl2(vector<Astnode*> *nodeList)
{
  if (this->tokens.at(i)->getTokenConstant() == COMMA)
  {
    match(COMMA);
    if (this->tokens.at(i)->getTokenConstant() == ID)
    {
      this->currentIdNode = new Id("Id");
      this->currentIdNode->lexema = this->tokens.at(i)->getLexema();
      TableEntry* new_entry =  this->symbolTable->insertEntry(this->tokens.at(i)->getLexema(), this->tokens.at(i)->getTokenConstant(),
    this->tokens.at(i)->getLineNumber(), this->currentType);
      if (new_entry == NULL)
        error_file << "[Erro] Redeclaração de variável na linha " << this->tokens.at(i)->getLineNumber() << \
        ". Já existe um Identificador com o nome " << this->tokens.at(i)->getLexema() << endl;
      //Aponta para a entrada da tabela já existente
      this->currentIdNode->tableEntryRef = this->symbolTable->getTableEntry(this->tokens.at(i)->getLexema());
      match(ID);
      Decl2(nodeList);
    }
    else
      error_file << "Erro sintático. Identificador esperado na linha " << this->tokens.at(i)->getLineNumber() << "." << endl;
  }
  else if (this->tokens.at(i)->getTokenConstant() == PCOMMA)
  {
    match(PCOMMA);
  }
  else if (this->tokens.at(i)->getTokenConstant() == ATTR)
  {
    match(ATTR);
    Expr* expr = Expressao();
    Attr* attr_node;
    cout << "[Teste linha 139] " << this->currentIdNode->tableEntryRef->getLexema() << endl;
    if (this->currentIdNode != NULL)
      attr_node = new Attr("Attr", this->currentIdNode, expr);
    else
      cerr << "[Erro linha 141] Nó Id nulo." << endl;
    (*nodeList).push_back(attr_node);
    Decl2(nodeList);
  }
  else if (this->tokens.at(i)->getTokenConstant() == LCOL)
  {
    match(LCOL);
    int dim = atoi(this->tokens.at(i)->getLexema().c_str());
    Num* numnode = new Num("Num", this->tokens.at(i)->getLexema(), this->currentType);
    match(INTEGER_CONST);
    match(RCOL);
    Arrayt *arrayt = new Arrayt(dim,&this->currentType);
    Array* array = new Array();
    array->isDecl = true;
    array->indices.push_back(numnode);
    L(nodeList, arrayt, array);
  }
}

//Acrescentar COMMA na função L
void SyntacticAnalyzer::L(vector<Astnode*> *nodeList, void* arrayt, Array* array)
{
  if (this->tokens.at(i)->getTokenConstant() == LCOL)
  {
    match(LCOL);
    int dim = atoi(this->tokens.at(i)->getLexema().c_str());
    Num* numnode = new Num("Num", this->tokens.at(i)->getLexema(), this->currentType);
    match(INTEGER_CONST);
    match(RCOL);
    Arrayt *arrayt = new Arrayt(dim,arrayt);
    array->indices.push_back(numnode);
    L(nodeList,arrayt, array);
  }
  else if (this->tokens.at(i)->getTokenConstant() == PCOMMA)
  {
    //Cria um nó Array passando o nó Id e a expressão de tipo
    this->currentIdNode->tableEntryRef->arrayt = (Arrayt*) arrayt;
    array->id = this->currentIdNode;
    (*nodeList).push_back(array);
    match(PCOMMA);
  }
}

void SyntacticAnalyzer::Comando(vector<Astnode*> *nodeList)
{
  if (this->tokens.at(i)->getTokenConstant() == LBRACE)
  {
    match(LBRACE);
    Astnode* bloco = new Astnode("Bloco");
    Decl_Comando(bloco->getChildren());
    match(RBRACE);
    (*nodeList).push_back(bloco);
  }
  else if (this->tokens.at(i)->getTokenConstant() == ID)
  {
    Id* id_node = new Id("Id");
    id_node->tableEntryRef = this->symbolTable->getTableEntry(this->tokens.at(i)->getLexema());
    id_node->lexema = this->tokens.at(i)->getLexema();
    if (id_node->tableEntryRef == NULL)
      error_file << "[Erro] Identificador " << this->tokens.at(i)->getLexema() <<" não declarado na linha " << this->tokens.at(i)->getLineNumber() << endl;
    match(ID);
    //Verificar se tem [
    match(ATTR);
    Expr* expr = Expressao();
    Attr* attr_node = new Attr("Attr", id_node, expr);
    match(PCOMMA);
    (*nodeList).push_back(attr_node);
  }
  else if (this->tokens.at(i)->getTokenConstant() == IF)
  {
    If* if_node = new If("If");
    match(IF);
    match(LBRACKET);
    Expr* expr = Expressao();
    if_node->getChildren()->push_back(expr);
    match(RBRACKET);
    Comando(if_node->getChildren());
    if (this->tokens.at(i)->getTokenConstant() == ELSE)
    {
      match(ELSE);
      Comando(if_node->getChildren());
    }
    (*nodeList).push_back(if_node);
  }
  else if (this->tokens.at(i)->getTokenConstant() == WHILE)
  {
    While* while_node = new While("While");
    match(WHILE);
    match(LBRACKET);
    Expr* expr = Expressao();
    while_node->getChildren()->push_back(expr);
    match(RBRACKET);
    Comando(while_node->getChildren());
    (*nodeList).push_back(while_node);
  }
  else if (this->tokens.at(i)->getTokenConstant() == READ)
  {
    Read* read_node = new Read("Read");
    match(READ);
    Id* id_node = new Id("Id");
    id_node->tableEntryRef = this->symbolTable->getTableEntry(this->tokens.at(i)->getLexema());
    read_node->getChildren()->push_back(id_node);
    match(ID);
    match(PCOMMA);
    (*nodeList).push_back(read_node);
  }
  else if (this->tokens.at(i)->getTokenConstant() == PRINT)
  {
    Print* print_node = new Print("Print");
    match(PRINT);
    match(LBRACKET);
    Expr* expr = Expressao();
    print_node->getChildren()->push_back(expr);
    match(RBRACKET);
    match(PCOMMA);
    (*nodeList).push_back(print_node);
  }
  else if (this->tokens.at(i)->getTokenConstant() == FOR)
  {
    For* for_node = new For("For");
    match(FOR);
    match(LBRACKET);
    AtribuicaoFor(for_node->getChildren());
    match(PCOMMA);
    for_node->getChildren()->push_back(Expressao());
    match(PCOMMA);
    AtribuicaoFor(for_node->getChildren());
    match(RBRACKET);
    Comando(for_node->getChildren());
    (*nodeList).push_back(for_node);
  }
}

void SyntacticAnalyzer::AtribuicaoFor(vector<Astnode*> *nodeList)
{
  Id* id_node = new Id("Id");
  id_node->tableEntryRef = this->symbolTable->getTableEntry(this->tokens.at(i)->getLexema());
  id_node->lexema = this->tokens.at(i)->getLexema();
  if (id_node->tableEntryRef == NULL)
    error_file << "[Erro] Identificador " << this->tokens.at(i)->getLexema() <<" não declarado na linha " << this->tokens.at(i)->getLineNumber() << endl;
  match(ID);
  match(ATTR);
  Expr* expr = Expressao();
  Attr* attr_node = new Attr("Attr", id_node, expr);
  (*nodeList).push_back(attr_node);
}

Expr* SyntacticAnalyzer::Expressao()
{
  Expr* expr1 = Conjuncao();
  return ExpressaoOpc(expr1);
}

Expr* SyntacticAnalyzer::ExpressaoOpc(Expr* expr1)
{
  if(this->tokens.at(i)->getTokenConstant() == OR)
  {
    match(OR);
    Expr* expr2 = Conjuncao();
    LogicalOp* logicalop_node = new LogicalOp("LogicalOp", "||");
    logicalop_node->addChild(expr1);
    logicalop_node->addChild(expr2);
    return ExpressaoOpc(logicalop_node);
  }
  return expr1;
}

Expr* SyntacticAnalyzer::Conjuncao()
{
  Expr* expr1 = Igualdade();
  return ConjuncaoOpc(expr1);
}

Expr* SyntacticAnalyzer::ConjuncaoOpc(Expr* expr1)
{
  if(this->tokens.at(i)->getTokenConstant() == AND)
  {
    match(AND);
    Expr* expr2 = Igualdade();
    LogicalOp* logicalop_node = new LogicalOp("LogicalOp", "&&");
    logicalop_node->addChild(expr1);
    logicalop_node->addChild(expr2);
    return ConjuncaoOpc(logicalop_node);
  }
  return expr1;
}

Expr* SyntacticAnalyzer::Igualdade()
{
  Expr* expr1 = Relacao();
  return IgualdadeOpc(expr1);
}

Expr* SyntacticAnalyzer::IgualdadeOpc(Expr* expr1)
{
  if(this->tokens.at(i)->getTokenConstant() == EQ)
  {
    match(EQ);
    Expr* expr2 = Relacao();
    RelOp* relop_node = new RelOp("RelOp", "==");
    relop_node->addChild(expr1);
    relop_node->addChild(expr2);
    return IgualdadeOpc(relop_node);
  }
  else if(this->tokens.at(i)->getTokenConstant() == NE)
  {
    match(NE);
    Expr* expr2 = Relacao();
    RelOp* relop_node = new RelOp("RelOp", "!=");
    relop_node->addChild(expr1);
    relop_node->addChild(expr2);
    return IgualdadeOpc(relop_node);
  }
  return expr1;
}

Expr* SyntacticAnalyzer::Relacao()
{
  Expr* expr1 = Adicao();
  return RelacaoOpc(expr1);
}

Expr* SyntacticAnalyzer::RelacaoOpc(Expr* expr1)
{
  if(this->tokens.at(i)->getTokenConstant() == LT)
  {
    match(LT);
    Expr* expr2 = Adicao();
    RelOp* relop_node = new RelOp("RelOp", "<");
    relop_node->addChild(expr1);
    relop_node->addChild(expr2);
    return RelacaoOpc(relop_node);
  }
  else if(this->tokens.at(i)->getTokenConstant() == LE)
  {
    match(LE);
    Expr* expr2 = Adicao();
    RelOp* relop_node = new RelOp("RelOp", "<=");
    relop_node->addChild(expr1);
    relop_node->addChild(expr2);
    return RelacaoOpc(relop_node);
  }
  else if(this->tokens.at(i)->getTokenConstant() == GT)
  {
    match(GT);
    Expr* expr2 = Adicao();
    RelOp* relop_node = new RelOp("RelOp", ">");
    relop_node->addChild(expr1);
    relop_node->addChild(expr2);
    return RelacaoOpc(relop_node);
  }
  else if(this->tokens.at(i)->getTokenConstant() == GE)
  {
    match(GE);
    Expr* expr2 = Adicao();
    RelOp* relop_node = new RelOp("RelOp", ">=");
    relop_node->addChild(expr1);
    relop_node->addChild(expr2);
    return RelacaoOpc(relop_node);
  }
  return expr1;
}

Expr* SyntacticAnalyzer::Adicao()
{
  Expr* expr1 = Termo();
  return AdicaoOpc(expr1);
}

Expr* SyntacticAnalyzer::AdicaoOpc(Expr* expr1)
{
  if(this->tokens.at(i)->getTokenConstant() == PLUS)
  {
    match(PLUS);
    Expr* expr2 = Termo();
    ArithOp* arithop_node = new ArithOp("ArithOp", "+");
    arithop_node->addChild(expr1);
    arithop_node->addChild(expr2);
    return AdicaoOpc(arithop_node);
  }
  else if(this->tokens.at(i)->getTokenConstant() == MINUS)
  {
    match(MINUS);
    Expr* expr2 = Termo();
    ArithOp* arithop_node = new ArithOp("ArithOp", "-");
    arithop_node->addChild(expr1);
    arithop_node->addChild(expr2);
    return AdicaoOpc(arithop_node);
  }
  return expr1;
}

Expr* SyntacticAnalyzer::Termo()
{
  Expr* expr1 = Fator();
  return TermoOpc(expr1);
}

Expr* SyntacticAnalyzer::TermoOpc(Expr* expr1)
{
  if(this->tokens.at(i)->getTokenConstant() == MULT)
  {
    match(MULT);
    Expr* expr2 = Fator();
    ArithOp* arithop_node = new ArithOp("ArithOp", "*");
    arithop_node->addChild(expr1);
    arithop_node->addChild(expr2);
    return TermoOpc(arithop_node);
  }
  else if(this->tokens.at(i)->getTokenConstant() == DIV)
  {
    match(DIV);
    Expr* expr2 = Fator();
    ArithOp* arithop_node = new ArithOp("ArithOp", "/");
    arithop_node->addChild(expr1);
    arithop_node->addChild(expr2);
    return TermoOpc(arithop_node);
  }
  return expr1;
}

Expr* SyntacticAnalyzer::Indice()
{
  if (this->tokens.at(i)->getTokenConstant() == ID)
  {
    Id* id_node = new Id("Id");
    id_node->tableEntryRef = this->symbolTable->getTableEntry(this->tokens.at(i)->getLexema());
    match(ID);
    return id_node;
  }
  else if (this->tokens.at(i)->getTokenConstant() == INTEGER_CONST)
  {
    Num* numnode = new Num("Num", this->tokens.at(i)->getLexema(), 0);
    match(INTEGER_CONST);
    return numnode;
  }
  cout << "Erro sintático. Identificador ou contante numérica esperada." << endl;
  return NULL;
}

Expr* SyntacticAnalyzer::Arranjo(Expr* array)
{
  if (this->tokens.at(i)->getTokenConstant() == LCOL)
  {
    match(LCOL);
    Expr* indice = Indice();
    match(RCOL);
    array->indices.push_back(indice);
    return Arranjo(array);
  }
  return array;
}

Expr* SyntacticAnalyzer::Fator()
{
  if (this->tokens.at(i)->getTokenConstant() == ID)
  {
    Id* id_node = new Id("Id");
    id_node->tableEntryRef = this->symbolTable->getTableEntry(this->tokens.at(i)->getLexema());
    id_node->lexema = this->tokens.at(i)->getLexema();
    if (id_node->tableEntryRef == NULL)
      error_file << "[Erro] Identificador " << this->tokens.at(i)->getLexema() <<" não declarado na linha " << this->tokens.at(i)->getLineNumber() << endl;
    match(ID);
    if (this->tokens.at(i)->getTokenConstant() == LCOL)
    {
      Array* array = new Array("Array", id_node, id_node->tableEntryRef->arrayt);
      return Arranjo(array);
    }
    return id_node;
  }
  else if (this->tokens.at(i)->getTokenConstant() == LBRACKET)
  {
    match(LBRACKET);
    Expr* expr = Expressao();
    match(RBRACKET);
    return expr;
  }
  else if (this->tokens.at(i)->getTokenConstant() == INTEGER_CONST)
  {
    Num* num_node = new Num("Num", this->tokens.at(i)->getLexema(), 0);
    stringstream ss(this->tokens.at(i)->getLexema());
    int aux;
    ss >> aux;
    num_node->setIntValue(aux);
    num_node->setFloatValue(aux);
    match(INTEGER_CONST); //cria um objeto Int_Const
    return num_node;
  }
  else if (this->tokens.at(i)->getTokenConstant() == FLOAT_CONST)
  {
    Num* num_node = new Num("Num", this->tokens.at(i)->getLexema(), 1);
    stringstream ss(this->tokens.at(i)->getLexema());
    float aux;
    ss >> aux;
    num_node->setFloatValue(aux);
    match(FLOAT_CONST);//Cria um objeto Float_const
    return num_node;
  }
  else
  {
    cout << "Erro sintático. Identificador, abre parênteses ou contante numérica esperada na linha " <<
    this->tokens.at(i)->getLineNumber() << "." << endl;
    return NULL;
  }
}

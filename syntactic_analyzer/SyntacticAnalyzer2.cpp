#include "SyntacticAnalyzer2.h"

using namespace std;

//#include <unordered_map>

template<typename K, typename V>
void print_map(std::map<K,V> const &m)
{
    for (auto const& pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

SyntacticAnalyzer2::SyntacticAnalyzer2(std::vector<Token*> tokens, LexicalAnalyzer* la)
{
    this->tokens = tokens;
    this->symbolTable = new SymbolTable();
    this->la = la;
    i = 0; //inicializa índice do vetor de tokens
    //astTree = new Astnode("AST"); //Cria o nó raiz da árvore de sintaxe abstrata
    //astTree->symbolTable = this->symbolTable;
    error_file.open ("error_log.txt");
    //flag_error = 0;
    odeCodeFile.open("OdePythonCode.py");
    this->code = "";
}

SyntacticAnalyzer2::SyntacticAnalyzer2(std::vector<Token*> tokens)
{
    this->tokens = tokens;
    this->symbolTable = new SymbolTable();
    i = 0; //inicializa índice do vetor de tokens
}

SyntacticAnalyzer2::~SyntacticAnalyzer2()
{
    //delete this->symbolTable;
    // error_file.close();
    // odeCodeFile.close();
}

std::vector<Token*> SyntacticAnalyzer2::getTokenVector() const
{
    return this->tokens;
}

SymbolTable& SyntacticAnalyzer2::getSymbolTable() const
{
    return *(this->symbolTable);
}

// Astnode& SyntacticAnalyzer2::getAstTree() const
// {
//     return *(this->astTree);
// }

void SyntacticAnalyzer2::match(int expectedToken)
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
        if (this->la->getLexema(expectedToken) != "")
        {
            cout << "\033[1;31merror: \033[0m \033[1;33mline " << this->tokens.at(i)->getLineNumber() << ":\033[0m " <<
            this->la->getLexema(expectedToken) << " expected." << endl;
            error_file << "error: line " << this->tokens.at(i)->getLineNumber() << ": " <<
                this->la->getLexema(expectedToken) << " expected" << endl;
        }
        else
        {
            cout << "\033[1;31merror: \033[0m \033[1;33mline " << this->tokens.at(i)->getLineNumber() << ":\033[0m " <<
                this->la->getTokensNames()[expectedToken] << " expected." << endl;
            error_file << "error: line " << this->tokens.at(i)->getLineNumber() << ": " <<
                this->la->getTokensNames()[expectedToken] << " expected" << endl;
        }
    }
}

//this->ls_var = this->tokens.at(i)->getLexema();
//this->code += this->tokens.at(i)->getLexema() + "=" + "(";

Odemodel* SyntacticAnalyzer2::S()
{
    //Create a new odemodel that will be returned
    this->ode = new Odemodel();
    if(this->tokens.at(i)->getTokenConstant() == VARS)
    {
        match(VARS);
        ListaNomes(true);
        match(PARAMS);
        ListaNomes(false);
        match(INI);
        ListaEq(true);
        match(PCOMMA);
        ListaEq(false);
        //if(this->tokens.at(i)->getTokenConstant() == EOF)
        {
            cout << "Fim da análise sintática." << endl;
            //odeCodeFile << this->code;
            error_file.close();
            odeCodeFile.close();
            //Print hashmaps
            print_map(this->ode->initialization);
            return this->ode;
        }

    }
    return NULL;
}

void SyntacticAnalyzer2::ListaNomes(bool isvar)
{
    if(this->tokens.at(i)->getTokenConstant() == ID)
    {
        TableEntry* ne = this->symbolTable->insertEntry(this->tokens.at(i)->getLexema(), this->tokens.at(i)->getTokenConstant(), 0);
        ne->setIsVar(isvar);
        if (isvar)
            this->ode->varNames.push_back(this->tokens.at(i)->getLexema());
        else
            this->ode->paramNames.push_back(this->tokens.at(i)->getLexema());
        match(ID);
        ListaNomes2(isvar);
    }
}

void SyntacticAnalyzer2::ListaNomes2(bool isvar)
{
    if(this->tokens.at(i)->getTokenConstant() == COMMA)
    {
        match(COMMA);
        TableEntry* ne = this->symbolTable->insertEntry(this->tokens.at(i)->getLexema(), this->tokens.at(i)->getTokenConstant(), 0);
        ne->setIsVar(isvar);
        if (isvar)
            this->ode->varNames.push_back(this->tokens.at(i)->getLexema());
        else
            this->ode->paramNames.push_back(this->tokens.at(i)->getLexema());
        match(ID);
        ListaNomes2(isvar);
    }
}

//ListaEq -> id =  Eq ; ListaEq2
// ListaEq2 -> id =  Eq ; ListaEq2 | e
// Eq → Unary ListaT | ListaT
void SyntacticAnalyzer2::ListaEq(bool isini)
{
    if(this->tokens.at(i)->getTokenConstant() == ID)
    {
        //Começa o reconhecimento de uma equação.
        //Associa uma nova equação à variável atual: Cria a equação para a variável e insere no hashmap
        std::map<string, Term*> map_;
        string varname = this->tokens.at(i)->getLexema();
        printf("Varname: %s\n",varname.c_str());

        match(ID);
        match(ATTR);
        Term* root = Eq();
        printf("----Testing tree: \n");
        root->print(0);
        if (isini)
        {
            this->ode->getInitialization()[varname] = root;
        }
        else
        {
            this->ode->getEquations()[varname] = root;
        }

        match(PCOMMA);
        ListaEq2(isini);
    }
}

void SyntacticAnalyzer2::ListaEq2(bool isini)
{
    if(this->tokens.at(i)->getTokenConstant() == ID)
    {
        //this->ode->getEquations()[this->tokens.at(i)->getLexema()] = new Equation();
        string varname = this->tokens.at(i)->getLexema();
        printf("Varname: %s\n",varname.c_str());
        match(ID);
        match(ATTR);
        Term* root = Eq();
        printf("----Testing tree: \n");
        root->print(0);
        if (isini)
        {
            this->ode->getInitialization()[varname] = root;
        }
        else
        {
            this->ode->getEquations()[varname] = root;
        }
        match(PCOMMA);
        ListaEq2(isini);
    }
}

Term* SyntacticAnalyzer2::Eq()
{
    char t_sig = ' ';
    //Term* termo = new Term();
    if(this->tokens.at(i)->getTokenConstant() == PLUS)
    {
        match(PLUS);
        //Cria um termo e passa para ListaT
        //termo->setSignal('+');
        t_sig = '+';
        //Define o sinal para o termo que será reconhecido a seguir

        //Passa o signal como parênteses
        return ListaT(t_sig);
    }
    else if(this->tokens.at(i)->getTokenConstant() == MINUS)
    {
        match(MINUS);
        //termo->setSignal('-');
        t_sig = '-';
        return ListaT(t_sig);
    }
    else
    {
        return ListaT(t_sig);
    }
}

//ListaT →  Operando ListaT2
//ListaT2 → Binary Operando ListaT2 | e
Term* SyntacticAnalyzer2::ListaT(char t_sig)
{
    //Term* termo = new Term();
    Term* termo = Operando();//Preenche o filho da esquerda
    termo->setSignal(t_sig);
    //printf("Cheguei antes de ListaT2\n");
    Term* root = ListaT2(termo);
    return root;
}

Term* SyntacticAnalyzer2::ListaT2(Term* t1)
{
    if (this->tokens.at(i)->getTokenConstant() == PLUS || this->tokens.at(i)->getTokenConstant() == MINUS
    || this->tokens.at(i)->getTokenConstant() == MULT || this->tokens.at(i)->getTokenConstant() == DIV)
    {
        char op = Binary(); //Preenche a operação
        Term* t2 = Operando(); //Preenche o filho da direita
        Term* t = new Term();
        t->setLeft(t1);
        t->setRight(t2);
        t->setOp(op);
        return ListaT2(t);
    }
    return t1;
}

//Ação semântica para identificar se um ID é válido (ou seja, se refere-se a uma var ou param)
// std::string t_name; //Nome do termo (nome da variável, parâmetro)
// char t_signal;
// char op; //operador
// Term* left; //operando da esquerda
// Term* right; //operando da direita
// char type; //parâmetro, variável, função
// double value;
Term* SyntacticAnalyzer2::Operando()
{
    if (this->tokens.at(i)->getTokenConstant() == ID)
    {
        Term *nt = NULL;
        //Cria um novo termo e retorna ele
        //Consulta a tabela de símbolos para verificar se é uma var ou param
        TableEntry* te = this->symbolTable->getTableEntry(this->tokens.at(i)->getLexema());
        if (te!=NULL)
        {

            //if (te->isvar)
            nt = new Term();
            nt->setTName(te->getLexema());
        }
        else
        {
            cout << "error: variável ou parâmetro não definido" << endl;
        }
        match(ID);
        return nt;
    }
    else if (this->tokens.at(i)->getTokenConstant() == INTEGER_CONST)
    {
        Term* nt = new Term();
        nt->setTName(this->tokens.at(i)->getLexema());
        match(INTEGER_CONST);
        return nt;
    }
    else if (this->tokens.at(i)->getTokenConstant() == FLOAT_CONST)
    {
        Term* nt = new Term();
        nt->setTName(this->tokens.at(i)->getLexema());
        match(FLOAT_CONST);
        return nt;
    }
    else if (this->tokens.at(i)->getTokenConstant() == LBRACKET)
    {
        match(LBRACKET);
        Term* t = Eq();
        match(RBRACKET);
        return t;
    }
    return NULL;
}

char SyntacticAnalyzer2::Binary()
{
    if (this->tokens.at(i)->getTokenConstant() == PLUS)
    {
        match(PLUS);
        return '+';
    }
    else if (this->tokens.at(i)->getTokenConstant() == MINUS)
    {
        match(MINUS);
        return '-';
    }
    else if (this->tokens.at(i)->getTokenConstant() == MULT)
    {
        match(MULT);
        return '*';
    }
    else if (this->tokens.at(i)->getTokenConstant() == DIV)
    {
        match(DIV);
        return '/';
    }
    return ' ';
}

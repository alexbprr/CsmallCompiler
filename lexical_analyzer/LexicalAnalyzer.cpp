#include "LexicalAnalyzer.h"

ofstream *LexicalAnalyzer::lexical_file;

LexicalAnalyzer::LexicalAnalyzer() {}

void LexicalAnalyzer::setLexicalFile(ofstream *lexical_file)
{
  LexicalAnalyzer::lexical_file = lexical_file;
}

LexicalAnalyzer::LexicalAnalyzer(int s, IO *io_)
{
    state = s;
    useLastChar = false;
    io = io_;
    reservedWords["main"] = MAIN;
    reservedWords["int"] = INT;
    reservedWords["float"] = FLOAT;
    reservedWords["if"] = IF;
    reservedWords["else"] = ELSE;
    reservedWords["while"] = WHILE;
    reservedWords["read"] = READ;
    reservedWords["print"] = PRINT;
    reservedWords["for"] = FOR;
    tokensNames[MAIN] = "MAIN";
    tokensNames[ID] = "ID";
    tokensNames[INT] = "INT";
    tokensNames[FLOAT] = "FLOAT";
    tokensNames[IF] = "IF";
    tokensNames[ELSE] = "ELSE";
    tokensNames[WHILE] = "WHILE";
    tokensNames[READ] = "READ";
    tokensNames[PRINT] = "PRINT";
    tokensNames[FOR] = "FOR";
    tokensNames[LBRACE] = "LBRACE";
    tokensNames[RBRACE] = "RBRACE";
    tokensNames[COMMA] = "COMMA";
    tokensNames[PCOMMA] = "PCOMMA";
    tokensNames[LBRACKET] = "LBRACKET";
    tokensNames[RBRACKET] = "RBRACKET";
    tokensNames[ATTR] = "ATTR";
    tokensNames[OR] = "OR";
    tokensNames[AND] = "AND";
    tokensNames[EQ] = "EQ";
    tokensNames[NE] = "NE";
    tokensNames[LT] = "LT";
    tokensNames[LE] = "LE";
    tokensNames[GT] = "GT";
    tokensNames[GE] = "GE";
    tokensNames[PLUS] = "PLUS";
    tokensNames[MINUS] = "MINUS";
    tokensNames[MULT] = "MULT";
    tokensNames[DIV] = "DIV";
    tokensNames[INTEGER_CONST] = "INTEGER_CONST";
    tokensNames[FLOAT_CONST] = "FLOAT_CONST";
    tokensNames[LCOL] = "LCOL";
    tokensNames[RCOL] = "RCOL";
}

LexicalAnalyzer::~LexicalAnalyzer()
{
    //dtor
}

void LexicalAnalyzer::returnToInitialState()
{
    useLastChar = true;
    state = 1;
    lexema.clear();
}


void LexicalAnalyzer::analyze()
{

    int lineNumber = 1; ///guarda o número atual da linha do código-fonte
    char c = io->getNextChar(); ///lê o próximo caractere do buffer
    Token *token;
    std::map<string,int>::iterator reservedWordsIterator;
    int aux = 0;
    while(!io->isEOF()) ///eof_ == 1: cheguei ao fim do arquivo
    {
        useLastChar = false;
        switch(state)
        {
        case 1:
            if(isalpha(c))
            {
                lexema.push_back(c);
                state = 2;
            }
            else if(isdigit(c))
            {
                lexema.push_back(c);
                state = 3;
            }
            else if(c == '{')
            {
                token = new Token("LBRACE",lineNumber,LBRACE, "{");
                tokens.push_back(token);
            }
            else if(c == '}')
            {
                token = new Token("RBRACE",lineNumber,RBRACE, "}");
                tokens.push_back(token);
            }
            else if(c == '(')
            {
                token = new Token("LBRACKET",lineNumber,LBRACKET, "(");
                tokens.push_back(token);
            }
            else if(c == ')')
            {
                token = new Token("RBRACKET",lineNumber,RBRACKET, ")");
                tokens.push_back(token);
            }
            else if(c == '[')
            {
                token = new Token("LCOL",lineNumber,LCOL, "[");
                tokens.push_back(token);
                state = 5;
            }
            else if(c == ']')
            {
                token = new Token("RCOL",lineNumber,RCOL, "]");
                tokens.push_back(token);
            }
            else if(c == ',')
            {
                token = new Token("COMMA",lineNumber,COMMA, ",");
                tokens.push_back(token);
            }
            else if(c == ';')
            {
                token = new Token("PCOMMA",lineNumber,PCOMMA, ";");
                tokens.push_back(token);
            }
            else if (c == '&')
            {
                c = io->getNextChar();
                if(c == '&')
                {
                    token = new Token("AND", lineNumber, AND, "&&");
                    tokens.push_back(token);
                    state = 1;
                }
                else
                {
                    cerr << "Erro! Operador & indefinido na linguagem. " << endl;
                    returnToInitialState();
                }
            }
            else if (c == '|')
            {
                c = io->getNextChar();
                if(c == '|')
                {
                    token = new Token("OR", lineNumber, OR, "||");
                    tokens.push_back(token);
                    state = 1;
                }
                else
                {
                    cerr << "Erro! Operador | indefinido na linguagem. " << endl;
                    returnToInitialState();
                }
            }
            else if (c == '=')
            {
                c = io->getNextChar();
                if(c == '=')
                {
                    token = new Token("EQ", lineNumber, EQ, "==");
                    state = 1;
                }
                else
                {
                    token = new Token("ATTR", lineNumber, ATTR, "=");
                    returnToInitialState();
                }
                tokens.push_back(token);
            }
            else if (c == '!')
            {
                c = io->getNextChar();
                if(c == '=')
                {
                    token = new Token("NE", lineNumber, NE, "!=");
                    tokens.push_back(token);
                    state = 1;
                }
                else
                {
                    cerr << "Erro! Operador ! indefinido na linguagem. " << endl;
                    returnToInitialState();
                }
            }
            else if (c == '<')
            {
                c = io->getNextChar();
                if(c == '=')
                {
                    token = new Token("LE", lineNumber, LE, "<=");
                    state = 1;
                }
                else
                {
                    token = new Token("LT", lineNumber, LT, "<");
                    returnToInitialState();
                }
                tokens.push_back(token);
            }
            else if (c == '>')
            {
                c = io->getNextChar();
                if(c == '=')
                {
                    token = new Token("GE", lineNumber, GE, ">=");
                    state = 1;
                }
                else
                {
                    token = new Token("GT", lineNumber, GT, ">");
                    returnToInitialState();
                }
                tokens.push_back(token);
            }
            else if (c == '+')
            {
                token = new Token("PLUS", lineNumber, PLUS, "+");
                tokens.push_back(token);
                state = 1;
            }
            else if (c == '-')
            {
                token = new Token("MINUS", lineNumber, MINUS, "-");
                tokens.push_back(token);
                state = 1;
            }
            else if (c == '*')
            {
                token = new Token("MULT", lineNumber, MULT, "*");
                tokens.push_back(token);
                state = 1;
            }
            else if (c == '/')
            {
                token = new Token("DIV", lineNumber, DIV, "/");
                tokens.push_back(token);
                state = 1;
            }
            else
            if(c == '\n')
                lineNumber++;
            else if(c == '\r')
            {
                c = io->getNextChar();
                if(c == '\n')
                    lineNumber++;
                else
                  useLastChar = true;
            }
            else
                if(c == ' ' || c == '\t')
                {
                    while(c == ' ' || c == '\t')
                    {
                        c = io->getNextChar();
                    }
                    useLastChar = true;
                }
            else
            {
                if (c != ' ' && lexema != " ")
                {
                    cerr << "Erro! O caractere " << c << " nao foi reconhecido. " << endl;
                    if(lexema.length() > 0){
                        cerr << "Lexema " << lexema << " nao foi reconhecido. " << endl;
                        lexema.clear();
                    }
                    useLastChar = false;
                }
            }
            break;
        case 2:
            while(isalpha(c) || isdigit(c) || c == '_')
            {
                //cout << "Char " << c << endl;
                lexema.push_back(c);
                c = io->getNextChar();
            }
            ///verifica se é palavra reservada
            reservedWordsIterator = reservedWords.find(lexema);
            if(reservedWordsIterator != reservedWords.end())///o lexema é uma palavra reservada
            {
                token = new Token(tokensNames[reservedWords[lexema]],lineNumber,reservedWords[lexema], lexema);
            }
            else  ///o lexema é um nome de identificador
            {
                token = new Token("ID",lineNumber,ID,lexema);
            }
            tokens.push_back(token);
            returnToInitialState();
            break;
        case 3:
            while(isdigit(c))
            {
                lexema.push_back(c);
                c = io->getNextChar();
            }
            if(c == '.')
            {
                lexema.push_back(c);
                state = 4;
            }
            else
            {
                token = new Token("INTEGER_CONST", lineNumber,INTEGER_CONST,lexema);
                tokens.push_back(token);
                returnToInitialState();
            }
            break;
        case 4:
            while(isdigit(c))
            {
                lexema.push_back(c);
                c = io->getNextChar();
            }
            token = new Token("FLOAT_CONST", lineNumber,FLOAT_CONST,lexema);
            tokens.push_back(token);
            returnToInitialState();
            break;
        case 5:
            while(isdigit(c))
            {
                lexema.push_back(c);
                c = io->getNextChar();
            }
            token = new Token("INTEGER_CONST", lineNumber,INTEGER_CONST,lexema);
            tokens.push_back(token);
            returnToInitialState();
            break;
        default:
            break;

        } ///fim do switch

        if (useLastChar == false)
            c = io->getNextChar();
        //cout << "Char " << c << endl;
    }///fim do while
}

void LexicalAnalyzer::printTokenBuffer()
{
    Token *t;
    cout << "-------Token Buffer------------" <<endl;
    cout << std::setw(15) << std::left << "Token" << "| ";
    cout << "Num. da Linha" << " | ";
    cout << std::left << "Lexema" << endl;
    cout << "----------------------------------------------- " <<endl;
    for (vector<Token*>::iterator tk = tokens.begin(); tk != tokens.end(); ++tk)
    {
        t = (Token*) *tk;
        cout << std::setw(15) << std::left << t->getName() << "  ";
        cout << t->getLineNumber() << " \t\t ";
        cout << std::setw(10) << std::left << t->getLexema() << endl;
    }
    cout << "---------------------------------" <<endl;
}

void LexicalAnalyzer::saveTokenBuffer()
{
    Token *t;
    (*LexicalAnalyzer::lexical_file) << "-------Token Buffer------------" <<endl;
    (*LexicalAnalyzer::lexical_file) << std::setw(15) << std::left << "Token" << "| ";
    (*LexicalAnalyzer::lexical_file) << "Num. da Linha" << " | ";
    (*LexicalAnalyzer::lexical_file) << std::left << "Lexema" << endl;
    (*LexicalAnalyzer::lexical_file) << "----------------------------------------------- " <<endl;
    for (vector<Token*>::iterator tk = tokens.begin(); tk != tokens.end(); ++tk)
    {
        t = (Token*) *tk;
        (*LexicalAnalyzer::lexical_file) << std::setw(15) << std::left << t->getName() << "  ";
        (*LexicalAnalyzer::lexical_file) << t->getLineNumber() << " \t\t ";
        (*LexicalAnalyzer::lexical_file) << std::setw(10) << std::left << t->getLexema() << endl;
    }
    (*LexicalAnalyzer::lexical_file) << "---------------------------------" <<endl;
}

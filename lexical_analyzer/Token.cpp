 #include "Token.h"

Token::Token()
{
    //ctor
}

Token::Token(std::string n, int ln, int tc)
{
    nome = n;
    lineNumber = ln;
    tokenConstant = tc;
}

Token::Token(std::string n, int ln, int tc, std::string lex)
{
    nome = n;
    lineNumber = ln;
    tokenConstant = tc;
    lexema = lex;
}

std::string Token::getName()
{
    return nome;
}

int Token::getLineNumber()
{
    return lineNumber;
}

std::string Token::getLexema()
{
    return lexema;
}

int Token::getTokenConstant()
{
    return tokenConstant;
}


Token::~Token()
{
    //dtor
}

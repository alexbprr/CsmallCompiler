 #ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "string.h"
#include "../symbol_table/TableEntry.h"

class Token
{
    private:
        std::string lexema;
        std::string nome;
        int tokenConstant;
        int lineNumber;
    public:
        TableEntry* stEntry;

        Token();
        Token(std::string n, int ln, int tc);
        Token(std::string n, int ln, int tc, std::string lex);
        std::string getName();
        int getLineNumber();
        std::string getLexema();
        int getTokenConstant();
        virtual ~Token();
    protected:
    private:
};

#endif // TOKEN_H

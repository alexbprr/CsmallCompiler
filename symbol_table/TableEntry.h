 #ifndef TABLEENTRY_H
#define TABLEENTRY_H

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "global.h"
#include "../ast/Arrayt.h"

class TableEntry
{
    public:
        string lexema;
        int lexemaPosition;
        int lexemaSize;
        int tokenType;
        int type;
        int scope;
        int lineNumber;
        bool isDeclaration;
        int lineNumberDeclaration;
        int intValue;
        float value;
        Arrayt* arrayt;

        TableEntry();
        TableEntry(string lexema, int token, int lineNumber);
        TableEntry(string lexema, int token, int lineNumber, int type);
        string getLexema();
        string getTypeName();
        float getValue();
        void setValue(float value);
        int getLineNumber();
        virtual ~TableEntry();
};

#endif // TABLEENTRY_H

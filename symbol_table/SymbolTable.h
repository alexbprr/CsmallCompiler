 #ifndef ST_H
#define ST_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include "TableEntry.h"

#define TABLEZISE 100

class SymbolTable{
    private:
        map<string, TableEntry*> table;
        std::string tokensNames[N];
    public:
        SymbolTable();
        map<string, TableEntry*> getSymbolTable() const;
        void printSymbolTable();
        TableEntry* insertEntry(string lexema, int token, int lineNumber);
        TableEntry* insertEntry(string lexema, int token, int lineNumber, int type);
        TableEntry* getTableEntry(string key);
        void initialize();
};


#endif // ST_H

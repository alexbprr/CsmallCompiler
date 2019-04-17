#include <iostream>
#include <map>
#include "SymbolTable.h"

using namespace std;

SymbolTable::SymbolTable()
{
  tokensNames[FOR] = "FOR";
  tokensNames[MAIN] = "MAIN";
  tokensNames[ID] = "ID";
  tokensNames[INT] = "INT";
  tokensNames[FLOAT] = "FLOAT";
  tokensNames[IF] = "IF";
  tokensNames[ELSE] = "ELSE";
  tokensNames[WHILE] = "WHILE";
  tokensNames[READ] = "READ";
  tokensNames[PRINT] = "PRINT";
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
}

TableEntry* SymbolTable::insertEntry(string lexema, int token, int lineNumber)
{
    cout << "Uma nova entrada será criada com o lexema: " << lexema << endl;
    TableEntry *te = new TableEntry();
    te->lexema = lexema;
    te->tokenType = token;
    te->lineNumber = lineNumber;
    te->value = 0.;
    this->table[lexema] = te;
    return te;
}

TableEntry* SymbolTable::insertEntry(string lexema, int token, int lineNumber, int type)
{
    if (this->table.find(lexema) != this->table.end())//o lexema foi encontrado
    {
      cout << "Já existe uma entrada com esse lexema." << endl;
      //cerr << "Erro. Redeclaração de variável." << endl;
      return NULL;
    }
    else
    {
      cout << "Uma nova entrada será criada com o lexema: " << lexema << endl;
      TableEntry *te = new TableEntry();
      te->lexema = lexema;
      te->tokenType = token;
      te->lineNumber = lineNumber;
      te->type = type;
      te->value = 0.;
      this->table[lexema] = te;
      return te;
    }
}

void SymbolTable::printSymbolTable()
{
    int i = 0;
    TableEntry* entry;
    cout << "-------Symbol Table------------" <<endl;
    map<string,TableEntry*>::iterator it;
    for (it = this->table.begin(); it != this->table.end(); ++it)
    {
        cout << i << ":  ";
        entry = (TableEntry*) it->second;
        cout << "token: " << tokensNames[entry->tokenType]
        << ", lexema: " << entry->getLexema()
        << ", tipo: " << entry->getTypeName()
        << ", valor: " << entry->getValue()
        << ", line number: " << entry->getLineNumber() << endl;
        i++;
    }
    cout << "---------------------------------" <<endl;
}

void SymbolTable::saveSymbolTable()
{
    ofstream symboltablefile;
    symboltablefile.open("symboltable.txt");
    int i = 0;
    TableEntry* entry;
    symboltablefile << "-------Symbol Table--------------" <<endl;
    map<string,TableEntry*>::iterator it;
    for (it = this->table.begin(); it != this->table.end(); ++it)
    {
        symboltablefile << i << ":  ";
        entry = (TableEntry*) it->second;
        symboltablefile << "token: " << tokensNames[entry->tokenType]
        << ", lexema: " << entry->getLexema()
        << ", tipo: " << entry->getTypeName()
        << ", valor: " << entry->getValue()
        << ", line number: " << entry->getLineNumber() << endl;
        i++;
    }
    symboltablefile << "---------------------------------" <<endl;
    symboltablefile.close();
}

TableEntry* SymbolTable::getTableEntry(string key)
{
    map<string,TableEntry*>::iterator it;
    it = table.find(key);
    if(it != table.end())
    {
      cout << "Chave encontrada." << endl;
      return (it->second);
    }
    else return NULL;
}

void SymbolTable::initialize()
{
}

map<string, TableEntry*> SymbolTable::getSymbolTable() const
{
    return table;
}

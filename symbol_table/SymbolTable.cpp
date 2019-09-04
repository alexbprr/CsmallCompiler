#include <iostream>
#include <map>
#include "SymbolTable.h"

using namespace std;

SymbolTable::SymbolTable()
{}

SymbolTable::~SymbolTable()
{}

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
        cout << ", lexema: " << entry->getLexema()
        << ", tipo: " << entry->getTypeName()
        << ", valor: " << entry->getValue()
        << ", line number: " << entry->getLineNumber()
        << ", isvar: " << entry->isvar 
        << endl;
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
        symboltablefile << ", lexema: " << entry->getLexema()
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

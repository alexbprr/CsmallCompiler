 #include "TableEntry.h"

TableEntry::TableEntry(){}

TableEntry::TableEntry(string lexema, int token, int lineNumber)
{
    this->lexema = lexema;
    this->tokenType = token;
    this->lineNumber = lineNumber;
    this->intValue = 0;
    this->value = 0;
}

TableEntry::TableEntry(string lexema, int token, int lineNumber, int type)
{
    this->lexema = lexema;
    this->tokenType = token;
    this->lineNumber = lineNumber;
    this->type = type;
    this->intValue = 0;
    this->value = 0;
}

TableEntry::~TableEntry()
{
    //dtor
}

string TableEntry::getLexema()
{
    return this->lexema;
}

string TableEntry::getTypeName()
{
    if (this->type == INT_)
        return "integer";
    else if (this->type == FLOAT_)
        return "float";
    else if (this->type == CHAR_)
        return "char";
    else if (this->type == VOID_)
        return "void";
    else
        return "unknown type";
}

float TableEntry::getValue()
{
    return this->value;
}

int TableEntry::getLineNumber()
{
    return this->lineNumber;
}

void TableEntry::setValue(float value)
{
    this->value = value;
}

void TableEntry::setIsVar(bool isvar)
{
    this->isvar = isvar;
}

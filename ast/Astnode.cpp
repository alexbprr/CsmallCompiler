using namespace std;
#include "Astnode.h"

ofstream *Astnode::ast_file;
ofstream *Astnode::tac_file;
ofstream *Astnode::pythonfile;
ofstream *Astnode::dotfile;

Astnode:: Astnode(){ }

Astnode:: Astnode(string name)
{
  this->name = name;
}

vector<Astnode*>* Astnode::getChildren()
{
  return &(this->children);
}

string Astnode::getName()
{
  return name;
}

float Astnode::getValue()
{
  return this->value;
}

Operand* Astnode::getAddress()
{
  return this->address;
}

Label* Astnode::getNextLabel()
{
  return this->next;
}

Label* Astnode::getTrueLabel()
{
  return this->true_label;
}

Label* Astnode::getFalseLabel()
{
  return this->false_label;
}

void Astnode::setChildren(vector<Astnode*> children)
{
  this->children = children;
}

void Astnode::setName(string name)
{
  this->name = name;
}

void Astnode::setIntValue(int value)
{
  this->intValue = value;
}

void Astnode::setFloatValue(float value)
{
  this->value = value;
}

void Astnode::setAddress(Operand* o)
{
  this->address = o;
}

void Astnode::setTacFile(ofstream *tac_file)
{
  Astnode::tac_file = tac_file;
}

void Astnode::setAstFile(ofstream *ast_file)
{
  Astnode::ast_file = ast_file;
}

void Astnode::setPythonFile(ofstream *pythonfile)
{
  Astnode::pythonfile = pythonfile;
}

void Astnode::setDotFile(ofstream *dotfile)
{
  Astnode::dotfile = dotfile;
}

void Astnode::addChild(Astnode* node)
{
  if (node == NULL)
    cerr << "Tentativa de adicionar um filho nulo." << endl;
  else
    this->children.push_back(node);
}

string Astnode::tabs(int level)
{
  string deslocamento = "";
  while (level!=0)
  {
    level = level - 1;
    deslocamento += "    ";
  }
  return deslocamento;
}

     //if ((*it)->tableEntryRef != NULL)
        //ss << (*it)->name << level << *cont << "_" << (*it)->tableEntryRef->getLexema();
      //ss << (*it)->name << level << *cont << "[shape=circle,label=\"Id("<< (*it)->tableEntryRef->getLexema()<< ")\"]";
      // if ((*it)->op.length() > 0)
      // {
      //   ss << (*it)->name << level << *cont << "\"" << (*it)->op << "\"";// << "[shape=circle,label=\""<< (*it)->name << "(" << (*it)->op<< ")\"]";
      //   (*it)->dotname = ss.str();
      //   ss.str("");
      // }
      // else
      //   ss << (*it)->name << level << *cont << "[shape=circle,label=\""<< (*it)->name << "\"]";
      //printf("Dot name: %s\n", (*it)->dotname.c_str());


void Astnode::generateDot(int level, int *cont)
{
  std::stringstream ss;
  if (level == 0)
  {
    ss << this->name;
    this->dotname = ss.str();
    ss.str("");
  }
  (*cont)++;
  if (this->children.size() > 0)
  {
    if (this->op.length() > 0)
      ss << this->name << level << *cont << "[shape=circle,label=\""<< this->name << "("<<  this->op <<")\"];"<<endl;
    else
      ss << this->name << level << *cont << "[shape=circle,label=\""<< this->name << "\"];"<< endl;
    (*Astnode::dotfile) << ss.str();
    ss.str("");
    ss << this->name << level << *cont;
    this->dotname = ss.str();
    ss.str("");
    for(vector<Astnode*>::iterator it = this->children.begin(); (*it) != NULL && it != this->children.end(); ++it)
    {
      if ((*it)->dotname.length() == 0)
      {
        //printf("lenght == 0\n");
        ss << (*it)->name << level << *cont;
        (*it)->dotname = ss.str();
        ss.str("");
      }
      (*it)->generateDot(level + 1, cont);
      (*Astnode::dotfile) << this->dotname << " -> " << (*it)->dotname << ";" << endl;
    }
  }
  else
  {
    if (this->getName() == "Id")
    {
      ss << this->name << level << *cont << "[shape=circle,label=\"Id["<< this->lexema << "]\"];"<< endl;
    }
    else {
      if (this->type == 0)
        ss << this->name << level << *cont << "[shape=circle,label=\"Integer["<< this->intValue << "]\"];"<< endl;
      else
        ss << this->name << level << *cont << "[shape=circle,label=\"Integer["<< this->value << "]\"];"<< endl;
    }
    (*Astnode::dotfile) << ss.str();
    ss.str("");
    ss << this->name << level << *cont;
    this->dotname = ss.str();
    ss.str("");

  }
}

void Astnode::printNode(int level)
{
  string deslocamento = this->tabs(level);
  cout << deslocamento << "<" << this->name << ">" << endl;
  (*Astnode::ast_file) << deslocamento << "<" << this->name << ">" << endl;
  if (this->children.size() > 0)
  {
      for(vector<Astnode*>::iterator it = this->children.begin(); it != this->children.end(); ++it)
      {
          if ((*it) != NULL)
            (*it)->printNode(level+1);
      }
  }
  cout << deslocamento << "</" << this->name << ">" << endl;
  (*Astnode::ast_file) << deslocamento << "</" << this->name << ">" << endl;
}

float Astnode::evaluate()
{
    if (this->children.size() > 0)
    {
        for(vector<Astnode*>::iterator it = this->children.begin(); it != this->children.end(); ++it)
            if ((*it) != NULL)
                (*it)->evaluate();
    }
}

void Astnode::generateCode()
{
    if (this->children.size() > 0)
    {
        for(vector<Astnode*>::iterator it = this->children.begin(); it != this->children.end(); ++it)
        {
            if ((*it) != NULL)
                (*it)->generateCode();
        }
    }
}

void Astnode::generateBranchCode(){}

void Astnode::generateRValueCode(){}

string Astnode::pythonTab(int level)
{
  string deslocamento = "";
  while (level!=0)
  {
    level = level - 1;
    deslocamento += "    ";
  }
  return deslocamento;
}

void Astnode::generatePythonCode(int level)
{
    if (this->children.size() > 0)
    {
        for(vector<Astnode*>::iterator it = this->children.begin(); it != this->children.end(); ++it)
        {
            if ((*it) != NULL)
                (*it)->generatePythonCode(level);
        }
    }
}

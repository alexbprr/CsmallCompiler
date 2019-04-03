#ifndef LABEL_H
#define LABEL_H
using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Operand.h"

class Label: public Operand
{
  private:
  public:
    static int n;
    string name;
    Label();
    virtual string getName();
};

#endif

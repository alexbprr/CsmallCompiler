#ifndef TEMP_H
#define TEMP_H
using namespace std;

#include "../symbol_table/TableEntry.h"

class Temp
{
  private:
  public:
    static int n;
    string name;
    Temp();
    string getName();
};

#endif

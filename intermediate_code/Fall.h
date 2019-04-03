#ifndef FALL_H
#define FALL_H
using namespace std;
#include "Label.h"

class Fall: public Label
{
  private:
  public:
    static int n;
    string name;
    Fall();
    string getName();
};

#endif

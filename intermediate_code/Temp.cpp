#include "Temp.h"
using namespace std;

int Temp::n = 0;

Temp::Temp()
{
  std::stringstream ss;
  ss << Temp::n++;
  this->name = "t" + ss.str();
}

string Temp::getName()
{
  return this->name;
}

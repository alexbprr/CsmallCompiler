#include "Label.h"
using namespace std;

int Label::n = 0;

Label::Label()
{
  std::stringstream ss;
  ss << Label::n++;
  this->name = "L" + ss.str();
}

string Label::getName()
{
  return this->name;
}

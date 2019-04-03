#ifndef ARRAYT_H
#define ARRAYT_H

using namespace std;
#include <string>

class Arrayt
{
  public:
    std::string typen;
    int dim;
    void* type;
    Arrayt(int dim, void *type);
};

#endif

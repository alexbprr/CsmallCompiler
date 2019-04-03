#ifndef VERTEX_H
#define VERTEX_H
using namespace std;
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Vertex
{
  private:
  public:
    string name;
    int number;
    vector<Vertex*> adjacent_list;
    Vertex();
};

#endif

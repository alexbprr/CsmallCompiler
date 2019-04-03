#ifndef NODE_H
#define NODE_H
using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include <list>

class Node
{
  private:
  public:
    string name;
    list<Node*> adjacents;
    Node();    
};

#endif

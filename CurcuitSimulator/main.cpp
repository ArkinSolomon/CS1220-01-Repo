#include "Circuit.h"
#include <iostream>
using namespace std;

int main()
{
  Circuit* c = new Circuit();

  if (!c->parseCircuit("circuitPath"))
  {
    delete c;
  }
  else if (!c->parseValues("valuePath"))
  {
    delete c;
  }

  return 0;
}
#include "Circuit.h"
#include <iostream>
using namespace std;

//#define LOOP_ALL

int main()
{
  // Get circuit and vector file name
  cout << "Enter a circuit file name: ";
  string circuitPath, valuePath;
  cin >> circuitPath >> valuePath;

  // Parses files
  Circuit *c = new Circuit();
  if ((!c->parseCircuit(circuitPath)) || (!c->parseValues(valuePath)))
  {
    delete c;
    return 1;
  }

  //Start simulation
  c->simulate();
  return 0;
}
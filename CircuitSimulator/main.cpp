// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/27/22
// Purpose: To get inputs to start circuit simulation
// 4/27/2022 -OW/AS -Fix logic, remove debugs

#include "Circuit.h"
#include <iostream>
using namespace std;

//#define LOOP_ALL

int main()
{
  // Get circuit and vector file name
  cout << "Enter a circuit file name: ";
  string circuitPath, valuePath;
  cin >> circuitPath;
  cout << "Enter a value file name: ";
  cin >> valuePath;

  // Parses files
  Circuit *c = new Circuit();
  if ((!c->parseCircuit(circuitPath)) || (!c->parseValues(valuePath)))
  {
    delete c;
    return 1;
  }

  // Start simulation
  c->simulate();
  return 0;
}
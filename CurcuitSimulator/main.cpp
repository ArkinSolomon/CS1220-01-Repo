#include "Circuit.h"
#include <iostream>
using namespace std;

int main()
{
  // for (int i = 0; i <= 6; ++i)
  // {
  //   if (i == 3) continue;
  int i = 5;
    // gets circuit file name
    // cout << "Enter a circuit file name: ";
    string circuitPath = "circuit" + to_string(i) + ".txt";
    // cin >> circuitPath;
    // gets vector file name
    // cout << "Enter a vector file name: ";
    string valuePath = "circuit" + to_string(i) + "_v.txt";
    // cin >> valuePath;

    // parses files
    Circuit *c = new Circuit();
    if ((!c->parseCircuit(circuitPath)) || (!c->parseValues(valuePath)))
    {
      delete c;
      return 1;
    }

    c->simulate();
    cout << endl;
  // }

  return 0;
}
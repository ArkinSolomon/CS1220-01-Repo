#include "Circuit.h"
#include <iostream>
using namespace std;

//#define LOOP_ALL

int main()
{
#ifdef LOOP_ALL
  for (int i = 0; i <= 6; ++i)
  {
    if (i == 3)
      continue;
#else
  int i = 0;
#endif
    // gets circuit file name
    // cout << "Enter a circuit file name: ";
    string circuitPath = "circuits/circuit5.txt";
    // cin >> circuitPath;
    // gets vector file name
    // cout << "Enter a vector file name: ";
    string valuePath = "circuits/circuit5_v.txt";
    // cin >> valuePath;

    // parses files
    Circuit *c = new Circuit();
    if ((!c->parseCircuit(circuitPath)) || (!c->parseValues(valuePath)))
    {
      delete c;
      return 1;
    }

    c->simulate();
#ifdef LOOP_ALL
    cout << endl;
  }
#endif

  return 0;
}
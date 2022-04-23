#include "Circuit.h"
#include <iostream>
using namespace std;

int main()
{
    //gets circuit file name
    cout << "Enter a circuit file name: " ;
    string circuitPath = "";
    cin >> circuitPath;
    //gets vector file name
    cout << "Enter a vector file name: ";
    string valuePath = "";
    cin >> valuePath;

    //parses files
  Circuit* c = new Circuit();
  if (!c->parseCircuit(circuitPath))
  {
      delete c;
  }

  else if (!c->parseValues(valuePath))
  {
    delete c;
  }



  return 0;
}
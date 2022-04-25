#include "Circuit.h"
#include <iostream>
using namespace std;

int main()
{
    //gets circuit file name
    //cout << "Enter a circuit file name: " ;
    string circuitPath = "circuit4.txt";
    // cin >> circuitPath;
    //gets vector file name
    //cout << "Enter a vector file name: ";
    string valuePath = "circuit4_v.txt";
    // cin >> valuePath;

    //parses files
    Circuit* c = new Circuit();
    if ((!c->parseCircuit(circuitPath)) || (!c->parseValues(valuePath)))
    {
        delete c;
        return 1;
    }

    c->simulate();

    return 0;
}
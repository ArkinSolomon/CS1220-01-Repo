// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Gate class
// 4/11/2022 -OW/AS -Defined all of the functions
#include "Wire.h"
#include "Gate.h"
#include <string.h>
#include <map>

#ifndef CIRCUIT_H
#define CIRCUIT_H

class Circuit
{
  public:
    Circuit(string circuitPath, string valuePath);
    void parseCircuit(string path);
    void parseValues(string path);
  private:
    string circuitName;
    map<char, Wire*> wires;
    map<char, Gate*> gates;

};
#endif
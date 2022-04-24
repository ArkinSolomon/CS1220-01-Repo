// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Gate class
// 4/11/2022 -OW/AS -Defined all of the functions
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Wire.h"
#include "Gate.h"
#include "Event.h"
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

class Circuit
{
public:
  ~Circuit();
  bool parseCircuit(string path);
  bool parseValues(string path);
  Wire *getWire(int i);
  Wire *getWireByName(char n);
  void addWire(int index, Wire* wire);
  void simulate();

private:
  string circuitName;
  vector<Wire *> wires;
  vector<Gate *> gates;
  priority_queue<Event> queue;
};

#endif
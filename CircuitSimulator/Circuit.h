// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/27/22
// Purpose: To declare the funtions in the Circuit class
// 4/27/2022 -OW/AS -Fix logic, finish project

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
  void addWire(int index, Wire *wire);
  void simulate();

private:
  string circuitName;
  vector<Wire *> wires;
  vector<Gate *> gates;
  priority_queue<Event> queue;
  int ooa;
};

#endif
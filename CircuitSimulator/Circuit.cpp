// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Gate class
// 4/11/2022 -OW/AS -Defined all of the functions

#define FILE_DEBUG
#define CIRCUIT_DEBUG

#include "Circuit.h"
#include "Event.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

Circuit::~Circuit()
{
  for (Wire *w : wires)
  {
    delete w;
  }
  for (Gate *g : gates)
  {
    delete g;
  }
}

bool Circuit::parseCircuit(string path)
{
  // Open the file and check if it exists
  ifstream circuitFile;
  circuitFile.open(path);
  if (!circuitFile.is_open())
  {
    cerr << "Could not open circuit file" << endl;
    return false;
  }

  // Ignore the word CIRCUIT
  string ignore;
  circuitFile >> ignore >> circuitName;

  while (!circuitFile.eof())
  {
    string type;
    circuitFile >> type;
    if (type == "INPUT" || type == "OUTPUT")
    {
      // Parses wires
      char name = '!';
      int index = -1;
      circuitFile >> name >> index;
      Wire *w = new Wire(index, name);
      addWire(index, w);
    }
    else if (type == "NOT")
    {
      // Only NOT gates have 3 arguments
      string delayStr;
      int delay = -1;
      int inIndex = -1;
      int outputIndex = -1;
      circuitFile >> delayStr >> inIndex >> outputIndex;

      // Parse the delay
      delayStr.replace(delayStr.find("ns"), 2, "");
      delay = stoi(delayStr);

      // Make sure all the wires exist
      Wire *inWire = getWire(inIndex);
      Wire *outWire = getWire(outputIndex);
      Gate *g = new Gate(GateType::NOT, delay, inWire, nullptr, outWire);

      // Makes sure the wire knows which gate it is plugged into
      inWire->setDrives(g);
      gates.push_back(g);
    }
    else
    {
      // Handles every other case
      string delayStr;
      int delay = -1;
      int in1Index = -1;
      int in2Index = -1;
      int outputIndex = -1;
      circuitFile >> delayStr >> in1Index >> in2Index >> outputIndex;

      // Parse the delay
      delayStr.replace(delayStr.find("ns"), 2, "");
      delay = stoi(delayStr);

      // Make sure all the wires exist
      Wire *in1Wire = getWire(in1Index);
      Wire *in2Wire = getWire(in2Index);
      Wire *outWire = getWire(outputIndex);
      GateType t;

      if (type == "AND")
      {
        t = GateType::AND;
      }
      else if (type == "OR")
      {
        t = GateType::OR;
      }
      else if (type == "XOR")
      {
        t = GateType::XOR;
      }
      else if (type == "NAND")
      {
        t = GateType::NAND;
      }
      else if (type == "NOR")
      {
        t = GateType::NOR;
      }
      else if (type == "XNOR")
      {
        t = GateType::XNOR;
      }
      else
      {
        throw runtime_error("Invalid gate in circuit definition");
      }

      Gate *newGate = new Gate(t, delay, in1Wire, in2Wire, outWire);
      gates.push_back(newGate);

      // making sure the wires know which gates they are hooked up to
      in1Wire->setDrives(newGate);
      in2Wire->setDrives(newGate);
    }
  }

  circuitFile.close();
  return true;
}

bool Circuit::parseValues(string path)
{
  // Open the file and check if it exists
  ifstream valueFile;
  valueFile.open(path);
  if (!valueFile.is_open())
  {
    cerr << "Could not open values file" << endl;
    return false;
  }

  // Ignore the word VECTOR
  string ignore, valueFileName;
  valueFile >> ignore >> valueFileName;
  if (valueFileName != circuitName)
  {
    cerr << "Incorrect value file for circuit file" << endl;
    return false;
  }

  // Start counting from zero
  while (true)
  {
    // Skip the word INPUT
    char wireName, value;
    int time;
    valueFile >> ignore >> wireName >> time >> value;

    if (valueFile.eof())
    {
      break;
    }

    Wire *w = getWireByName(wireName);
    Event e = Event(ooa, time, w, value);

    queue.push(e);
    ++ooa;
  }

  return true;
}

// Get a wire by index or create an internal wire it if it doesn't exist
Wire *Circuit::getWire(int i)
{
  if (wires.size() < i || wires.at(i) == nullptr)
  {
    Wire *w = new Wire(i, '@');
    if (i > wires.size())
    {
      wires.resize(i + 1);
    }
    wires.at(i) = w;
  }
  return wires.at(i);
}

// Get a wire by it's name
Wire *Circuit::getWireByName(char n)
{
  for (Wire *w : wires)
  {
    if (w == nullptr)
    {
      continue;
    }
    else if (w->getName() == n)
    {
      return w;
    }
  }
  return nullptr;
}

// Resize the vector if needed
void Circuit::addWire(int index, Wire *wire)
{
  if (index > wires.size())
  {
    wires.resize(index);
  }
  wires.insert(wires.begin() + index, wire);
}

void Circuit::simulate()
{
  int maxTime = -1;
  while (!queue.empty())
  {
    Event e = queue.top();
    queue.pop();
    Wire *w = e.getWire();
    char v = e.getValue();
    char original = w->getValue();
    w->setValue(v);

    w->stretchHistory(e.getTime());
    w->setHistory(v);

    if (e.getTime() > 61)
    {
      break;
    }

    if (maxTime < e.getTime()){
      maxTime = e.getTime();
    }

    for (Gate *g : w->getDrives())
    {
      char result = g->evaluate();
      w->setValue(original);
      if (g->evaluate() != result)
      {
        // cout << newV << endl;
        queue.push(Event(ooa, e.getTime() + g->getDelay(), g->getOutput(), result));
        ++ooa;
      }
      w->setValue(v);
    }
  }

  // Print wire history
  for (Wire *w : wires)
  {
    if (w != nullptr && w->getName() != '@')
    {
      w->stretchHistory(maxTime + 1);
      w->printHistory();
    }
  }
  //add time line at bottom
  cout << "   0";
  int i = 0;
  int j = 1;
  size_t lengthStr = wires.at(1)->getHistory().length();
  while(i < lengthStr) {
      if (j == 5) {
          cout << j;
          j ++;
      }
      else if (j == 10)
      {
          cout << "0";
          j=0;
      }
      else {
          cout << "-";
          j++;
          i++;
      }
  }
}

// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Gate class
// 4/11/2022 -OW/AS -Defined all of the functions
#include "Circuit.h"
#include "Event.h"
#include <fstream>
#include <iostream>
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
      if (index > wires.size())
      {
        wires.resize(index);
      }
      Wire *w = new Wire(index, name);
      wires.insert(wires.begin() + index, w);
    }
    else if (type == "NOT")
    {
      // Only NOT gates have 3 arguments
      int delay = -1;
      int inIndex = -1;
      int outputIndex = -1;
      circuitFile >> delay >> inIndex >> outputIndex;

      // Make sure all the wires exist
      Wire *inWire = getWire(inIndex);
      Wire *outWire = getWire(outputIndex);
      Gate *g = new Gate(GateType::NOT, delay, inWire, nullptr, outWire);
      inWire->setDrives(g);
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

      //Parse the delay
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
  int ooa = 0;
  while (!valueFile.eof())
  {
    // Skip the word INPUT
    char wireName;
    int time, value;
    valueFile >> ignore >> wireName >> time >> value;

    Wire *w = getWireByName(wireName);
    Event *e = new Event(ooa, time, w, value);

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
      wires.resize(i);
    }
    wires.insert(wires.begin() + i, w);
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

void Circuit::simulate()
{
  while (!queue.empty())
  {
    Event *e = queue.top();
    cout << e->getOOA() << " " << e->getTime() << " " << e->getWire()->getName() << endl;
    queue.pop();
  }
}

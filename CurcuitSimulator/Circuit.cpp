// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Gate class
// 4/11/2022 -OW/AS -Defined all of the functions
#include "Circuit.h"
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
      Wire w(index, name);
      wires.at(index) = &w;
    }
    else if (type == "NOT")
    {
      // Only NOT gates have 3 arguments
      int delay = -1;
      int inIndex = -1;
      int outputIndex = -1;
      cin >> delay >> inIndex >> outputIndex;

      // Make sure all the wires exist
      Wire *inWire = getWire(inIndex);
      Wire *outWire = getWire(outputIndex);
      Gate g(GateType::NOT, delay, inWire, nullptr, outWire);
      inWire->setDrives(&g);
    }
    else
    {
      // Handles every other case
      int delay = -1;
      int in1Index = -1;
      int in2Index = -1;
      int outputIndex = -1;
      cin >> delay >> in1Index >> in2Index >> outputIndex;

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
  return true;
}

// Get a wire by index or create an internal wire it if it doesn't exist
Wire *Circuit::getWire(int i)
{
  if (wires.at(i) == nullptr)
  {
    Wire w(i, '@');
    wires.at(i) = &w;
  }
  return wires.at(i);
}

// Get a wire by it's name
Wire *Circuit::getWireByName(char n)
{
  for (Wire *w : wires)
  {
    if (w->getName() == n)
    {
      return w;
    }
  }
  return nullptr;
}

void Circuit::simulate()
{
  
}

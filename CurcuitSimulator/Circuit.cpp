// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Gate class
// 4/11/2022 -OW/AS -Defined all of the functions

// #define FILE_DEBUG
// #define CIRCUIT_DEBUG

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
#ifdef FILE_DEBUG
  // Kept for testing circuit and vector file parsing
  cout << "Wire info" << endl;
  for (Wire *w : wires)
  {
    if (w != NULL)
    {
      cout << w->getName() << " Drives: ";
      for (Gate *g : w->getDrives())
      {
        cout << g->getDelay() << " " << endl;
      }
    }
  }
  cout << "Gates info" << endl;
  for (Gate *g : gates)
  {
    cout << "Delay: " << g->getDelay() << " Input 1: " << g->getInput(1)->getName() << " Output: " << g->getOutput()->getName() << endl;
  }

  vector<Event> events;
  while (!queue.empty())
  {
    Event e = queue.top();
    cout << "OOA: " << e.getOOA() << " TIME: " << e.getTime() << " WIRE: " << e.getWire()->getName() << " Value: " << e.getValue() << endl;
    queue.pop();
    events.push_back(e);
  }
  for (Event e : events)
  {
    queue.push(e);
  }
#endif

  // The last event's time of occurence
  int maxTime = 0;

  while (!queue.empty())
  {
    // get the first event and the wire it is associated to
    Event e = queue.top();

#ifdef CIRCUIT_DEBUG
    cout << "Handling event: " << e.getWire()->getName() << " --> " << e.getValue() << " [" << e.getTime() << "]" << endl;
#endif
    queue.pop();
    Wire *w = e.getWire();
    w->setValue(e.getValue());
    if (maxTime < e.getTime())
    {
      maxTime = e.getTime() + 1;
    }

    // Loop through all drives
    vector<Gate *> wd = w->getDrives();
    for (Gate *g : wd)
    {
      char result = g->evaluate();
      if (g->getOutput()->getValue() != result)
      {
#ifdef CIRCUIT_DEBUG
        cout << "Difference in gate result -- Time: " << e.getTime() << " Result: " << result << " New event time: " << (e.getTime() + g->getDelay()) << endl;
#endif

        // create a new event that was caused by this change
        queue.push(Event(ooa, (e.getTime() + g->getDelay() - 1), g->getOutput(), result));
        ooa++;
      }
    }
    w->stretchHistory(e.getTime());
    w->setHistory(w->getValue());
  }

#ifdef CIRCUIT_DEBUG
  cout << "DONE SIMULATING... PRINTING HISTORY:" << endl;
#endif
  for (Wire *w : wires)
  {
    if (w != NULL)
    {
      if (w->getName() != '@')
      {
        cout << w->getName() << ": ";
        w->stretchHistory(maxTime);
        string h = w->getHistory();
        cout << h << endl;
      }
    }
  }
}

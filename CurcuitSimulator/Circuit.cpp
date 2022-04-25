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
      //Makes sure the wire knows which gate it is plugged into
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
      //making sure the wires know which gates they are hooked up to
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
  while (!valueFile.eof())
  {
    // Skip the word INPUT
    char wireName;
    int time;
    char value;
    valueFile >> ignore >> wireName >> time >> value;

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
    //kept for testing circuit parser
    /*cout << "Wire info" << endl;
    for (Wire* w : wires) {
        if (w != NULL) {
            cout << w->getName() << " Drives: ";
            for (Gate* g : w->getDrives()) {
                cout << g->getDelay() << " ";
            }
        }
  }*/
    /*cout << "Gates info" << endl;
    for (Gate* g : gates)
  {
      cout << "Delay: " << g->getDelay() << " Input 1: " << g->getInput(1)->getName() << " Output: " << g->getOutput()->getName() << endl;
  }*/
    //kept for testing vector parser
    /*while (!queue.empty())
    {
        Event e = queue.top();
        cout << e.getOOA() << " " << e.getTime() << " " << e.getWire()->getValue() << endl;
        queue.pop();
    }*/

    while (!queue.empty()) {
        //get the first event and the wire it is associated to
        Event e = queue.top();
        queue.pop();
        Wire* w = e.getWire();
        w->setValue(e.getValue());
        
        //check if this event affects values in the future
        vector<Gate*> wd = w->getDrives();

        //checks to make sure this wire has drives
        if (!wd.empty()) {
          for (Gate* g : wd){

            char result = g->evaluate();
            if (w->getValue() != result) {
                //create a new event that was caused by this change
                queue.push(Event(ooa, (e.getTime() + g->getDelay()), g->getOutput(), result));
                ooa++;
            }

          }
        }
        string wHistory = w->getHistory();
        int currentTime = e.getTime();
        int hSize = wHistory.length();
        if (hSize < currentTime) {
            char wc = w->getValue();
            char c = 'X';
            if (wc == '1') {
                c = '-';
            }
            else if (wc == '0') {
                c = '_';
            }
            for (int j = wHistory.length(); j <= currentTime; j++) {
                w->setHistory(c);
            }
        }
    }
        for (Wire* w : wires) {
            if (w != NULL) {
                if (w->getName() != '@') {
                    cout << w->getName() << ": ";
                    w->printHistory();
                }
            }
        }
}


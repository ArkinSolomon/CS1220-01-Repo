// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Gate class
// 4/11/2022 -OW/AS -Defined all of the functions
#include "Circuit.h"
#include <fstream>
#include <iostream>
using namespace std;

Circuit::Circuit(string circuitPath, string valuePath)
{

  parseCircuit(circuitPath);
  parseValues(valuePath);
}

Circuit::~Circuit() {
    for (Wire* w: wires) {
        delete w;
    }
    for (Gate* g : gates) {
        delete g;
    }
}

void Circuit::parseCircuit(string path)
{
  // Open the file and check if it exists
  ifstream circuitFile;
  circuitFile.open(path);
  if (!circuitFile.is_open())
  {
    cout << "Could not open circuit file" << endl;
    return;
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
    else
    {
      //Parses gates
        string name= "";
        int delay = -1;

    }
  }

  circuitFile.close();
}

void Circuit::parseValues(string path)
{
  // Open the file and check if it exists
  ifstream valueFile;
  valueFile.open(path);
  if (!valueFile.is_open())
  {
    cout << "Could not open values file" << endl;
    return;
  }
}
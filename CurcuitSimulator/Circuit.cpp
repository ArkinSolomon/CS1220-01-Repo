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
      char name;
      int index;

      // Parses wires
      circuitFile >> name >> index;
      Wire w(index, name);  
      wires.insert(name, &w);
    }
    else
    {
      //Parses gates
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
// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/27/22
// Purpose: To declare the funtions in the Wire class
// 4/27/2022 -OW/AS -Fix logic, finish project

#ifndef WIRE_H
#define WIRE_H

#include <vector>
#include <string>
using namespace std;

class Gate;

class Wire
{
public:
  Wire(int i, char n);
  ~Wire();
  void setValue(char v);
  void setHistory(char c);
  void setDrives(Gate *g);
  char getValue() const;
  char getName() const;
  vector<Gate *> getDrives() const;
  string getHistory() const;
  void stretchHistory(int time);
  void printHistory() const;

private:
  char value;
  char name;
  int index;
  vector<Gate *> drives;
  string history;
};
#endif

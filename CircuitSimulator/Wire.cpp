// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Wire class
// 4/11/2022 -OW/AS -Defined all of the functions

#include "Wire.h"
#include <iostream>
using namespace std;

Wire::Wire(int i, char n)
{
  index = i;
  name = n;
  value = 'X';
  history = "";
}

Wire::~Wire()
{
  for (int i = 0; i < drives.size(); i++)
  {
    delete drives.at(i);
  }
}

void Wire::setValue(char v)
{
  value = v;
}

void Wire::addHistory(char c)
{
  char v = c;
  if (c == '1')
  {
    v = '-';
  }
  else if (c == '0')
  {
    v = '_';
  }
  history.push_back(v);
}

void Wire::addDriven(Gate *g)
{
  drives.push_back(g);
}

char Wire::getName() const
{
  return name;
}

char Wire::getValue() const
{
  return value;
}

vector<Gate *> Wire::getDrives() const
{
  return drives;
}

string Wire::getHistory() const
{
  return history;
}

void Wire::stretchHistory(int time)
{
  if (history.length() < time)
  {
    int hSize = history.length();
    char c = hSize > 0 ? history[hSize - 1] : 'X';
    for (int j = history.length(); j < time; j++)
    {
      addHistory(c);
    }
  }
  else if (history.length() > time)
  {
    history = history.substr(0, time);
  }
}

void Wire::printHistory() const
{
  cout << name << ": " << history << endl;
}
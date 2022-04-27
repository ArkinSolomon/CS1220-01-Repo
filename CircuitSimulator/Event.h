// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/27/22
// Purpose: To declare the funtions in the Event class
// 4/27/2022 -OW/AS -Fix logic, finish project

#include <string>
#include "Wire.h"

#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
  Event(int ooa, int t, Wire *w, char v);
  int getOOA() const;
  int getTime() const;
  Wire *getWire() const;
  char getValue() const;

  // for the priority_queue
  friend bool operator<(const Event &e1, const Event &e2);

private:
  int orderOfArrival;
  int time;
  Wire *wire;
  char value;
};

#endif
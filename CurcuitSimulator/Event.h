// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/15/20
// Purpose: To track events for easy strorage in queue
// 4/15/2022 -OW/AS -Defined all of the functions
#include <string>
#include "Wire.h"

#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
	Event(int i, int t, Wire* w, char v);
private:
	int index, time;
	Wire* wire;
  char value;
};

#endif
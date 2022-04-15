// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/15/20
// Purpose: To track events for easy strorage in queue
// 4/15/2022 -OW/AS -Defined all of the functions
#include <string>

#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
	Event(int i, Wire* w);
private:
	Wire* wire;
	int index;
};

#endif
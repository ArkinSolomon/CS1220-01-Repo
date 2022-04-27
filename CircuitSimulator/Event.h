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
	Event(int ooa, int t, Wire* w, char v);
	int getOOA() const;
	int getTime()const;
	Wire* getWire() const;
	char getValue() const;
	//for the priority_queue
	friend bool operator<(const Event& e1, const Event& e2);

private:
	int orderOfArrival;
	int time;
	Wire* wire;
	char value;
};

#endif
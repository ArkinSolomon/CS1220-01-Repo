// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/15/20
// Purpose: To track events for easy strorage in queue
// 4/15/2022 -OW/AS -Defined all of the functions
#include "Event.h"
#include <string>

Event::Event(int ooa, int t, Wire* w, char v)
{
	orderOfArrival = ooa;
	time = t;
	wire = w;
	value = v;
}

int Event::getOOA() const {
	return orderOfArrival;
}

int Event::getTime()const {
	return time;
}

Wire* Event::getWire() const {
	return wire;
}

char Event::getValue() const {
	return value;
}

bool operator<(const Event& e1, const Event& e2) {

	if (e1.getTime() == e2.getTime()) {
		return e1.getOOA() > e2.getOOA();
	}

	return e1.getTime() > e2.getTime();
}

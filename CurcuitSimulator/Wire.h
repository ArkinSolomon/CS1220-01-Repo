// Author:  Keith A. Shomper
// Date:    2/13/20
// Purpose: To specify a simple, linked-list of sorted positive integers

#ifndef WIRE_H
#define WIRE_H

#include <vector>
#include <string>
using namespace std;

class Gate;

class Wire{
public:
	Wire(char n, int i);
	void setValue(char v);
	void setHistory(string s);
	void setDrives(vector<Gate*> d);
	char getValue() const;
	char getName() const;
	vector<Gate*> getDrives() const;
	string getHistory() const;
	void printHistory() const;

private:
	char value;
	char name;
	vector<Gate*> drives;
	int index;
	string history;
};
#endif

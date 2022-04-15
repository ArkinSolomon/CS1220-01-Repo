// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Wire class
// 4/8/2022 -OW/AS -Defined all of the functions

#ifndef WIRE_H
#define WIRE_H

#include <vector>
#include <string>
using namespace std;

class Gate;

class Wire{
public:
	Wire(int i, char n);
	void setValue(char v);
	void setHistory(string s);
	void setDrives(vector<Gate*>& d);
	char getValue() const;
	char getName() const;
	vector<Gate*> getDrives() const;
	string getHistory() const;
	void printHistory() const;

private:
	char value;
	char name;
	int index;
	vector<Gate*> drives;
	string history;
};
#endif

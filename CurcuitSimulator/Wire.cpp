#include "Wire.h"
#include <iostream>
using namespace std;

Wire::Wire(char n = '1', char v = 'X', int i) {
	index = i;
}

void Wire::setValue(char v) {
	value = v;
}

void Wire::setHistory(string h) {
	history = h;
}

void Wire::setDrives(vector<Gate*> d) {
	drives = d;
}

char Wire::getName() const {
	return name;
}

char Wire::getValue() const{
	return value;
}

vector<Gate*> Wire::getDrives() const {
	return drives;
}

string Wire::getHistory() const {
	return history;
}

void Wire::printHistory() const {
	cout << name<< " " << history << endl;
}
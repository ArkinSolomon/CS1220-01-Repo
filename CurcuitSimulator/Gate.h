// Author:  Keith A. Shomper
// Date:    2/13/20
// Purpose: To specify a simple, linked-list of sorted positive integers

#ifndef GATE_H
#define GATE_H

class Wire;
enum GateType{AND, OR, NOT, XOR, NAND, NOR, XNOR};

class Gate {
public:
	Gate(GateType t, int d, Wire* in1, Wire* in2, Wire* out);
	int getDelay() const;
	Wire* getInput(int i) const;
	Wire* getOutput() const;
	char evaluate() const;

private:
	GateType type;
	int delay;
	Wire* input1, * input2;
	Wire* output;
};
#endif

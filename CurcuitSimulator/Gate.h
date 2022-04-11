// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Wire class
// 4/8/2022 -OW/AS -Defined all of the functions

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

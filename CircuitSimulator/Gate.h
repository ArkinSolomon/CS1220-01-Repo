// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/27/22
// Purpose: To declare the funtions in the Gate class
// 4/27/2022 -OW/AS -Fix logic, finish project

#ifndef GATE_H
#define GATE_H

class Wire;

enum class GateType
{
  AND,
  OR,
  NOT,
  XOR,
  NAND,
  NOR,
  XNOR
};

class Gate
{
public:
  Gate(GateType t, int d, Wire *in1, Wire *in2, Wire *out);
  ~Gate();
  int getDelay() const;
  Wire *getInput(int i) const;
  Wire *getOutput() const;
  char evaluate() const;
  char eval_and() const;
  char eval_or() const;
  char eval_xor() const;

private:
  GateType type;
  int delay;
  Wire *input1, *input2;
  Wire *output;
};

char not_func(char in);
#endif

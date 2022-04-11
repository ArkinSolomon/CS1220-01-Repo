// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Gate class
// 4/11/2022 -OW/AS -Defined all of the functions
#include "Gate.h"

Gate::Gate(GateType t, int d, Wire *in1, Wire *in2, Wire *out)
{
  type = t;
  delay = d;
  input1 = in1;
  input2 = in2;
  output = out;
}

int Gate::getDelay() const
{
  return delay;
}

Wire *Gate::getInput(int i) const
{
  if (i > 2 || i < 1) {
    return nullptr;
  }
  return (i == 1) ? input1 : input2;
}

Wire *Gate::getOutput() const
{
  return output;
}

char Gate::evaluate() const
{
  
}
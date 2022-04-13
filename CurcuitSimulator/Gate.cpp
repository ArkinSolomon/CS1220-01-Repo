// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/11/20
// Purpose: To define the funtions in the Gate class
// 4/11/2022 -OW/AS -Defined all of the functions
#include "Gate.h"
#include "Wire.h"

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
  if (i > 2 || i < 1)
  {
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
  switch (type)
  {
  case AND:
  {
    return eval_and();
  }

  case OR:
  {
    return eval_or();
  }

  case NOT:
  {
    char in1 = input1->getValue();
    return not_func(in1);
  }

  case XOR:
  {
    return eval_xor();
  }

  case NAND:
  {
    char andOut = eval_and();
    return not_func(andOut);
  }

  case NOR:
  {
    char orOut = eval_or();
    return not_func(orOut);
  }

  case XNOR:
  {
    char xorOut = eval_xor();
    return not_func(xorOut);
  }

  default:
  {
    return 'X';
  }
  }
}

char Gate::eval_and() const
{
  char in1 = input1->getValue();
  char in2 = input2->getValue();
  if (in1 == 'X' && in2 == 'X')
  {
    return 'X';
  }
  else if ((in1 == '1' && in2 == 'X') || (in1 == 'X' && in2 == '1'))
  {
    return 'X';
  }
  else if (in1 == '1' && in2 == '1')
  {
    return '1';
  }
  return '0';
}

char Gate::eval_or()const
{
  char in1 = input1->getValue();
  char in2 = input2->getValue();
  if (in1 == '1' || in2 == '1')
  {
    return '1';
  }
  else if (in1 == 'X' || in2 == 'X')
  {
    return 'X';
  }
  return '0';
}

char Gate::eval_xor()const
{
  char in1 = input1->getValue();
  char in2 = input2->getValue();
  if (in1 == in2)
  {
    return '0';
  }
  else
  {
    return '1';
  }
}

char not_func(char in)
{
  if (in == '0')
  {
    return '1';
  }
  else if (in == '1')
  {
    return '0';
  }
  return 'X';
}
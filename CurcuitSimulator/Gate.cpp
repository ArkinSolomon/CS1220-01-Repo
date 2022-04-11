
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
  char in1 = input1->getValue();
  switch (type)
  {
  case AND:
    return eval_and();
    break;

  case OR:
    return eval_or();
    break;

  case NOT:
    return not_func(in1);
    break;

  case XOR:
    return eval_xor();
    break;

  case NAND:
    char andOut = eval_and();
    return not_func(andOut);
    break;

  case NOR:
    char orOut = eval_or();
    return not_func(orOut);
    break;

  case XNOR:
    char xorOut = eval_xor();
    return not_func(xorOut);
    break;

  default:
    return 'X';
  }
}

friend char eval_and()
{
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

friend char eval_or()
{
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

friend char eval_xor()
{
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
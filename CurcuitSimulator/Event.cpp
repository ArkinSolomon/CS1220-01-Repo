// Author:  Olivia Walrath and Arkin Solomon
// Date:    4/15/20
// Purpose: To track events for easy strorage in queue
// 4/15/2022 -OW/AS -Defined all of the functions
#include "Event.h"
#include <string>

Event::Event(int i, int t, Wire* w, char v)
{
  index = i;
  time = t;
  wire = w;
  value = v;
}

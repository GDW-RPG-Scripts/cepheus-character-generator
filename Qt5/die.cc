#include "die.hh"

#include <cstdlib>

using namespace GDW::RPG;

int
Die::Roll(int number)
{
  int result = 0;

  for(int i = 0; i < number; i++)
    result += rand() % 6 + 1;

  return result;
}

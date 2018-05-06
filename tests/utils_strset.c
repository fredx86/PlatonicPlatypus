#include <assert.h>
#include <string.h>

#include "pp/utils.h"

int main()
{
  char buf[8];
  assert(strcmp(strset(buf, "test", 8), "test") == 0);
  assert(strcmp(strset(buf, "test", 2), "t") == 0);
  assert(strcmp(strset(buf, "test", 1), "") == 0);
  return (0);
}

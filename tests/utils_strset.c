#include <assert.h>
#include <string.h>

#include "pp/utils.h"

int main()
{
  char buf[8];
  assert(strcmp(strset(buf, 8, "test"), "test") == 0);
  assert(strcmp(strset(buf, 2, "test"), "t") == 0);
  assert(strcmp(strset(buf, 1, "test"), "") == 0);
  return (0);
}

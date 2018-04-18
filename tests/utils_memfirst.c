#include <assert.h>
#include <string.h>

#include "pp/utils.h"

int main()
{
  const char* test = "abc";
  assert(memfirst(test, strlen(test), test, strlen(test)) == test);
  assert(memfirst(test, strlen(test), "a", 1));
  assert(memfirst(test, strlen(test), "b", 1));
  assert(memfirst(test, strlen(test), "c", 1));
  assert(memfirst(test, strlen(test), "c", 1) == test + 2);
  assert(memfirst(test, strlen(test), "0", 1) == NULL);
  return (0);
}

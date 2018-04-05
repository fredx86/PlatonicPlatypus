#include <assert.h>
#include <string.h>

#include "../utils.h"

int main()
{
  const char* test = "abc";
  assert(bytesfirst(test, strlen(test), test, strlen(test)) == test);
  assert(bytesfirst(test, strlen(test), "a", 1));
  assert(bytesfirst(test, strlen(test), "b", 1));
  assert(bytesfirst(test, strlen(test), "c", 1));
  assert(bytesfirst(test, strlen(test), "c", 1) == test + 2);
  assert(bytesfirst(test, strlen(test), "0", 1) == NULL);
  return (0);
}

#include <stdio.h>
#include <assert.h>
#include "../barray.h"

int main()
{
  char big_alloc[4096] = { 42 };
  ba_t* array = ba_create(NULL, 0);

  assert(array != NULL);
  assert(array->size == 0);
  assert(ba_app(NULL, "a", 1) == NULL);
  assert(ba_app(array, "a", 1) != NULL);
  assert(array->size == 1);
  assert(array->bytes[0] == 'a');
  assert(ba_app(array, "bc", 2) != NULL);
  assert(array->size == 3);
  assert(array->bytes[1] == 'b');
  assert(array->bytes[2] == 'c');
  assert(ba_app_byte(array, 'd') != NULL);
  assert(array->size == 4);
  assert(ba_app(array, big_alloc, 4096) != NULL);
  assert(array->size == 4100);

  assert(ba_find(NULL, "cd", 2) == NULL);
  assert(ba_find(array, "cd", 2) != NULL);
  assert(ba_find(array, "abcde", 5) == NULL);
  assert(ba_find(array, "f", 1) == NULL);
  assert(ba_find_byte(NULL, 'a') == NULL);
  assert(ba_find_byte(array, 'a') != NULL);
  assert(ba_find_byte(array, 'f') == NULL);

  ba_destroy(array);

  fprintf(stderr, "[assert] All tests passed successfully\n");
  return (0);
}

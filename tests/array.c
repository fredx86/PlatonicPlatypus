#include <assert.h>

#include "pp/array.h"

int main()
{
  array_t array;

  assert(array_init(&array, sizeof(int)));
  assert(array_push_back(&array, &(int){ 0 }));
  assert(array_push_front(&array, &(int){ -1 }));
  assert(array_insert(&array, 1, &(int){ 42 }));
  assert(array.size == 3);
  array_erase(&array, 2);
  assert(*(int*)array_at(&array, 0) == -1);
  assert(*(int*)array_at(&array, 1) == 42);
  array_clear(&array);

  assert(array.size == 0);
  assert(array_push_back(&array, &(int){ 0 }));
  assert(*(int*)array_at(&array, 0) == 0);
  array_clear(&array);

  int list[] = { 0, 2, 4 };
  assert(array_append_at(&array, 0, list, 3));
  assert(array.size == 3);
  assert(*(int*)array_at(&array, 0) == 0);
  assert(*(int*)array_at(&array, 1) == 2);
  assert(*(int*)array_at(&array, 2) == 4);
  array_clear(&array);
  return (0);
}

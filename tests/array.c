#include <assert.h>

#include "pp/array.h"

typedef unsigned char uchar;

int matches_uchar(const void* left, const void* right)
{
  return *(uchar*)left == *(uchar*)right;
}

int main()
{
  array_t array;

  assert(array_init(&array, sizeof(uchar)));
  assert(array_push_back(&array, &(uchar){ 0 }));
  assert(array_push_front(&array, &(uchar){ 255 }));
  assert(array_insert(&array, 1, &(uchar){ 42 }));
  assert(array.size == 3);
  array_erase_at(&array, 2);
  assert(*(uchar*)array_at(&array, 0) == 255);
  assert(*(uchar*)array_at(&array, 1) == 42);
  array_clear(&array);

  assert(array.size == 0);
  assert(array_push_back(&array, &(uchar){ 0 }));
  assert(*(uchar*)array_at(&array, 0) == 0);
  array_clear(&array);

  uchar list[] = { 0, 2, 4 };
  assert(array_emplace(&array, 0, list, 3));
  assert(array.size == 3);
  assert(*(uchar*)array_at(&array, 0) == 0);
  assert(*(uchar*)array_at(&array, 1) == 2);
  assert(*(uchar*)array_at(&array, 2) == 4);
  array_clear(&array);

  assert(array_push_back(&array, &(uchar){ 42 }));
  assert(array_push_back(&array, &(uchar){ 10 }));
  assert(array_find(&array, &(uchar){ 0 }, &matches_uchar) == NULL);
  uchar* element = array_find(&array, &(uchar){ 42 }, &matches_uchar);
  assert(element && *element == 42);
  assert(array_find(&array, element, NULL));
  array_remove(&array, element);
  assert(array.size == 1);
  assert(*(uchar*)array_at(&array, 0) == 10);
  array_clear(&array);

  assert(array_add_back(&array));
  assert(array_add(&array, 0));
  assert(array_add_front(&array));
  assert(array.size == 3);
  *(uchar*)array_at(&array, 0) = 0;
  *(uchar*)array_at(&array, 1) = 255;
  *(uchar*)array_at(&array, 2) = 42;
  assert(*(uchar*)array_at(&array, 0) == 0);
  assert(*(uchar*)array_at(&array, 1) == 255);
  assert(*(uchar*)array_at(&array, 2) == 42);
  array_clear(&array);

  assert(array_emplace_front(&array, "HELLO WORLD I AM A TEST", 24));
  array_erase(&array, 5, 6);
  assert(strcmp("HELLO I AM A TEST", array.content) == 0);
  array_erase(&array, 5, 12);
  assert(strcmp("HELLO", array.content) == 0);
  array_clear(&array);
  return (0);
}

#include <assert.h>
#include <string.h>
#include "../barray.h"

int main()
{
  char big_alloc[4096] = { 0 };
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
  assert(ba_app(array, big_alloc, 4096) != NULL);
  assert(array->size == 4099);

  assert(ba_app_byte(NULL, 'd') == NULL);
  assert(ba_app_byte(array, 'd') != NULL);
  assert(array->size == 4100);

  assert(ba_insert(NULL, 0, "0", 1) == NULL);
  assert(ba_insert(NULL, 4100, "0", 1) == NULL);
  assert(ba_insert(array, 0, "0", 1) != NULL);
  assert(array->bytes[0] == '0');
  assert(array->bytes[1] == 'a');
  assert(array->size == 4101);
  assert(ba_insert(array, 1, "123", 3) != NULL);
  assert(array->bytes[1] == '1');
  assert(array->bytes[3] == '3');
  assert(array->bytes[4] == 'a');
  assert(array->size == 4104);
  assert(ba_insert(array, 4103, "!!", 2) != NULL);
  assert(array->bytes[4104] == '!');
  assert(array->size == 4106);

  assert(ba_replace(NULL, 0, "42", 2) == NULL);
  assert(ba_replace(array, 0, "42", 2) != NULL);
  assert(array->size == 4106);
  assert(array->bytes[0] == '4');
  assert(array->bytes[1] == '2');
  assert(ba_replace(array, 42, "!", 1) != NULL);
  assert(array->bytes[42] == '!');
  assert(ba_replace(array, 4106, "*", 1) == NULL);

  assert(ba_erase(NULL, 0, 0) == NULL);
  assert(ba_erase(array, 0, 1) != NULL);
  assert(array->bytes[0] == '2');
  assert(array->size == 4105);
  assert(ba_erase(array, 4105, 1) == NULL);
  assert(ba_erase(array, 0, 4106) == NULL);

  assert(ba_find(NULL, "!!", 2) == NULL);
  assert(ba_find(array, "!!", 2) != NULL);
  assert(ba_find(array, "abcdefgh", 8) == NULL);
  assert(ba_find(array, "h", 1) == NULL);

  assert(ba_find_byte(NULL, 'a') == NULL);
  assert(ba_find_byte(array, 'a') != NULL);
  assert(ba_find_byte(array, 'h') == NULL);

  ba_clear(array);

  assert(ba_app_format(array, "%X:%d", 42, 42) != NULL);
  assert(array->size == 5);
  assert(strcmp(array->bytes, "2A:42") == 0);

  ba_destroy(array);
  return (0);
}

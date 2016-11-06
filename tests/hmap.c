#include <assert.h>
#include <pp/hmap.h>

void _hmap()
{
  hmap_t map;

  assert(hmcrt(&map, 2, HM_STRING) != NULL);
  assert(hmget(&map, "a") == NULL);
  assert(hmadd(&map, "a", "Hello") != NULL);
  assert(hmget(&map, "a") != NULL);
  assert(strcmp((char*)hmget(&map, "a")->value, "Hello") == 0);
  assert(hmadd(&map, "a", "World") != NULL);
  assert(hmget(&map, "a") != NULL);
  assert(strcmp((char*)hmget(&map, "a")->value, "World") == 0);
  assert(hmadd(&map, "b", "collision") != NULL);
  assert(hmget(&map, "b") != NULL);
  assert(strcmp((char*)hmget(&map, "b")->value, "collision") == 0);
  assert(hmadd(&map, "c", "collision2") != NULL);
  assert(hmget(&map, "c") != NULL);
  assert(strcmp((char*)hmget(&map, "c")->value, "collision2") == 0);
}
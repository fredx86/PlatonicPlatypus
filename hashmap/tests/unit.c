#include <assert.h>
#include "../hmap.h"

int main()
{
  hm_t* map = hm_create(1, HM_STRING, &hm_jenkins);

  assert(map != NULL);
  assert(hm_get(map, "a") == NULL);
  assert(hm_put(map, "a", "Hello") != NULL);
  assert(hm_get(map, "a") != NULL);
  assert(strcmp((char*)hm_get(map, "a")->value, "Hello") == 0);
  assert(hm_put(map, "a", "World") != NULL);
  assert(hm_get(map, "a") != NULL);
  assert(strcmp((char*)hm_get(map, "a")->value, "World") == 0);
  assert(hm_put(map, "b", "collision") != NULL);
  assert(hm_get(map, "b") != NULL);
  assert(strcmp((char*)hm_get(map, "b")->value, "collision") == 0);
  assert(hm_put(map, "c", "collision2") != NULL);
  assert(hm_get(map, "c") != NULL);
  assert(strcmp((char*)hm_get(map, "c")->value, "collision2") == 0);

  hm_clear(map);
  assert(hm_get(map, "a") == NULL);
  assert(hm_put(map, "a", NULL) != NULL);
  assert(hm_get(map, "a") != NULL);

  hm_destroy(map);
  return (0);
}

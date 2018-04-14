#include <assert.h>
#include <stdio.h>

#include "pp/thpool.h"

#define NMEMBR 15

int routine(void* arg)
{
  (void)arg;
  //TODO Check if was called X times
  return (0);
}

int main()
{
  thpool_t pool;
  int array[NMEMBR];

  for (int i = 0; i < NMEMBR; ++i)
  {
    array[i] = i;
  }
  assert(thpool_init(&pool, 5));
  assert(thpool_map(&pool, array, NMEMBR, sizeof(*array), &routine) >= 0);
  assert(thpool_join(&pool) >= 0);
  return (0);
}

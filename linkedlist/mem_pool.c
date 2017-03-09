#include "mem_pool.h"

void* mem_get(unsigned size)
{
  return (malloc(size));
}

void mem_release(void* ptr)
{
  free(ptr);
}
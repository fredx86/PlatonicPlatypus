#include "mem_pool.h"

void* mem_get(size_t size)
{
  return (malloc(size));
}

void* mem_get_from(void* ptr, size_t size)
{
  if (ptr == NULL)
    return (mem_get(size));
  return (realloc(ptr, size));
}

void mem_release(void* ptr)
{
  free(ptr);
}
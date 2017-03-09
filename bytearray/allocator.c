#include "pp/allocator.h"

int alloc_re(struct allocator* alloc, size_t size)
{
  if (size <= *alloc->alloc_size)
    return (1);
  if ((*alloc->data = realloc(*alloc->data, size * alloc->type_size)) == NULL)
    return (0);
  *alloc->alloc_size = size;
  return (1);
}

int alloc_pow2(struct allocator* alloc, size_t size, size_t minalloc)
{
  while (minalloc <= size)
    minalloc = minalloc << 1;
  return (alloc_re(alloc, minalloc));
}
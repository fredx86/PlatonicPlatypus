#include "pp/allocator.h"

int allocator_re(struct allocator* alloc, size_t size, size_t minalloc)
{
  if (size <= *alloc->alloc_size)
    return (1);
  while (minalloc <= size)
    minalloc = minalloc << 1;
  if ((*alloc->data = realloc(*alloc->data, minalloc * alloc->type_size)) == NULL)
    return (0);
  *alloc->alloc_size = minalloc;
  return (1);
}
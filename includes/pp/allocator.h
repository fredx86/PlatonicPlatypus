#ifndef PP_ALLOCATOR_H_
#define PP_ALLOCATOR_H_

#include <string.h>
#include <stdlib.h>

struct allocator
{
  void** data;
  size_t type_size;
  size_t* alloc_size;
};

int alloc_re(struct allocator*, size_t);
int alloc_pow2(struct allocator*, size_t, size_t);

#endif
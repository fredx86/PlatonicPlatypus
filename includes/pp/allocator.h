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

//Return: 1 Success - 0 Error
int alloc_re(struct allocator*, size_t size, size_t minalloc);

#endif
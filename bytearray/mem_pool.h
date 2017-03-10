#ifndef MEM_POOL_H_
#define MEM_POOL_H_

#include <stdlib.h>

void* mem_get(size_t size);
void* mem_get_from(void* ptr, size_t size);
void mem_release(void* ptr);

#endif
#ifndef MEM_POOL_H_
#define MEM_POOL_H_

#include <stdlib.h>

void* mem_get(unsigned size);
void mem_release(void* ptr);

#endif
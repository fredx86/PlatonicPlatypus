#ifndef BARRAY_H_
#define BARRAY_H_

#include <string.h>
#include "mem_pool.h"

typedef struct s_barray
{
  char* bytes;
  size_t size;
  size_t alloc;
} ba_t;

ba_t* ba_create(const void*, size_t);

void ba_clear(ba_t*);
ba_t* ba_set(ba_t*, const void*, size_t);
ba_t* ba_app(ba_t*, const void*, size_t);
ba_t* ba_app_byte(ba_t*, char);

ba_t* ba_insert(ba_t*, size_t, const void*, size_t);
ba_t* ba_replace(ba_t*, size_t, const void*, size_t);

ba_t* ba_erase(ba_t*, size_t, size_t);

void* ba_find(const ba_t*, const void*, size_t);
void* ba_find_byte(const ba_t*, char);

void ba_destroy(ba_t*);

int ba_memory_for(ba_t*, size_t n); /* Allocate enough memory for size n + actual size of array. Return 0 on error, 1 on success */
size_t ba_alloc_size(size_t n); /* Return in bytes, the alloc size needed for n bytes */

#endif

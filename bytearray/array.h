#ifndef PP_ARRAY_H_
#define PP_ARRAY_H_

#include "allocator.h"

typedef struct s_array
{
  void** item;
  size_t size;
  size_t _alloc;
} array_t;

array_t* arcrt(array_t*, size_t, void**);
array_t* arcrts(array_t*, size_t);

array_t* aradd(array_t*, void*);
array_t* arrmvv(array_t*, const void*);
array_t* arrmvi(array_t*, size_t);

ssize_t arindex(array_t*, const void*);
int arhas(array_t*, const void*);

void ardel(array_t*);


/* ARRAY UTILS */

int _arrealloc(array_t*, size_t);

#endif
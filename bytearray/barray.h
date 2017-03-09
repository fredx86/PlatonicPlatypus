#ifndef PP_BARRAY_H_
#define PP_BARRAY_H_

#include <string.h>
#include <stdarg.h>
#include "allocator.h"

typedef struct s_barray
{
  char* bytes;
  size_t size;
  size_t _alloc;
} barray_t;

barray_t* bacrt(barray_t*, const void*, size_t);
barray_t* bacrts(barray_t*, size_t);

barray_t* bacpy(barray_t*, const void*, size_t);
barray_t* baapp(barray_t*, const void*, size_t);
barray_t* baappc(barray_t*, char);
barray_t* baappv(barray_t*, size_t count, ...);

barray_t* bainsrt(barray_t*, size_t, const void*, size_t);
barray_t* barplc(barray_t*, size_t, const void*, size_t);

barray_t* basub(barray_t*, barray_t*, size_t, size_t);
barray_t* barmv(barray_t*, size_t, size_t);

int bacmp(barray_t*, const void*, size_t);
ssize_t bafnd(barray_t*, const void*, size_t);

void badel(barray_t*);


/* BARRAY UTILS */

int _barealloc(barray_t*, size_t);

/*
Tranform a pos and size to fit within the barray.
Return 1 on success, 0 on erroneous pos/size
*/
int _batransform(barray_t*, size_t* pos, size_t* size);

#endif
#ifndef PP_UTILS_H_
#define PP_UTILS_H_

#include <stdio.h>
#include "array.h"
#include "barray.h"

void putb(const void*, size_t);
void fputb(const void*, size_t, FILE*);

int endianess(); /* 1 is little endian, 0 is big endian */
void* revbytes(void*, size_t);

//int split(array_t*, const char*, size_t);

#endif
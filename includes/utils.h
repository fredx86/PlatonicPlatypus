#ifndef PP_UTILS_H_
#define PP_UTILS_H_

#include <stdlib.h>

/*
  @return       Pointer to the first occurence from haystack or NULL if not found
  @description  Finds the first occurrence of needle in haystack
*/
void* bytesfirst(const void* haystack, size_t hsize, const void* needle, size_t nsize);

#endif

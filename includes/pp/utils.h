#ifndef PP_UTILS_H_
#define PP_UTILS_H_

#include <stdlib.h>

/*
  @return       1 if system is big endian, 0 otherwise
*/
int is_little_endian();

/*
  @return       Pointer to the first occurence from haystack or NULL if not found
  @description  Finds the first occurrence of needle in haystack
*/
void* memfirst(const void* haystack, size_t hsize, const void* needle, size_t nsize);

/*
  @return       dest
  @description  Copies the string from src to dest, including \0
                If src is greater than maxlen, dest will be truncated
  @warning      If maxlen is 0, undefined behaviour
*/
char* strset(char* dest, const char* src, size_t maxlen);

#endif

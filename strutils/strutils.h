#ifndef STRUTILS_H_
#define STRUTILS_H_

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef int (*str_ctype_f)(int);

size_t str_count(const char*, char);
size_t str_count_f(const char*, str_ctype_f contains);
size_t str_count_substr(const char*, const char* substr);
char* str_consume(char*, str_ctype_f contains);

/*
  Copy the content of src into *dest using strdup
  If src is NULL, dest is set to NULL
  Return -1 on error
*/
int str_dup(char** dest, const char* src);

/*
  Copy src into dest until \0 OR if max_len is reached
  Always add a \0 at the end of dest
  Return dest
*/
char* str_cpy_max(char* dest, const char* src, size_t max_len);

/*
  All function listed below transform the char* given in parameter
  They DO NOT use and return a copy !
*/
char* str_lower(char*);
char* str_upper(char*);
char* str_trim(char*);
char* str_tokenize(char*, char);
char** str_split(char*, const char*, int* size);

/* Returns the argument from 'needle=' if exists within the haystack of size 'size'. Returns NULL otherwise */
char* str_argument(size_t size, char** haystack, const char* needle);

#endif

#ifndef STR_UTILS_H_
#define STR_UTILS_H_

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef int (*str_ctype_f)(int);

int str_count(const char*, char);
int str_count_f(const char*, str_ctype_f contains);
char* str_consume(char*, str_ctype_f contains);

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
char** str_split(char*, char, int* size);

#endif
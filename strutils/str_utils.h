#ifndef STR_UTILS_H_
#define STR_UTILS_H_

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef int (*str_ctype_f)(int);

int str_count(char*, char);
char* str_consume(char*, str_ctype_f contains);

char* str_trim(char*); /* trim() the string given in parameter. Not a copy ! */
char* str_tokenize(char*, char); /* tokenize() the string given in parameter. Not a copy ! */
char** str_split(char*, char, int* size); /* split() the string given in parameter, and fill the size pointer. Not a copy ! */

#endif
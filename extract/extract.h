#ifndef EXTRACT_H_
#define EXTRACT_H_

#include <stdarg.h>
#include "barray.h"
#include "strutils.h"

struct s_extract
{
  char flag;
  char type;
  union
  {
    char* (*str)(char*);
    str_ctype_f chr;
  } eval;
  void (*extract)(char*, void*);
};

void extract_as_char(char*, void*);
void extract_as_str(char*, void*);
void extract_as_int(char*, void*);
void extract_as_float(char*, void*);

char* extract_modulo(char*);
char* extract_identifier(char*);
char* extract_number(char*);
char* extract_floating_point(char*);

struct s_extract* extract_get(char);
char* extract_eval(char*, struct s_extract*);
int extract_consume(char**, ba_t*, struct s_extract*, va_list*);

/* Return -1 on failure, 0 on success */
int extract(const char*, const char* frmt, ...);

#endif
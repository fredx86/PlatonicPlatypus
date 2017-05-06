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

/* Return -1 on failure, 0 on success */
int extract(const char*, const char* frmt, ...);

#endif
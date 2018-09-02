#include "pp/fassert.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void _fassert(int val, const char* expr, const struct log_info* info)
{
  int e = errno;
  if (!val)
  {
    logger(info, "%s: %s (%d)", expr, strerror(e), e);
    exit(1);
  }
}

void* _fassert_ptr(void* ptr, const char* expr, const struct log_info* info)
{
  if (ptr != NULL)
  {
    return ptr;
  }
  _fassert(0, expr, info);
  return NULL;
}

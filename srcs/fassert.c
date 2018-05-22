#include "pp/fassert.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void* _fassert(void* ptr, const char* expr, const struct log_info* info)
{
  int e = errno;
  if (ptr != NULL)
  {
    return ptr;
  }
  logger(info, "%s: %s (%d)", expr, strerror(e), e);
  exit(1);
  return NULL;
}

#ifndef FASSERT_H_
#define FASSERT_H_

#include "pp/logger.h"

/*
  @return       Value returned by expr. Must be a pointer
  @description  Assert if the result of expr is not NULL using fassert_f
                If NULL, log as fatal and exit(1)
*/
#define fassert(expr) (_fassert((expr), #expr, TRC_FATAL))

/*
  @return       ptr
  @description  Assert if ptr is not NULL
                If NULL, log using info and exit(1)
                Will display the given expr and the last errno status
*/
void* _fassert(void* ptr, const char* expr, const struct log_info* info);

#endif

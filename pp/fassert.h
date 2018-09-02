#ifndef FASSERT_H_
#define FASSERT_H_

#include "pp/logger.h"

/*
  @return       void
  @description  Assert if the result of expr is true using _fassert()
                If false, log as fatal and exit(1)
*/
#define fassert(expr)   (_fassert((expr), #expr, TRC_FATAL))

/*
  @return       Value returned by expr. Must be a pointer
  @description  Assert if the result of expr is not NULL using _fassert_ptr()
                If NULL, log as fatal and exit(1)
*/
#define fassertp(expr)  (_fassert_ptr((expr), #expr, TRC_FATAL))

/*
  @description  Assert val: If false, log using info and exit(1)
                Will display the given expr and the last errno status
*/
void _fassert(int val, const char* expr, const struct log_info* info);

/*
  @return       ptr
  @description  Assert ptr: if NULL, log using info and exit(1)
                Will display the given expr and the last errno status
                Uses _fassert()
*/
void* _fassert_ptr(void* ptr, const char* expr, const struct log_info* info);

#endif

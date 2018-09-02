#ifndef PP_REALTIME_H_

#include <time.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct realtime
{
  time_t seconds; /* Seconds since epoch */
  int16_t milliseconds;
} realtime_t;

/*
  @return       1 on success, 0 on error
  @description  Get the current real time
*/
int realtime_now(realtime_t* time);

/*
  @return       Elapsed time in seconds
  @description  Get the elapsed time between end and begin in seconds
                Milliseconds are considered (decimal places)
  @warning      Undefined behaviour if end or begin is NULL
*/
float realtime_elapsed(const realtime_t* end, const realtime_t* begin);

#endif

#include "pp/realtime.h"

#ifdef __unix__
  #include <sys/time.h>
#endif

int realtime_now(realtime_t* time)
{
#ifdef __unix__
  struct timeval tv;

  if (gettimeofday(&tv, NULL) < 0)
  {
    return 0;
  }
  time->seconds = tv.tv_sec;
  time->milliseconds = tv.tv_usec / 1000;
  return 1;
#else
  #error realtime_now() not supported for your OS
#endif
}

float realtime_elapsed(const realtime_t* end, const realtime_t* begin)
{
  time_t seconds = end->seconds - begin->seconds;
  int16_t ms = end->milliseconds - begin->milliseconds;
  if (ms > 1000)
  {
    ms -= 1000;
    seconds += 1;
  }
  return seconds + (ms / 1000.0f);
}

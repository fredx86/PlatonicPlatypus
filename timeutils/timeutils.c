#include "timeutils.h"

void time_from_seconds(struct timeval* time, float seconds)
{
  time->tv_sec = (int)seconds;
  time->tv_usec = (seconds - (int)seconds) * 1000000;
}

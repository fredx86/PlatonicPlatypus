#include "timeutils.h"

float time_as_diff(const struct timeval* time)
{
  struct timeval now;

  gettimeofday(&now, NULL);
  return (now.tv_sec - time->tv_sec + (now.tv_usec - time->tv_usec / 1000000.0));
}

void time_from_seconds(struct timeval* time, float seconds)
{
  time->tv_sec = (int)seconds;
  time->tv_usec = (seconds - (int)seconds) * 1000000;
}

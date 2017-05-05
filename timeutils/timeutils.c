#include "timeutils.h"

void time_reset(struct timeval* time)
{
  time->tv_sec = 0;
  time->tv_usec = 0;
}

void time_from_seconds(struct timeval* time, float seconds)
{
  time->tv_sec = (int)seconds;
  time->tv_usec = (seconds - (int)seconds) * 1000000;
}

float time_to_seconds(const struct timeval* time)
{
  return (time->tv_sec + (time->tv_usec / 1000000.0));
}

void time_add(struct timeval* dest, const struct timeval* src)
{
  dest->tv_sec += src->tv_sec;
  if (dest->tv_usec + src->tv_usec >= 1000000)
  {
    dest->tv_sec = (dest->tv_usec + src->tv_usec) / 1000000;
    dest->tv_usec = (dest->tv_usec + src->tv_usec) - 1000000;
  }
  else
  {
    dest->tv_usec += src->tv_usec;
  }
}

float time_as_seconds_diff(const struct timeval* time)
{
  struct timeval now;
  gettimeofday(&now, NULL);
  return (now.tv_sec - time->tv_sec + ((now.tv_usec - time->tv_usec) / 1000000.0));
}
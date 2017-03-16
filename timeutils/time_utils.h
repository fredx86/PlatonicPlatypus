#ifndef TIME_UTILS_H_
#define TIME_UTILS_H_

#include <sys/time.h>

void time_from_seconds(struct timeval*, float seconds);

#endif
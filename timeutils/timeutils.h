#ifndef TIMEUTILS_H_
#define TIMEUTILS_H_

#include <sys/time.h>

float time_as_diff(const struct timeval*);
void time_from_seconds(struct timeval*, float seconds);

#endif

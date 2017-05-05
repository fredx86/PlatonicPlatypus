#ifndef TIMEUTILS_H_
#define TIMEUTILS_H_

#include <stdlib.h>
#include <sys/time.h>

void time_reset(struct timeval*);

void time_from_seconds(struct timeval*, float seconds);
float time_to_seconds(const struct timeval*);

void time_add(struct timeval* dest, const struct timeval* src);

float time_as_seconds_diff(const struct timeval*);

#endif

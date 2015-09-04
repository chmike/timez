#ifndef TIMEZ_H
#define TIMEZ_H
#include <stdbool.h>
#include <time.h>

typedef long long signed int timez_t; // absolute time with tz

#define TIMEZ_INVALID (0LL)

/* Return the current time or TIMEZ_INVALID if failed */
timez_t timez_now();

/* Return the time or TIMEZ_INVALID based on the time spec tp
 * obtained from clock_gettime() and the time zone tz.
 * tz is in minutes units and must be in the range -1023 to 1023.
 * If tz is -1024, the returned timez is invalid.
 */
timez_t timez_new(struct timespec *tp, const short tz);

/* Return true if the timez t is valid */
bool timez_valid(const timez_t t);

/* Return false if timez is invalid. Otherwise set timespec tp if not NULL
 * and set time zone tz if not NULL and return true.
 */
bool timez_get(struct timespec *tp, short *tz, const timez_t t);

/* return the difference between t1 and t2 in microsecond units */
long long timez_diff(timez_t t1, timez_t t2);

/* Return a timez as t + microseconds or TIMEZ_INVALID if would
 * overflow or underflow.
 */
timez_t timez_add(const timez_t t, const long long microseconds);


#endif // TIMEZ_H


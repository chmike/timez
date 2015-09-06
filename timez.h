#ifndef TIMEZ_H
#define TIMEZ_H
#include <stdbool.h>
#include <time.h>

typedef long long signed int timez_t; // absolute time with tz

#define TIMEZ_INVALID (0LL)

/* Return the current time or TIMEZ_INVALID if failed */
timez_t timez_now();

/* Return the timez_t combining time spec tp and time offset to. The value
 * tp is obtained from clock_gettime(CLOCK_REALTIME), and to is the time
 * offset between the UTC and the local time.
 * If tp is NULL or tp->seconds is negative, or to is not in the range
 * -2047 to 2047, the function returns TIMEZ_INVALID.
 */
timez_t timez_new(struct timespec *tp, const short to);

/* Return true if the timez t is valid */
bool timez_valid(const timez_t t);

/* Returns false if timez t is invalid, otherwise stores in the timespec tp
 * the wall clock time if it is not NULL, and stores the time offset in to
 * if it is not NULL.
 */
bool timez_get(struct timespec *tp, short *to, const timez_t t);

/* return the difference between t1 and t2 in microsecond units */
long long timez_diff(timez_t t1, timez_t t2);


#endif // TIMEZ_H


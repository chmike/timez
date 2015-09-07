#ifndef TIMEZ_H
#define TIMEZ_H
#include <stdbool.h>
#include <time.h>


#define TIMEZ_OFFSET_BITS 11
#define TIMEZ_INVALID (0LL)
#define TIMEZ_INVALID_COUNT (-1LL << 63)
#define TIMEZ_INVALID_OFFSET (-1 << 31)

/* Wall clock time with local time offset to UTC */
typedef long long signed int timez_t;

/* Convert the timespec tp into the number of micro seconds elapsed
 * since epoch. Returns TIMEZ_INVALID_COUNT if tp is NULL. The timespec
 * tp is usually obtained from clock_gettime(CLOCK_REALTIME, &tp).
 */
long long timez_tp2count(const struct timespec *tp);

/* Convert the number of micro seconds elapsed since epoch into the
 * timespec tp. Returns false if would overflow or tp is NULL.
 */
bool timez_count2tp(struct timespec *tp, const long long count);

/* Return the current time or TIMEZ_INVALID if failed */
timez_t timez_now();

/* Return the timez_t combining the number of micro seconds elapsed since
 * the epoch and the time offset relative to the UTC time. Adding offset to
 * the UTC time should yield the local time.
 * The function returns TIMEZ_INVALID if it would overflow.
 */
timez_t timez_new(long long count, const int offset);

/* Return true if the timez t is valid */
bool timez_valid(const timez_t t);

/* Returns the number of micro seconds elapsed since epoch part of t, or
 * TIMEZ_INVALID_COUNT if t is TIMEZ_INVALID.
 */
long long timez_count(const timez_t t);

/* Returns the time offset part of t, or TIMEZ_INVALID_OFFSET if t is
 * TIMEZ_INVALID.
 */
int timez_offset(const timez_t t);



#endif // TIMEZ_H


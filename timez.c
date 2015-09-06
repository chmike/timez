#include "timez.h"

#define TOFFBITS 12
#define TOFFMID 2048
#define TOFFMASK 0xFFF
#define TIMEMID (1LL<<51)

timez_t timez_now() {
    struct timespec tp;
    tzset();
    // This is incorret for countries with a DST != 1 hour
    long to = -timezone / 60 + (daylight ? 60 : 0);
    if ((timezone % 60) == 0 && !clock_gettime(CLOCK_REALTIME, &tp) &&
            to > -TOFFMID && to < TOFFMID) {
        return timez_new(&tp, (short)to);
    }
    return TIMEZ_INVALID;
}


timez_t timez_new(struct timespec *tp, const short to) {
    if (tp && to > -TOFFMID && to < TOFFMID) {
        long long t = tp->tv_sec * 1000000LL + tp->tv_nsec / 1000;
        if (t >= 0 && (t -= TIMEMID) < TIMEMID) {
            return (t << TOFFBITS) | (to + TOFFMID);
        }
    }
    return TIMEZ_INVALID;
}


bool timez_valid(const timez_t t) {
    return (t & TOFFMASK) != 0;
}


bool timez_get(struct timespec *tp, short *to, const timez_t t) {
    short tmp_to = t & TOFFMASK;
    long long tmp_t = t >> TOFFBITS;
    if (tmp_to != 0 && tmp_t >= -TIMEMID && tmp_t < TIMEMID) {
        if (to) {
            *to = tmp_to - TOFFMID;
        }
        if (tp) {
            tmp_t += TIMEMID;
            tp->tv_sec = (long)(tmp_t / 1000000);
            tp->tv_nsec = (long)(tmp_t % 1000000) * 1000;
        }
        return true;
    }
    return false;
}


long long timez_diff(timez_t t1, timez_t t2) {
    return ((t1 >> TOFFBITS) + TIMEMID) - ((t2 >> TOFFBITS) + TIMEMID);
}



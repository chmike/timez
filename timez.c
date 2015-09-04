#include "timez.h"

timez_t timez_now() {
    struct timespec tp;
    tzset();
    long tz = -timezone / 60 + 60 * daylight;
    if (!clock_gettime(CLOCK_REALTIME, &tp) && tz > -1024 && tz < 1024) {
        timez_t t = tp.tv_sec;
        return (((t * 1000000) + (tp.tv_nsec / 1000)) << 11) | (tz + 1024);
    }
    return TIMEZ_INVALID;
}


timez_t timez_new(struct timespec *tp, const short tz) {
    if (tp && tz > -1024 && tz < 1024) {
        timez_t t = tp->tv_sec;
        return (((t * 1000000) + (tp->tv_nsec / 1000)) << 11) | (tz + 1024);
    }
    return TIMEZ_INVALID;
}


bool timez_valid(const timez_t t) {
    return (t & 0x7FF) != 0;
}


bool timez_get(struct timespec *tp, short *tz, const timez_t t) {
    short tmp_tz = t & 0x7FF;
    if (tmp_tz > 0 && (t & ~0x7FF) > (1LL << 63)) {
        if (tz) {
            *tz = tmp_tz - 1024;
        }
        if (tp) {
            long long tmp_t = t >> 11;
            tp->tv_sec = tmp_t / 1000000;
            tp->tv_nsec = (tmp_t % 1000000) * 1000;
        }
        return true;
    }
    return false;
}


long long timez_diff(timez_t t1, timez_t t2) {
    return (t1 >> 11) - (t2 >> 11);
}


timez_t timez_add(const timez_t t, const long long microseconds) {
    long long t1 = (t >> 11) + microseconds, s = t1 & 0xFFF0000000000000LL;
    if (s != 0LL && s ^ 0xFFF0000000000000LL)
        return TIMEZ_INVALID;
    return (t1 << 11) | (t & 0x7FF);
}


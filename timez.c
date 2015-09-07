#include "timez.h"

#define TIMEZ_OBITS TIMEZ_OFFSET_BITS
#define TIMEZ_OMID (1 << (TIMEZ_OBITS - 1))
#define TIMEZ_OMASK ((1LL << TIMEZ_OBITS) - 1)
#define TIMEZ_CMID (1LL << (63 - TIMEZ_OBITS))


long long timez_tp2count(const struct timespec *tp) {
    return tp ? (tp->tv_sec * 1000000LL) + (tp->tv_nsec / 1000) : 0;
}


bool timez_count2tp(struct timespec *tp, const long long count) {
    const long long time_t_max = (1LL << 31) * 1000000;
    if (tp && count >= -time_t_max && count < time_t_max) {
        tp->tv_sec = (long)(count / 1000000);
        long long tmp = (count < 0) ? -count : count;
        tp->tv_nsec = (long)(tmp % 1000000) * 1000;
        return true;
    }
    return false;
}


timez_t timez_now() {
    struct timespec tp;
    tzset();
    // This is incorret for countries with a DST different of one hour
    int to = (short)(-timezone / 60 + (daylight ? 60 : 0));
    if ((timezone % 60) == 0 && clock_gettime(CLOCK_REALTIME, &tp) == 0) {
        return timez_new(timez_tp2count(&tp), to);
    }
    return TIMEZ_INVALID;
}


timez_t timez_new(long long count, const int offset) {
    return (count >= -TIMEZ_CMID && count < TIMEZ_CMID &&
            offset > -TIMEZ_OMID && offset < TIMEZ_OMID) ?
                (count << TIMEZ_OBITS) | (offset + TIMEZ_OMID) : TIMEZ_INVALID;
}


bool timez_valid(const timez_t t) {
    return (t & TIMEZ_OMASK) != 0;
}


long long timez_count(const timez_t t) {
    return (t & TIMEZ_OMASK) ? t >> TIMEZ_OBITS : TIMEZ_INVALID_COUNT;
}


int timez_offset(const timez_t t) {
    int offset = (int)(t & TIMEZ_OMASK);
    return offset ? offset - TIMEZ_OMID : TIMEZ_INVALID_OFFSET;
}




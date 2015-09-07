#include <stdio.h>
#include <stdlib.h>
#include "timez.h"



int main(void)
{

    struct timespec tp1, tp2;
    long long cnt1, cnt2;
    int off1, off2;
    bool res1, res2;
    timez_t t1, t2;

    tp1.tv_sec = tp1.tv_nsec = 0;
    cnt1 = timez_tp2count(&tp1);
    res1 = timez_count2tp(&tp2, cnt1);
    cnt2 = timez_tp2count(&tp2);
    if (!res1 || tp1.tv_sec != tp2.tv_sec || tp1.tv_nsec != tp2.tv_nsec || cnt1 != cnt2) {
        printf("Test 1: Error in timez_tp2count() or timez_count2tp()\n");
        return 1;
    }
    printf("Test 1: OK\n");

    tp1.tv_sec = 0x7FFFFFFF;
    cnt1 = timez_tp2count(&tp1);
    res1 = timez_count2tp(&tp2, cnt1);
    cnt2 = timez_tp2count(&tp2);
    if (!res1 || tp1.tv_sec != tp2.tv_sec || tp1.tv_nsec != tp2.tv_nsec || cnt1 != cnt2) {
        printf("Test 2: Error in timez_tp2count() or timez_count2tp()\n");
        return 1;
    }
    printf("Test 2: OK\n");

    tp1.tv_sec = -1 << 31;
    cnt1 = timez_tp2count(&tp1);
    res1 = timez_count2tp(&tp2, cnt1);
    cnt2 = timez_tp2count(&tp2);
    if (!res1 || tp1.tv_sec != tp2.tv_sec || tp1.tv_nsec != tp2.tv_nsec || cnt1 != cnt2) {
        printf("Test 3: Error in timez_tp2count() or timez_count2tp()\n");
        return 1;
    }
    printf("Test 3: OK\n");

    res2 = clock_gettime(CLOCK_REALTIME, &tp1) == 0;
    tp1.tv_nsec = (tp1.tv_nsec / 1000) * 1000;
    cnt1 = timez_tp2count(&tp1);
    res1 = timez_count2tp(&tp2, cnt1);
    cnt2 = timez_tp2count(&tp2);
    if (!res2 || !res1 || tp1.tv_sec != tp2.tv_sec || tp1.tv_nsec != tp2.tv_nsec || cnt1 != cnt2) {
        printf("Test 4: Error in timez_tp2count() or timez_count2tp()\n");
        return 1;
    }
    printf("Test 4: OK\n");

    cnt1 = 0LL;
    off1 = 0;
    t1 = timez_new(cnt1, off1);
    cnt2 = timez_count(t1);
    off2 = timez_offset(t1);
    if (cnt1 != cnt2 || off1 != off2) {
        printf("Test 5: Error in timez_new(), timez_count() or timez_offset()\n");
        return 1;
    }
    printf("Test 5: OK\n");

    cnt1 = (1LL << (63 - TIMEZ_OFFSET_BITS)) - 1;
    t1 = timez_new(cnt1, off1);
    cnt2 = timez_count(t1);
    off2 = timez_offset(t1);
    if (cnt1 != cnt2 || off1 != off2) {
        printf("Test 6: Error in timez_new(), timez_count() or timez_offset()\n");
        return 1;
    }
    printf("Test 6: OK\n");

    cnt1 = -cnt1 - 1;
    t1 = timez_new(cnt1, off1);
    cnt2 = timez_count(t1);
    off2 = timez_offset(t1);
    if (cnt1 != cnt2 || off1 != off2) {
        printf("Test 7: Error in timez_new(), timez_count() or timez_offset()\n");
        return 1;
    }
    printf("Test 7: OK\n");

    cnt1 = (1LL << (63 - TIMEZ_OFFSET_BITS));
    t1 = timez_new(cnt1, off1);
    cnt2 = -cnt1 - 1;
    t2 = timez_new(cnt2, off1);
    if (t1 != TIMEZ_INVALID || t2 != TIMEZ_INVALID) {
        printf("Test 8: Error in timez_new()\n");
        return 1;
    }
    printf("Test 8: OK\n");

    cnt1 = 0;
    off1 = (1 << (TIMEZ_OFFSET_BITS - 1)) - 1;
    t1 = timez_new(cnt1, off1);
    cnt2 = timez_count(t1);
    off2 = timez_offset(t1);
    if (!timez_valid(t1) || cnt1 != cnt2 || off1 != off2) {
        printf("Test 9: Error in timez_new(), timez_count() or timez_offset()\n");
        return 1;
    }
    printf("Test 9: OK\n");

    off1 = (1 << (TIMEZ_OFFSET_BITS - 1));
    t1 = timez_new(cnt1, off1);
    if (timez_valid(t1)) {
        printf("Test 10: Error in timez_new(), timez_count() or timez_offset()\n");
        return 1;
    }
    printf("Test 10: OK\n");

    cnt2 = timez_count(TIMEZ_INVALID);
    if (cnt2 != TIMEZ_INVALID_COUNT) {
        printf("Test 11: Error in timez_count()\n");
        return 1;
    }
    printf("Test 11: OK\n");

    off2 = timez_offset(TIMEZ_INVALID);
    if (off2 != TIMEZ_INVALID_OFFSET) {
        printf("Test 12: Error in timez_offset()\n");
        return 1;
    }
    printf("Test 12: OK\n");

    cnt2 = timez_count(1LL << TIMEZ_OFFSET_BITS);
    if (cnt2 != TIMEZ_INVALID_COUNT) {
        printf("Test 13: Error in timez_count()\n");
        return 1;
    }
    printf("Test 13: OK\n");

    off2 = timez_offset(1LL << TIMEZ_OFFSET_BITS);
    if (off2 != TIMEZ_INVALID_OFFSET) {
        printf("Test 14: Error in timez_offset()\n");
        return 1;
    }
    printf("Test 14: OK\n");

    cnt2 = timez_count(-1LL << TIMEZ_OFFSET_BITS);
    if (cnt2 != TIMEZ_INVALID_COUNT) {
        printf("Test 15: Error in timez_count()\n");
        return 1;
    }
    printf("Test 15: OK\n");

    off2 = timez_offset(-1LL << TIMEZ_OFFSET_BITS);
    if (off2 != TIMEZ_INVALID_OFFSET) {
        printf("Test 16: Error in timez_offset()\n");
        return 1;
    }
    printf("Test 16: OK\n");

    t1 = 1 << TIMEZ_OFFSET_BITS;
    if (timez_valid(t1)) {
        printf("Test 17: Error in timez_valid()\n");
        return 1;
    }
    printf("Test 17: OK\n");

    t1 = 1;
    if (!timez_valid(t1)) {
        printf("Test 18: Error in timez_valid()\n");
        return 1;
    }
    printf("Test 18: OK\n");

    res2 = clock_gettime(CLOCK_REALTIME, &tp1) == 0;
    t1 = timez_new(timez_tp2count(&tp1), 0);
    t2 = timez_now();
    res1 = timez_count2tp(&tp2, timez_count(t2));
    if (!res1 || !res2 || !timez_valid(t1) || !timez_valid(t2) || tp1.tv_sec != tp2.tv_sec) {
        printf("Test 19: Error in timez_valid()\n");
        // may fail as false negative, but probability is very low
        return 1;
    }
    printf("Test 19: OK\n");

    // Display tp1 as local time
    size_t l;
    char buf[256];
    struct tm tm;
    localtime_r(&tp1.tv_sec, &tm);
    l = strftime(buf, sizeof buf, "%Y-%m-%dT%H:%M:%S", &tm);
    sprintf(buf + l, ".%09ld", tp1.tv_nsec);
    printf("Current time from clock_gettime(): %s\n", buf);

    localtime_r(&tp2.tv_sec, &tm);
    l = strftime(buf, sizeof buf, "%Y-%m-%dT%H:%M:%S", &tm);
    sprintf(buf + l, ".%06ld", tp2.tv_nsec / 1000);
    printf("Current time from timez_t        : %s\n", buf);

    puts("Compute time difference between consecutive calls to clock_gettime()");
    long long dt = timez_count(t2) - timez_count(t1);
    long long h = dt / 3600000000LL;
    long long m = (llabs(dt) / 60000000LL) % 60;
    long long s = (llabs(dt) / 1000000LL) % 60;
    long long us = llabs(dt) % 1000000;
    printf("Time diff: %lld:%lld:%lld.%06lld\n", h, m, s, us);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include "timez.h"



int main(void)
{
    timez_t t1 = timez_now();
    printf("0x%016llX \n", t1);

    short tz1;
    struct timespec tp1;
    if (timez_get(&tp1, &tz1, t1) < 0) {
        puts("Invalid timez");
    }

    printf ("tz: %d:%02d\n", tz1 / 60, abs(tz1) % 60);

    timez_t t2 = timez_now();
    printf("0x%016llX \n", t2);

    short tz2;
    struct timespec tp2;
    if (timez_get(&tp2, &tz2, t2) < 0) {
        puts("Invalid timez");
    }

    struct tm *tmd1 = localtime(&tp1.tv_sec);
    struct tm *tmd2 = localtime(&tp2.tv_sec);

    char buf1[256];
    size_t l1 = strftime(buf1, sizeof buf1, "%Y-%m-%dT%H:%M:%S", tmd1);
    sprintf(buf1+l1,".%06ld", tp1.tv_nsec/1000);
    puts(buf1);

    char buf2[256];
    size_t l2 = strftime(buf2, sizeof buf2, "%Y-%m-%dT%H:%M:%S", tmd2);
    sprintf(buf2+l2,".%06ld", tp2.tv_nsec/1000);
    puts(buf2);

    struct timespec tp3;
    clock_gettime(CLOCK_REALTIME, &tp3);
    struct tm *tmd3 = localtime(&tp3.tv_sec);
    char buf3[256];
    size_t l3 = strftime(buf3, sizeof buf3, "%Y-%m-%dT%H:%M:%S", tmd3);
    sprintf(buf3+l3,".%09ld", tp3.tv_nsec);
    puts(buf3);

    long long dt = timez_diff(t2, t1);
    long long h = dt / 3600000000LL;
    long long m = (llabs(dt) / 60000000LL) % 60;
    long long s = (llabs(dt) / 1000000LL) % 60;
    long long us = llabs(dt) % 1000000;
    printf("Time diff: %lld:%lld:%lld.%06lld\n", h, m, s, us);

    return 0;
}


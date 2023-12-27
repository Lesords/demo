#include <stdio.h>
#include <time.h>
#include <sys/time.h> // gettimeofday

static long long getTimestampUs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * (long long)(1e+6) + tv.tv_usec);
}

int main() {
    clock_t start, end;
    start = clock();

    // Operative part of the program

    end = clock();
    printf("runtime: %f\n", (double) (end - start) / CLOCKS_PER_SEC);
    return 0;
}

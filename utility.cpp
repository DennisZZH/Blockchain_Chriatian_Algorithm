#include <cmath>
#include <cstdlib>
#include "utility.h"
#include "parameters.h"


void divide_time(timespec &t, uint32_t div, timespec& result) {
    double sec = (double)t.tv_sec / div;
    uint64_t nano = ((sec - floorl(sec)) * SEC_IN_NANOSEC) + t.tv_nsec / div;
    result.tv_sec = (int64_t)sec + nano / SEC_IN_NANOSEC;
    result.tv_nsec = nano % SEC_IN_NANOSEC;
}

void scale_time(timespec &t, double scale, timespec& result) {
    double sec = t.tv_sec * scale;
    double nano = t.tv_nsec * scale;
    result.tv_sec = (uint64_t) (sec + (uint64_t)nano/SEC_IN_NANOSEC);
    result.tv_nsec = (uint64_t)nano % SEC_IN_NANOSEC;
}

/**
 * @brief compare two timestamps
 * 
 * @param t0 
 * @param t1 
 * @return int 0 means t0 == t1, 1 means t0 > t1, -1 means t0 < t1
 */
int compare_time(timespec &t0, timespec &t1) {
    if (t0.tv_nsec == t1.tv_nsec && t0.tv_sec == t1.tv_sec)
        return 0;
    if (t1.tv_sec > t0.tv_sec || t1.tv_sec == t0.tv_sec && t1.tv_nsec > t0.tv_nsec)
        return -1;
    return 1;
}

void get_dt(timespec &t0, timespec &t1, timespec& diff) {
    int64_t ds = t1.tv_sec - t0.tv_sec;
    int64_t dn = t1.tv_nsec - t0.tv_nsec;
    if (ds > 0 || ds == 0 && dn > 0) {
        ds += (dn < 0) ? -1 : 0;
        dn = (dn + (dn < 0 ? SEC_IN_NANOSEC : 0)) % SEC_IN_NANOSEC;
        diff.tv_nsec = dn;
        diff.tv_sec = ds;
    } else {
        get_dt(t1, t0, diff);
        diff.tv_sec = -diff.tv_sec;
        diff.tv_nsec = -diff.tv_nsec;
    }
}

/**
 * @brief Get the calculate the time difference in nano seconds.
 * 
 * @param t0 The previous timestamp.
 * @param t1 The lastest timestamp.
 * @return uint64_t The time difference in nano seconds.
 */
int64_t get_dt_nanosec(timespec &t0, timespec &t1) {
    int64_t ds, dn;
    ds = t1.tv_sec - t0.tv_sec;
    dn = t1.tv_nsec - t0.tv_nsec;
    return ds * SEC_IN_NANOSEC + dn;
}

int64_t get_dt_sec(timespec &t0, timespec &t1) {
    int64_t ds, dn;
    ds = t1.tv_sec - t0.tv_sec;
    dn = t1.tv_nsec - t0.tv_nsec;
    return ds + dn / SEC_IN_NANOSEC;
}

/**
 * @brief Generate a random 32 bit integer within [1, 2, .... range]
 * 
 * @param range the random number generated.
 * @return uint32_t 
 */
uint32_t random_uint32(uint32_t range) {
    return ceil((double)rand()/RAND_MAX * range);
}

/**
 * @brief Increse the time base on t and the delta t and assign the new value to t.
 * 
 * @param t    The original time.
 * @param dt The time increment.
 */
void increase_time(timespec  &t, timespec &dt) {
    int64_t ns = t.tv_nsec + dt.tv_nsec;
    int64_t s = t.tv_sec + ns / SEC_IN_NANOSEC;
    t.tv_sec = s;
    t.tv_nsec = ns % SEC_IN_NANOSEC; 
}
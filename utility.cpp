#include <cmath>
#include "utility.h"
#include "parameters.h"

/**
 * @brief Get the calculate the time difference in nano seconds.
 * 
 * @param t0 The previous timestamp.
 * @param t1 The lastest timestamp.
 * @return uint64_t The time difference in nano seconds.
 */
uint64_t get_dt_nanosec(timespec &t0, timespec &t1) {
    int64_t ds, dn;
    ds = t1.tv_sec - t0.tv_sec;
    dn = t1.tv_nsec - t0.tv_nsec;
    return ds * SEC_IN_NANOSEC + dn;
}

/**
 * @brief Increse the time base on t0 and the delta t and assign the new value to t0.
 * 
 * @param t0    The original time.
 * @param dt_ns The time increment in nanoseconds.
 */
void increase_time(timespec  &t0, uint64_t dt_ns) {
    uint64_t ns = t0.tv_nsec + dt_ns % SEC_IN_NANOSEC ;
    t0.tv_sec += dt_ns / SEC_IN_NANOSEC + ns / SEC_IN_NANOSEC;
    t0.tv_nsec = ns % SEC_IN_NANOSEC; 
}
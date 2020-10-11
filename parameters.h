#pragma once


#define SEC_IN_NANOSEC      1000000000

/**
 * @brief TIMESTEP_NANOSEC means the simulated counter will be updated every 100ms system time.
 * This value shouldn't be too small (for example 1000ns) because based on experience the thread context
 * switching time is around that magnitude.
 */
#define TIMESTEP_NANOSEC    100000000

/**
 * @brief TIME_DIFF_TOLERANCE means the maximum tolerable time difference between different client.
 * 
 */
#define TIME_DIFF_TOLERANCE 200000000

#define TIME_DRIFT_FACTOR   0.2

/**
 * @brief The upper bound of the communication delay in seconds.
 * 
 */
#define COMM_DELAY_MAX      5
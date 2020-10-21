#pragma once



#define SEC_IN_NANOSEC      1000000000

/**
 * @brief TIMESTEP_NANOSEC means the simulated counter will be updated every 100ms system time.
 * This value shouldn't be too small (for example 1000ns) because based on experience the thread context
 * switching time is around that magnitude.
 */
#define TIMESTEP_NANOSEC    100000000

/**
 * @brief TIME_DIFF_TOLERANCE means the maximum tolerable time difference between different client in seconds.
 * 
 */
#define TIME_DIFF_TOLERANCE 10

#define TIME_DRIFT_FACTOR   0.25

/**
 * @brief The upper bound of the communication delay in seconds.
 * 
 */
#define COMM_DELAY_MAX      5

/**
 * @brief The type of client's request to server
 * Type 1 for request time
 * Type 2 for stop connection
 * 
 */
#define REQUEST_TIME_TYPE   1
#define REQUEST_STOP_TYPE   2


/**
 *  Communication related parameters
 */
#define SERVER_IP           "127.0.0.1"
#define CLIENT_IP           "127.0.0.1"
#define UDP_BASE_PORT       8020
#define SERVER_BASE_PORT    8000
#define SERVER_LISTEN_PORT  SERVER_BASE_PORT

/** @Insufficient balance error flag.
* Client throw this flag when user trying to send an amt greater than its balance
*/
#define INSUFFICIENT_BALANCE_ERROR  -1
#define ILLEGAL_SENDER_ERROR -2
#define ILLEGAL_RECVER_ERROR -3

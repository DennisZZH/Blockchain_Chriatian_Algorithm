#pragma once
#include <time.h>
#include <stdint.h>


uint64_t get_dt_nanosec(timespec &t0, timespec &t1);
void increase_time(timespec  &t0, uint64_t dt_ns);
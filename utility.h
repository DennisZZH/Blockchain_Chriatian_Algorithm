#pragma once
#include <time.h>
#include <stdint.h>

void divide_time(timespec &t, uint32_t div, timespec& result);
void scale_time(timespec &t, double scale, timespec& result);
int compare_time(timespec &t0, timespec &t1);
void get_dt(timespec &t0, timespec &t1, timespec& diff);
int64_t get_dt_sec(timespec &t0, timespec &t1);
int64_t get_dt_nanosec(timespec &t0, timespec &t1);
uint32_t random_uint32(uint32_t range);
// void increase_time(timespec  &t0, uint64_t dt_ns);
void increase_time(timespec &t0, timespec &dt);
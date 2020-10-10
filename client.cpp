#include <thread>
#include <chrono>
#include <time.h>
#include "parameters.h"
#include "client.h"
#include "utility.h"


int main(int argc, char* argv[]) {
    timespec t0, t1;
    clock_gettime(CLOCK_REALTIME, &t0);
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        clock_gettime(CLOCK_REALTIME, &t1);
        std::cout << "t0: " << t0.tv_sec << " " << t0.tv_nsec << "t1: " << t1.tv_sec << " " << t1.tv_nsec << std::endl;
        std::cout << "Increment: " << get_dt_nanosec(t0, t1) << std::endl;
        memcpy(&t0, &t1, sizeof(t1));
    }


    return 0;
}

client::client(int cid) {
    client_id = cid;
    
    // Initialize time
    simulated_time.set_nanos(0);
    simulated_time.set_seconds(0);
    simulate_time_thread = thread(&client::simulate_time, this);
}

client::~client() {
    stop_flag = true;
}

float client::get_balance(){
    return 0.0;
}
    
int client::balance_transaction() {
    return 0;
}
    
int client::transfer_transaction(int sid, int rid, float amt) {
    return 0;
}

// Private functions
void client::sync_server_time(timespec& time) {
    timespec t0, t1;
    clock_gettime(CLOCK_REALTIME, &t0);
    // TODO: Wait for random time.
    // TODO: Request from server
    clock_gettime(CLOCK_REALTIME, &t1);
    // TODO: Assign the new value based on christian's algorithm.
}

void client::simulate_time() {   // REVIEW: Need to verify this function.
    // Created this just to make the sim_time operations (like add, assign, etc) easier.
    timespec local_time = {0};
    timespec last_synctime;     // Expressed in systime because systime time is updated in everyloop, yet localtime is updated once for a while.
    timespec prev_systime;      // Used for recording last time the local time is updated, might caused by sync or simulation tick.
    timespec curr_systime;
    
    // Need to synchronize with the server first
    // because while the thread is running, the server time might not be zero.
    sync_server_time(local_time);
    clock_gettime(CLOCK_REALTIME, &curr_systime);
    memcpy(&last_synctime, &curr_systime, sizeof(curr_systime));
    memcpy(&prev_systime, &curr_systime, sizeof(curr_systime));
    

    while (!stop_flag) {
        clock_gettime(CLOCK_REALTIME, &curr_systime);
        // Check if the time difference has passed the update threshold for simulation time.
        if (get_dt_nanosec(prev_systime, curr_systime) > TIMESTEP_NANOSEC) {
            uint64_t dt_ns = get_dt_nanosec(prev_systime, curr_systime);
            increase_time(local_time, (uint64_t)(dt_ns * (1 + TIME_DRIFT_FACTOR)));
            memcpy(&prev_systime, &curr_systime, sizeof(curr_systime));
        }

        // Check if the time difference between clients pass the max tolerable drift.
        if (get_dt_nanosec(last_synctime, curr_systime) >= TIME_DIFF_TOLERANCE / (2 * TIME_DRIFT_FACTOR)) {
            sync_server_time(local_time);
            clock_gettime(CLOCK_REALTIME, &curr_systime);
            memcpy(&last_synctime, &curr_systime, sizeof(curr_systime));
            memcpy(&prev_systime, &curr_systime, sizeof(curr_systime));
        }
        
        // Here need to sleep for a while to save CPU resources. Yet it shouldn't sleep long.
        // Because if the sleeping time is too long, the duration between two simulation time updates will be inaccurate.
        // So here the sleeping time is the 1/100 of the duration between two simulation time updates.
        std::this_thread::sleep_for(std::chrono::nanoseconds(TIMESTEP_NANOSEC / 100));
    }
}
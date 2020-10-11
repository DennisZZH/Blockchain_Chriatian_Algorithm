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
    float balance = 0.f;
    std::list<transaction_t>::iterator it;
    for (it = blockchain.begin(); it != blockchain.end(); it++) {
        if (it->receiver_id() == client_id && it->sender_id() != client_id) {
            balance += it->amount();
        }
    }
    return balance;
}


int client::balance_transaction() {
    // Log the current request
    // wait for delta + tau
    // sort of the transactions in the buffer
    // Move all of the buffer to its local blockchain.
    // Traver the local blockchain to calculate the balance.
    timespec balance_timestamp = {0};
    get_simulated_time(balance_timestamp);
    std::this_thread::sleep_for(std::chrono::seconds(COMM_DELAY_MAX));

    // Sort the message buffer based on the following comparator function.
    auto comparator = [](message_t &m1, message_t &m2) {
        if (m1.timestamp().seconds() == m2.timestamp().seconds())
            return m1.timestamp().nanos() < m2.timestamp().nanos();
        else
            return m1.timestamp().seconds() < m2.timestamp().seconds();
    };
    std::sort(message_buffer.begin(), message_buffer.begin() + message_buffer.size(), comparator);

    // Iterate through the buffer to move all of the transactions has timestamp lower than logged stamp into the transaction.
    uint32_t msg_index = 0;
    auto is_msg_earlier = [](message_t &msg, timespec& t) {
        uint64_t msg_sec = msg.timestamp().seconds();
        uint32_t msg_nano = msg.timestamp().nanos();
        return (msg_sec < t.tv_sec || msg_sec == t.tv_nsec && msg_nano == t.tv_nsec);
    };
    while(msg_index < message_buffer.size()) {
        message_t& msg = message_buffer.at(msg_index);
        if (!is_msg_earlier(msg, balance_timestamp))
            break;
        // Here fetch the transaction info from the buffer and move it to the blockchain list.
        blockchain.push_back(msg.transaction());
        msg_index ++; 
    }
    // Need to pop out the message. (Currently, the msg_index is pointing to the first message later than the balance_timestamp).
    message_buffer.erase(message_buffer.begin(), message_buffer.begin() + msg_index);
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

void client::get_simulated_time(timespec& result) {
    simulated_time_mutex.lock();
    result.tv_sec = simulated_time.seconds();
    result.tv_nsec = simulated_time.nanos();
    simulated_time_mutex.unlock();
}

void client::set_simulated_time(timespec& t) {
    simulated_time_mutex.lock();
    simulated_time.set_seconds(t.tv_sec);
    simulated_time.set_nanos(t.tv_nsec);
    simulated_time_mutex.unlock();
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
            set_simulated_time(local_time);
            memcpy(&prev_systime, &curr_systime, sizeof(curr_systime));
        }

        // Check if the time difference between clients pass the max tolerable drift.
        if (get_dt_nanosec(last_synctime, curr_systime) >= TIME_DIFF_TOLERANCE / (2 * TIME_DRIFT_FACTOR)) {
            sync_server_time(local_time);
            clock_gettime(CLOCK_REALTIME, &curr_systime);
            set_simulated_time(local_time);
            memcpy(&last_synctime, &curr_systime, sizeof(curr_systime));
            memcpy(&prev_systime, &curr_systime, sizeof(curr_systime));
        }
        
        // Here need to sleep for a while to save CPU resources. Yet it shouldn't sleep long.
        // Because if the sleeping time is too long, the duration between two simulation time updates will be inaccurate.
        // So here the sleeping time is the 1/100 of the duration between two simulation time updates.
        // std::this_thread::sleep_for(std::chrono::nanoseconds(TIMESTEP_NANOSEC / 100));
        std::this_thread::yield();
    }
}
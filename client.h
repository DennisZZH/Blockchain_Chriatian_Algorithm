#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <deque>

#include <time.h>
#include <thread>
#include "Msg.pb.h"

using namespace std;

// struct trans_t {
//     uint32_t sender_id;
//     uint32_t receiver_id;
//     float amount;
// };

class client{
public:
    client(int cid);
    ~client();
    float get_balance();
    int balance_transaction();
    int transfer_transaction(int sid, int rid, float amt);
    
private:
    std::mutex simulated_time_mutex;
    timestamp_t simulated_time;
    int client_id;
    int port_id;
    deque<message_t> message_buffer;
    list<transaction_t> blockchain;
    
    bool stop_flag = false;     // We need a flag to stop the loop in other threads.
    thread simulate_time_thread;

    // Private method
    void get_simulated_time(timespec& result);
    void set_simulated_time(timespec& time);  
    void sync_server_time(timespec& time);

    // Thread Tasks
    void simulate_time();
};

#endif
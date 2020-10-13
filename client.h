#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <deque>
#include <time.h>
#include <thread>
#include "Msg.pb.h"

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
    int client_id;                  // id number of this client
    int port_id_TCP;                // port number used by this client for TCP socket
    int port_id_UDP;                // port number used by this client for UDP socket
    int sockfd_TCP;                 // TCP socket connection to time server
    int sockfd_UDP;                 // UDP socket for peer clients communication

    std::deque<message_t> message_buffer;
    std::list<transaction_t> blockchain;
    
    bool stop_flag = false;         // We need a flag to stop the loop in other threads.
    std::thread simulate_time_thread;
    std::thread receive_msg_thread;      // A thread for continously receiving msg from peer clients

    // Private method
    void get_simulated_time(timespec& result);
    void set_simulated_time(timespec& time);  
    void sync_server_time(timespec& time);
    float calc_balance();

    void connect_to_server();       // function for establishing TCP connection to server
    void setup_peer_connection();   // function for seting up UDP connection with peer clients

    void tcp_send(int type);
    void udp_send(int cid, timespec& time, int recv_id, float amt);

    // Thread Tasks
    void simulate_time();           // Thread function for simulating time
    void receive_msg();             // Thread function for continously receiving msg from peer clients 
};

#endif
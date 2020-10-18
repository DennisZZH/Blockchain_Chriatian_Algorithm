#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <deque>
#include <time.h>
#include <thread>
#include "Msg.pb.h"

// message	message_t {
// 	required int32 client_id = 1;
// 	required timestamp_t timestamp = 2;
// 	required transaction_t transaction = 3;
// }
/**
 * struct {
 *  uint32 id;
 * timestamp_t *time = 0;
 * trans_t *trans =;
 * }
 * 
 */

typedef struct {
    uint32_t delay_seconds;
    timespec start_time;            // Note this should be the real world time because we are simulating the delay.
    message_t message;
} udp_send_t;

// [32] [timespec] [messge [ptr][ptr]] 

// [] [C][B][A] >>>>>> []
// [5] [1] [3] [2]
//  ^
// [A] [B] [C] 
//  [C]>>[B]>>[A] >>>>>>>>>>>>>>>>>> target

// current_time - start_time > delay_seconds:

class client{
public:
    client(int cid);
    ~client();
    float get_balance();
    int balance_transaction();
    int transfer_transaction(int sid, int rid, float amt);
    std::string serialize_transaction();    // A function that prints the block chain for debugging.
    int get_client_id() {return client_id;};
    void stop_client();                     // Terminate client 

private:
    std::mutex simulated_time_mutex;
    timestamp_t simulated_time;
    int client_id;                  // id number of this client
    int port_id_UDP;                // port number used by this client for UDP socket
    int sockfd_TCP;                 // TCP socket connection to time server
    int sockfd_UDP;                 // UDP socket for peer clients communication

    double drift_factor;             // drift factor to this local client.    

    std::deque<udp_send_t*> udp_send_queue;   // This queue is used to hold the dynamic allocated send tasks.
    std::deque<message_t> message_buffer;
    std::list<transaction_t> blockchain;
    
    bool stop_flag = false;              // We need a flag to stop the loop in other threads.
    std::thread simulate_time_thread;
    std::thread receive_msg_thread;      // A thread for continously receiving msg from peer clients
    std::thread transfer_msg_thread;     // A thread for continously checking udp_send_queue and send

    // Private method
    void sort_message_buffer();
    void move_message_blockchain(timespec &timestamp);
    void get_simulated_time(timespec& result);
    void set_simulated_time(timespec& time);  
    void sync_server_time(timespec& time);
    uint64_t calc_message_size();       // Maybe good to move to utility.
    uint64_t calc_timestamp_size();     // Maybe good to move to utility.

    void connect_to_server();       // function for establishing TCP connection to server
    void setup_peer_connection();   // function for seting up UDP connection with peer clients

    void broadcast(message_t& message);
    // void tcp_send(int type);
    // void udp_send(int cid, timespec& time, int recv_id, float amt);

    // Thread Tasks
    void simulate_time();           // Thread function for simulating time
    void receive_msg();             // Thread function for continously receiving msg from peer clients 
    void transfer_msg();            // Thread function for sending the udp requests in the queue.
};

#endif
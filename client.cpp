#include "client.h"
#include "utility.h"
#include "parameters.h"
#include "Msg.pb.h"

#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h> 
#include <errno.h>
#include <sys/time.h>
#include <thread>

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
    port_id_TCP = 8010 + cid;
    port_id_UDP = 8020 + cid;

    // Establish TCP connection to the Time Server
    connect_to_server();

    // Setup UDP connection with peer clients
    setup_peer_connection();

    // Spawn a Thread for continously receiving from peer clients
    receive_msg_thread = std::thread(&client::receive_msg, this);

    // Spawn a Thread for simulating time
    // Initialize time
    simulated_time.set_nanos(0);
    simulated_time.set_seconds(0);
    simulate_time_thread = std::thread(&client::simulate_time, this); 
}

client::~client() {
    stop_flag = true;

    // Join threads
    receive_msg_thread.join();
    simulate_time_thread.join();
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
    // Log the current request, and broadcast it
    // wait for delta + tau
    // sort of the transactions in the buffer
    // Move all of the buffer to its local blockchain.
    // Traver the local blockchain to calculate the balance.
    timespec balance_timestamp = {0};
    get_simulated_time(balance_timestamp);

    // Broadcast this balance transaction message to all peer clients   
    // broadcast_msg(BALANCE_TRANSACTION_TYPE, balance_timestamp);

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

    // Send request to server
    request_t r;
    std::string msg_str;
    r.set_type(1);
    r.SerializeToString(&msg_str);
    if(send(sockfd_TCP, msg_str.c_str(), sizeof(request_t), 0) < 0){
        std::cerr<<"Error: Failed to send out the request to time server!"<<std::endl;
        exit(0);
    }

    // Receive respons from server
    char buf[sizeof(timestamp_t)];
    int to_read = sizeof(timestamp_t), siz_read = 0;
    timestamp_t t;
    msg_str.clear();
    while(to_read != 0){
        siz_read = recv(sockfd_TCP, buf, sizeof(timestamp_t), 0);
        if(siz_read < 0){
            std::cerr<<"Error: Failed to recv the message from time server!"<<std::endl;
            exit(0);
        }
        to_read -= siz_read;
        msg_str.append(buf);
        bzero(buf, sizeof(buf));
    }
    t.ParseFromString(msg_str);

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

void client::connect_to_server() {
    // Function for establishing TCP connection to server
    struct sockaddr_in server_address;
    sockfd_TCP = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_TCP == -1) {
        printf("Socket creation failed.\n");
        exit(0);
    }
    const char* server_ip = "127.0.0.1";
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(port_id_TCP);

    if (connect(sockfd_TCP, (struct sockaddr*)&server_address, sizeof(server_address)) != 0) {
        printf("Error number: %d\n", errno);
        printf("The error message is %s\n", strerror(errno));
        printf("Connection to the server failed.\n");
        exit(0);
    }

    std::cout << "TCP Socket created.\n";
}

void client::setup_peer_connection() {
    // Function for seting up UDP connection with peer clients
    //std::cout << "The port of the current process is " << port + pid << "\n";
    if ((sockfd_UDP = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cerr << "Socket creation failed!\n";
        exit(0);
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    const char* server_ip = "127.0.0.1";
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port_id_UDP);
    servaddr.sin_addr.s_addr = inet_addr(server_ip);

    // Bind the socket
    if (bind(sockfd_UDP, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        std::cerr << "Socket bind failed!\n";
        exit(0); 
    }

    std::cout << "UDP Socket created.\n";
 }

void client::receive_msg() {
    int read_size = 0;
    char buf[sizeof(message_t)];
    std::string str_message;
    message_t m;
    struct sockaddr_in recvaddr;
    memset(&recvaddr, 0, sizeof(recvaddr));
    while (true)
    {
        m.Clear();
        bzero(buf, sizeof(buf));
        bzero(&str_message, sizeof(str_message));
        int len = sizeof(recvaddr);
        read_size = recvfrom(sockfd_UDP, buf, sizeof(buf), MSG_WAITALL, (struct sockaddr *)&recvaddr, (socklen_t *)&len);
        if (read_size < 0)
        {
            std::cerr << "Error: Failed to receive message!"
                      << "\n";
            exit(0);
        }
        str_message.append(buf);

        m.ParseFromString(str_message);
        // std::cout << "From receiving: " << m.DebugString();

        // Push to messages with lock/unlock
        // TODO：lock
        message_buffer.push_back(m);
        // TODO：unlock
    }
}

void tcp_send(int type) {

}

void udp_send(int cid, timespec& time, int recv_id, float amt) {
    
}


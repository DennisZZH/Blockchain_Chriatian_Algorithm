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

const char* usage = "Run the program by typing ./client <cid> where cid is within range [0, 2].";
inline void print_usage() {
    printf("%s\n", usage);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        print_usage();
        exit(1);
    }
    
    int cid = atoi(argv[1]);
    if (cid < 0 || cid > 2) {
        std::cout << "Your input cid is out of the accepted range." << std::endl;
        print_usage();
        exit(1);
    }

    client c(cid);
    

    // Test Code
    timespec t0, t1, diff, div;
    clock_gettime(CLOCK_REALTIME, &t0);
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        clock_gettime(CLOCK_REALTIME, &t1);
        get_dt(t0, t1, diff);
        // std::cout << "t0: " << t0.tv_sec << " " << t0.tv_nsec << "t1: " << t1.tv_sec << " " << t1.tv_nsec << std::endl;
        std::cout << "Old Nano: " << t0.tv_nsec << std::endl;
        std::cout << "New Nano: " << t1.tv_nsec << std::endl;
        std::cout << "Increment: " << diff.tv_sec << "s " << diff.tv_nsec/1000000 << "ms " << std::endl;
        divide_time(diff, 2, div);
        std::cout << "Div: " << div.tv_sec << "s " << div.tv_nsec / 1000000 << "ms " << std::endl;
        get_dt(t1, t0, diff);
        std::cout << "Increment: " << diff.tv_sec << "s " << diff.tv_nsec/1000000 << "ms " << std::endl;
        std::cout << std::endl;
        // memcpy(&t0, &t1, sizeof(t1));
    }
    return 0;
}

void client::broadcast(message_t& message) {
    for (int cid = 0; cid < 3; cid++) {
        if (cid == this->client_id)
            continue;
        sockaddr_in client_addr = {0};
        client_addr.sin_family = AF_INET;
        client_addr.sin_addr.s_addr = inet_addr(CLIENT_IP);
        client_addr.sin_port = htons(UDP_BASE_PORT + cid);
        size_t bytes_count = sendto(sockfd_UDP, &message, sizeof(message), 0, (sockaddr*)&client_addr, sizeof(client_addr));
        if (bytes_count < sizeof(message)) {
            printf("Send message to process id: %d failed. Send %ld out of %ld bytes", cid, bytes_count, sizeof(message));
        }
    }
}

client::client(int cid) {
    client_id = cid;
    port_id_TCP = TCP_BASE_PORT + cid;
    port_id_UDP = UDP_BASE_PORT + cid;

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
    while(msg_index) {
        //message_buffer.erase(message_buffer.begin(), message_buffer.begin() + msg_index);
        message_buffer.pop_front();
        msg_index --;
    }
    return 0;
}
    
int client::transfer_transaction(int sid, int rid, float amt) {
    // a
    // b
    // udp_send_t* task = new 
    // task->start_time = get_clocktime();
    // task->delay_seconds = ceil(rand() * 5);
    return 0;
}

// Private functions
void client::sync_server_time(timespec& time) {
    timespec t0, t1;
    clock_gettime(CLOCK_REALTIME, &t0);
    // Wait for random time to simulate the communication delay.
    std::this_thread::sleep_for(std::chrono::seconds(random_uint32(COMM_DELAY_MAX)));

    // Send request to server
    request_t request;
    std::string msg_str;
    request.set_type(REQUEST_TIME_TYPE);
    request.SerializeToString(&msg_str);
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
    
    // REVIEW: Assign the new value based on christian's algorithm.
    timespec sync_timestamp = {0}, local_timestamp = {0};
    // Calculate half trip time
    timespec delta_time = {0};
    get_dt(t0, t1, delta_time);
    divide_time(delta_time, 2, delta_time);

    // Christian Algorithm
    sync_timestamp.tv_sec = t.seconds();
    sync_timestamp.tv_nsec = t.nanos();
    increase_time(sync_timestamp, delta_time);


    // Implement slow down speed up algorithm.
    get_simulated_time(local_timestamp);
    if (compare_time(local_timestamp, sync_timestamp) > 0) { // Local time is faster
        timespec diff = {0};
        get_dt(sync_timestamp, local_timestamp, diff);
        std::this_thread::sleep_for(std::chrono::nanoseconds(diff.tv_nsec));
        std::this_thread::sleep_for(std::chrono::seconds(diff.tv_sec));
    }
    set_simulated_time(sync_timestamp);
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
            timespec dt = {0};
            // uint64_t dt_ns = get_dt_nanosec(prev_systime, curr_systime);
            get_dt(prev_systime, curr_systime, dt);
            scale_time(dt, (1 + TIME_DRIFT_FACTOR), dt);
            increase_time(local_time, dt);
            set_simulated_time(local_time);
            memcpy(&prev_systime, &curr_systime, sizeof(curr_systime));
        }

        // Check if the time difference between clients pass the max tolerable drift.
        if (get_dt_sec(last_synctime, curr_systime) >= TIME_DIFF_TOLERANCE / (2 * TIME_DRIFT_FACTOR)) {
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

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
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
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port_id_UDP);
    servaddr.sin_addr.s_addr = inet_addr(CLIENT_IP);

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

void client::transfer_msg() {
    // Note: This function only transfers the udp message.
    while (!stop_flag) {
        if (udp_send_queue.size() == 0)
            continue;
        udp_send_t* send_task = udp_send_queue[0];
        timespec curr_time;
        clock_gettime(CLOCK_REALTIME, &curr_time);
        uint64_t diff_in_sec = get_dt_sec(send_task->start_time, curr_time);
        
        // If the passed time is smaller than the delay time, then we should wait.
        if(diff_in_sec < send_task->delay_seconds) {
            std::this_thread::sleep_for(std::chrono::seconds(diff_in_sec));
            continue;
        }
        
        // make message
        broadcast(send_task->message);

        // After the current message is sent successfully, pop the front.
        udp_send_queue.pop_front();
        delete send_task;
    }
    
    // Free of the dynamic memory before quit.
    while (udp_send_queue.size() > 0) {
        udp_send_t* send_task = udp_send_queue[0];
        udp_send_queue.pop_front();
        delete send_task;
    }
}




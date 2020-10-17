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
#include <sstream>


/**
 * @brief User input format:
 * - Transfer Transaction: t / transfer <receiver id> <amount>
 * - Balance Transaction: b / balance
 * - Stop Running: s / stop
 */

#define CMD_TRANS_ARGS_NUM  2
#define CMD_BALANCE_ARGS_NUM 0

typedef enum {
    BLOCK 
} input_option_t;

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

    bool running = true;
    std::string input;
    while (running) {
        std::cout << "input: " << std::endl;
        // Parse user input
        input.clear();
        std::getline(std::cin, input);
        std::stringstream ss(input);
        std::vector<std::string> args;
        while (ss.good()) {
            std::string arg = "";
            ss >> arg;
            args.push_back(arg);
        }

        std::string &cmd = args[0];
        if (cmd.compare("t") == 0 || cmd.compare("transfer") == 0) 
        {
            if (args.size() != CMD_TRANS_ARGS_NUM + 1) {
                std::cout << "Command format is not correct." << std::endl;
                continue;
            }
            int recv_id = atoi(args[1].c_str());
            float amount = (float)atof(args[2].c_str());

            // Call the transfer transaction method.
            int status = c.transfer_transaction(c.get_client_id(), recv_id, amount);
            switch (status) {
                case INSUFFICIENT_BALANCE_ERROR:
                    std::cout << "Insufficient balance!" << std::endl;
                    break;
                case ILLEGAL_SENDER_ERROR:
                    std::cout << "Illegal sender!" << std::endl;
                    break;
                default:
                    std::cout << "Transfer successfully." << std::endl; 
            }
        }
        else if (cmd.compare("b") == 0 || cmd.compare("balance") == 0)
        {
            // Call the balance transaction method.
            c.balance_transaction();
            float balance = c.get_balance();
            std::cout<<"Current balance = "<< balance <<std::endl;
        }
        else if (cmd.compare("s") == 0 || cmd.compare("stop") == 0)
        {
            running = false;
            // Set the stop_flag in the class to be true.
            c.stop_client();
        } 
        else 
        {
            std::cout << "Unknown command type. Supported commands: transfer(t), balance(b), stop(s)" << std::endl;
        }

    }


    // Test Code
    // timespec t0, t1, diff, div;
    // clock_gettime(CLOCK_REALTIME, &t0);
    // while(true) {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //     clock_gettime(CLOCK_REALTIME, &t1);
    //     get_dt(t0, t1, diff);
    //     // std::cout << "t0: " << t0.tv_sec << " " << t0.tv_nsec << "t1: " << t1.tv_sec << " " << t1.tv_nsec << std::endl;
    //     std::cout << "Old Nano: " << t0.tv_nsec << std::endl;
    //     std::cout << "New Nano: " << t1.tv_nsec << std::endl;
    //     std::cout << "Increment: " << diff.tv_sec << "s " << diff.tv_nsec/1000000 << "ms " << std::endl;
    //     divide_time(diff, 2, div);
    //     std::cout << "Div: " << div.tv_sec << "s " << div.tv_nsec / 1000000 << "ms " << std::endl;
    //     get_dt(t1, t0, diff);
    //     std::cout << "Increment: " << diff.tv_sec << "s " << diff.tv_nsec/1000000 << "ms " << std::endl;
    //     std::cout << std::endl;
    //     // memcpy(&t0, &t1, sizeof(t1));
    // }
    // return 0;
}

void client::stop_client() {
    // Send stop requrst to server
    request_t request;
    std::string msg_str;
    request.set_type(REQUEST_STOP_TYPE);
    request.SerializeToString(&msg_str);
    if(send(sockfd_TCP, msg_str.c_str(), sizeof(request_t), 0) < 0){
        std::cerr<<"Error: Failed to send out the request to time server!"<<std::endl;
        exit(0);
    }
    // Terminate client threads
    stop_flag = true;
}

client::client(int cid) {
    client_id = cid;
    port_id_UDP = UDP_BASE_PORT + cid;

    // Establish TCP connection to the Time Server
    connect_to_server();

    // Setup UDP connection with peer clients
    setup_peer_connection();

    transaction_t trans;
    trans.set_amount(10);
    trans.set_receiver_id(cid);
    trans.set_sender_id(-1);
    blockchain.push_back(trans);

    // Spawn a Thread for continously receiving from peer clients
    receive_msg_thread = std::thread(&client::receive_msg, this);
    std::cout<<"receive_msg_thread created!"<<std::endl;

    // Spawn a Thread for continously checking udp_send_queue and send
    transfer_msg_thread = std::thread(&client::transfer_msg, this);
    std::cout<<"transfer_msg_thread created!"<<std::endl;

    // Spawn a Thread for simulating time
    // Initialize time
    simulated_time.set_nanos(0);
    simulated_time.set_seconds(0);
    simulate_time_thread = std::thread(&client::simulate_time, this);
    std::cout<<"simulate_time_thread created!"<<std::endl;
}

client::~client() {
    // Join threads
    receive_msg_thread.join();
    simulate_time_thread.join();
    transfer_msg_thread.join();

    // Close socket
    close(sockfd_TCP);
    close(sockfd_UDP);
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
    // If this function returns true, it means m1 < m2.
    auto comparator = [](message_t &m1, message_t &m2) {
        // Deal with the case where timestamps are exactly same first. Use the pid to break the tie.
        if (m1.timestamp().seconds() == m2.timestamp().seconds() && m1.timestamp().nanos() == m2.timestamp().nanos()) {
            return m1.transaction().sender_id() < m2.transaction().sender_id();
        }
        
        // if the two messages's timestamps are not the same, then compare their time stamps.
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
    // Check current balance
    if (get_balance() < amt) return INSUFFICIENT_BALANCE_ERROR;
    // Check ensure client can only send its own money, ie. sid = client_id
    if (sid != client_id) return ILLEGAL_SENDER_ERROR;
    // Prepare send task
    udp_send_t* task = new udp_send_t();
    timespec start_time = {0};

    timestamp_t *timestamp = new timestamp_t();
    transaction_t *transaction = new transaction_t();

    get_simulated_time(start_time);
    timestamp->set_seconds(start_time.tv_sec);
    timestamp->set_nanos(start_time.tv_nsec);
    transaction->set_sender_id(sid);
    transaction->set_receiver_id(rid);
    transaction->set_amount(amt);
    
    // set timestamp
    task->start_time.tv_nsec = start_time.tv_nsec;
    task->start_time.tv_sec = start_time.tv_sec;
    // set delay
    task->delay_seconds = random_uint32(COMM_DELAY_MAX);
    // set message
    task->message.set_client_id(client_id);
    task->message.set_allocated_timestamp(timestamp);
    task->message.set_allocated_transaction(transaction);

    // Add message to send queue
    udp_send_queue.push_back(task);

    return 0;
}

std::string client::serialize_transaction() {
    uint32_t size = blockchain.size();
    std::stringstream ss("");
    std::list<transaction_t>::iterator it_trans = blockchain.begin();
    while (size) {
        ss << "================" << std::endl;
        ss << "Sender: " << it_trans->sender_id() << std::endl;
        ss << "Receiver: " << it_trans->receiver_id() << std::endl;
        ss << "Amount: " << it_trans->amount() << std::endl;
        it_trans ++;
        size--;
    }
    return ss.str();
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
    server_address.sin_port = htons(SERVER_BASE_PORT + client_id);

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
    while (!stop_flag)
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
        message_buffer.push_back(m);
        transaction_t trans = m.transaction();
        timestamp_t time = m.timestamp();
        printf("[Received] Sender: %d | Amount: %f | SenderTime: %lld.%d\n", trans.sender_id(), trans.amount(), time.seconds(), time.nanos());
    }
}

void client::transfer_msg() {
    // Note: This function only transfers the udp message.
    while (!stop_flag) {
        if (udp_send_queue.size() == 0)
            continue;
        udp_send_t* send_task = udp_send_queue[0];

        printf("Ptr Addr: %llu", (uint64_t)send_task);        
        std::cout << "Transfer message: " << send_task->message.transaction().amount() << std::endl;

        
        timespec curr_time;
        clock_gettime(CLOCK_REALTIME, &curr_time);
        uint64_t diff_in_sec = get_dt_sec(send_task->start_time, curr_time);
        
        // If the passed time is smaller than the delay time, then we should wait.
        if(diff_in_sec < send_task->delay_seconds) {
            std::this_thread::sleep_for(std::chrono::seconds(diff_in_sec));
            continue;
        }
        
        broadcast(send_task->message);
        delete send_task;

        // CAUTION: we might need to delete here, rather than after quit!
        udp_send_queue.pop_front();
        
    }
    
    // Free of the dynamic memory before quit.
    while (udp_send_queue.size() > 0) {
        udp_send_t* send_task = udp_send_queue[0];
        udp_send_queue.pop_front();
        delete send_task;
    }
}

void client::broadcast(message_t& message) {
    std::string msg_string = message.SerializeAsString();
    for (int cid = 0; cid < 3; cid++) {
        if (cid == this->client_id)
            continue;
        sockaddr_in client_addr = {0};
        client_addr.sin_family = AF_INET;
        client_addr.sin_addr.s_addr = inet_addr(CLIENT_IP);
        client_addr.sin_port = htons(UDP_BASE_PORT + cid);
        size_t bytes_count = sendto(sockfd_UDP, msg_string.c_str(), msg_string.size(), 0, (sockaddr*)&client_addr, sizeof(client_addr));
        if (bytes_count < sizeof(message)) {
            printf("Send message to process id: %d failed. Send %ld out of %ld bytes", cid, bytes_count, sizeof(message));
        }
    }
}

#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <pthread.h>
#include <list>
#include <thread>
#include "Msg.pb.h"

typedef struct {
    bool valid;
    int socket;
    std::thread* task; 
} connected_client_t;

struct argu_t{
    int cid;
    int sockfd;
};

class server {    
public:
    server();
    ~server();
    void start_server();
    void accept_clients();

    // Old methods
    int set_up_connection();
    int run_time_server();

private:
    const char* server_ip = "127.0.0.1";
    int sock;
    bool stop_flag = false;
    std::list<connected_client_t*> clients_list;
    timespec server_start_time;
    std::thread client_recycler_thread;

    // Old variables
    int server_port = 8000;
    int server_sockets[3];
    int client_sockets[3];
    pthread_t tids[2];

    // Methods
    void get_server_time(timespec &server_time);
    uint64_t calc_request_size();

    // threads
    void client_handler(connected_client_t* client_info);
    void client_recycler();

};

void* manage_clients(void* args);

#endif
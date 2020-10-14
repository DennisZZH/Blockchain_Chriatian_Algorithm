#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <pthread.h>
#include "Msg.pb.h"

struct argu_t{
    int cid;
    int sockfd;
};

class server {    
public:
    server();
    int set_up_connection();
    int run_time_server();

private:
    const char* server_ip = "127.0.0.1";
    int server_port = 8000;
    int server_sockets[3];
    int client_sockets[3];
    pthread_t tids[2];
};

void* manage_clients(void* args);

#endif
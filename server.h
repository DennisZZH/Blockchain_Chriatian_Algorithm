#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <iostream>
#include <time.h>
#include "Msg.pb.h"


class server {
public:
    server();
    int set_up_connection();
    int run_time_server();

private:
    char* server_ip;
    int server_port;
    int server_sockets[3];
    int client_sockets[3];
    pthread_t tids[2];
    void* manage_clients(void* args);
};

#endif
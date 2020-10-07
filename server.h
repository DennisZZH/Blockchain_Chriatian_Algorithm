#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <iostream>
#include <time.h>
#include "Msg.pb.h"

class server{
public:
    server();

private:
    char* server_ip = "127.0.0.1";
    int server_port = 8000;
};

#endif
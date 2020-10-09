#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <time.h>
#include "Msg.pb.h"

class client{
public:
    client(int cid);
    float get_balance();
    int balance_transaction();
    int transfer_transaction(int sid, int rid, float amt);

private:
    time_t simulated_time;
    int client_id;
    int port_id;
    vector<message_t> message_buffer;
    list<transaction_t> blockchain;
};

#endif
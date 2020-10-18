#include "server.h"
#include "Msg.pb.h"
#include "parameters.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h> 
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>

int main() {
    // Run server routine
    char input;

    // std::cout<<"Do you want to run server now? (Y/N)"<<std::endl;
    // std::cin>>input;

    // if (input == 'Y') {
        // server s;
    // }
    server s;
    s.accept_clients();

    std::cout<<"Server finished!"<<std::endl;

    return 0;
}

server::server() {
    // set_up_connection();
    // run_time_server();
    start_server();
}

server::~server() {
    stop_flag = true;
    std::list<connected_client_t*>::iterator curr_client_it;
    for (curr_client_it = clients_list.begin(); curr_client_it != clients_list.end(); curr_client_it++) {
        connected_client_t* client_info = *curr_client_it;
        client_info->task->join();
        delete client_info->task;
        delete client_info;
    }
}

void server::start_server() {
    // Reset server time
    clock_gettime(CLOCK_REALTIME, &server_start_time);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_BASE_PORT);
    // Bind server
    if (bind(sock, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "[start_server] Failed binding the server socket." << std::endl;
        exit(1);  
    }
    // Define maximum connect number
    if (listen(sock, 3) < 0) {
        std::cerr << "[start_server] Failed to listen the port." << std::endl;
        exit(1);
    }

    client_recycler_thread = std::thread(&server::client_recycler, this);
    std::cout << "[start_server] Done!" << std::endl;
}

void server::accept_clients() {
    while (!stop_flag) {
        int client_sock = accept(sock, NULL, NULL);
        if (client_sock < 0) {
            std::cout << "[accept_clients] Failed to accept client." << std::endl;
            continue;
        }
        
        // Create new thread to communicate with the new client
        connected_client_t* client_info = new connected_client_t();
        client_info->socket = client_sock;
        client_info->valid = true;
        client_info->task = new std::thread(&server::client_handler, this, client_info);

        clients_list.push_back(client_info);
        std::cout << "[accept_clients] Client connected!" << std::endl;
    }
}

void server::client_handler(connected_client_t* client_info) {
    int client_sock = client_info->socket;
    char buffer[calc_request_size()];
    // std::cout << "[client_handler] Buffer size: " << calc_request_size() << std::endl;
    while (true) {
        bzero(buffer, sizeof(buffer));
        int read_size = 0;
        int req_size = calc_request_size();

        if ((read_size = recv(client_sock, buffer, sizeof(buffer), 0)) <= 0) {
            std::cerr << "[client_handler] Read socket error. The socket is failed or closed. (read size: " << read_size << ")" << std::endl;
            break;
        }
        
        if (read_size != sizeof(buffer)) {
            std::cerr << "[client_handler] The request received is not valid. Waiting for another one." << std::endl;
            continue;
        }
        
        request_t req;
        req.ParseFromArray(buffer, sizeof(buffer));

        // type 1 for request, type 2 for quit
        if (req.type() == REQUEST_STOP_TYPE) {
            break;
        }
        
        if (req.type() == REQUEST_TIME_TYPE ) {
            // Send out the timestamp to client
            std::cout << "[client_handler] Received time request. Sending the server time back ... ";
                
            timespec curr_server_time = {0};
            get_server_time(curr_server_time);
            timestamp_t server_timestamp;
            server_timestamp.set_seconds(curr_server_time.tv_sec);
            server_timestamp.set_nanos(curr_server_time.tv_nsec);
            std::string message_string = server_timestamp.SerializeAsString();
                
            // Add random delay
            uint32_t delay = random_uint32(COMM_DELAY_MAX);
            std::this_thread::sleep_for(std::chrono::seconds(delay));

            int send_size = 0;
            if ((send_size = send(client_sock, message_string.c_str(), message_string.size(), 0)) < 0) {
                std::cerr << std::endl <<  "[client_handler] Failed to send to client." << std::endl;
                break;
            }
            std::cout << "Done!" << std::endl;
        }    
    }
    client_info->valid = false;
    std::cout << "[client_handler] client thread with fd: " << client_info->socket << " is exiting." << std::endl;
}

void server::client_recycler() {
    while (!stop_flag) {
        uint32_t count = clients_list.size();
        std::list<connected_client_t*>::iterator curr_client_it = clients_list.begin();
        std::list<connected_client_t*>::iterator delete_client_it;
        while (count--) {
            delete_client_it = curr_client_it;
            curr_client_it++;
            if ((*delete_client_it)->valid == false) {
                connected_client_t* client_info = *delete_client_it;
                client_info->task->join();
                close(client_info->socket);
                delete client_info->task;
                delete client_info;
                clients_list.erase(delete_client_it);
                std::cout << "[client_recycler] One client has been freed." << std::endl;
            }
        }
    }
}


void server::get_server_time(timespec &server_time) {
    timespec curr_time = {0};
    clock_gettime(CLOCK_REALTIME, &curr_time);
    get_dt(server_start_time, curr_time, server_time);
}

uint64_t server::calc_request_size() {
    request_t req;
    req.set_type(REQUEST_TIME_TYPE);
    return req.ByteSizeLong();
}

// int server::set_up_connection() {
//     struct sockaddr_in addresses[3];
//     int addrlen[3];

//     // Create server socket file descriptors for 3 clients
//     std::cout << "Creating the server sockets...";
//     for (int i = 0; i < 3; i++) {
//         if ((server_sockets[i] = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//             std::cerr << "Failed creating " << i + 1 << " server socket!\n";
//             exit(0);
//         }
//     }
//     std::cout << "Done!\n";

//     // Bind all 3 sockets
//     std::cout << "Binding the server sockets...";
//     for (int i = 0; i < 3; i++) {
//         addresses[i].sin_family = AF_INET;
//         addresses[i].sin_addr.s_addr = INADDR_ANY;
//         addresses[i].sin_port = htons(server_port + i);
//         if (bind(server_sockets[i], (struct sockaddr *)(addresses + i), sizeof(addresses[i])) < 0) {
//             std::cerr << "Bind failed on " << i + 1 << " socket!\n";
//             exit(0);
//         }
//     }
//     std::cout << "Done!\n";

//     // 3 sockets listening
//     std::cout << "Listening...";
//     for (int i = 0; i < 3; i++) {
//         if (listen(server_sockets[i], 3) < 0) {
//             std::cerr << "Failed on listening " << i + 1 << " socket.\n";
//         }
//     }
//     std::cout << "Done!\n";

//     // Connect with 3 client sockets
//     std::cout << "Connecting...";
//     for (int i = 0; i < 3; i++) {
//         addrlen[i] = sizeof(addresses[i]);
//         if ((client_sockets[i] = accept(server_sockets[i], (struct sockaddr *)(addresses + i), (socklen_t *)(addrlen + 1))) < 0) {
//             std::cerr << "Failed accepting process " << i + 1 << "\n";
//             printf("Error number: %d\n", errno);
//             printf("The error message is %s\n", strerror(errno));
//             printf("Local socket connection with the server failed.\n");
//             exit(errno);
//         }
//     }
//     std::cout << "Done!\n";

//     return 0;
// }

// void* manage_clients(void* args) {
//      // Manage clients' requests using this function
//     // args: 1. client id  2. sockfd: the listening socket for the corresponding process
//     argu_t* argu = (argu_t*) args;
//     int cid = argu->cid;
//     int cur_sockfd = argu->sockfd;
//     struct timeval timestamp;
//     timestamp_t timestamp_msg;

//     // A while loop receiving from the corresponding client
//     char buffer[sizeof(request_t)];
//     int read_size, sizeleft;
//     while (true) {
//         sizeleft = sizeof(request_t);
//         std::string strMessage;
//         while (sizeleft != 0) {
//             if ((read_size = recv(cur_sockfd, buffer, sizeof(buffer), 0)) < 0) {
//                 std::cerr << "Failed receving from process " << cid + 1 << "\n";
//                 exit(0);
//             }
//             strMessage.append(buffer);
//             sizeleft -= read_size;
//             bzero(buffer, sizeof(buffer));
//         }
//         request_t m;
//         m.ParseFromString(strMessage);

//         // type 1 for request, type 2 for quit
//         if (m.type() == REQUEST_STOP_TYPE) {
//             std::cout << "Client " << cid << " exits.\n";
//             break;
//         }

//         // Send out the timestamp to client
//         std::cout << "Waiting to send the message from server to client" << cid << "......"<<std::endl;
            
//         gettimeofday(&timestamp, NULL);
//         timestamp_msg.set_seconds(timestamp.tv_sec);
//         timestamp_msg.set_nanos(timestamp.tv_usec);
//         strMessage = timestamp_msg.SerializeAsString();
        
//         // Add random delay
//         uint32_t delay = random_uint32(COMM_DELAY_MAX);
//         sleep(delay);

//         int send_size = 0;
//         if ((send_size = send(cur_sockfd, strMessage.c_str(), sizeof(timestamp_t), 0)) < 0) {
//             std::cerr << "Failed\n";
//             exit(0);
//         }
//         std::cout << "Done!\n";
//     }

//     close(cur_sockfd);
//     return NULL;
// }

// int server::run_time_server() {
   
//     // Create two extra threads to handle messages from client 2 and 3
//     argu_t argus[3];
//     for (int i = 1; i < 3; i++) {
//         argus[i].cid = i + 1;
//         argus[i].sockfd = client_sockets[i];
//         pthread_create(tids + i - 1, NULL, manage_clients, (void*)(argus + i));
//     }

//     // Call function for main thread
//     argus[0].cid = 1;
//     argus[0].sockfd = client_sockets[0];
//     manage_clients((void*)(argus));

//     std::cout << "The time server to clients connection is up!\n";

//     // pthread_join for other two threads
//     for (int i = 0; i < 2; i++) {
//         pthread_join(tids[i], NULL);
//     }

//     std::cout << "The time server to clients connection is down!\n";

//     return 0;
// }

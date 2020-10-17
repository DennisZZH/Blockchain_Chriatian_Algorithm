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

    std::cout<<"Do you want to run server now? (Y/N)"<<std::endl;
    std::cin>>input;

    if (input == 'Y') {
        server s;
    }

    std::cout<<"Server finished!"<<std::endl;

    return 0;
}

server::server() {
    set_up_connection();
    run_time_server();
}

server::~server() {
}

int server::set_up_connection() {
    struct sockaddr_in addresses[3];
    int addrlen[3];

    // Create server socket file descriptors for 3 clients
    std::cout << "Creating the server sockets...";
    for (int i = 0; i < 3; i++) {
        if ((server_sockets[i] = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            std::cerr << "Failed creating " << i + 1 << " server socket!\n";
            exit(0);
        }
    }
    std::cout << "Done!\n";

    // Bind all 3 sockets
    std::cout << "Binding the server sockets...";
    for (int i = 0; i < 3; i++) {
        addresses[i].sin_family = AF_INET;
        addresses[i].sin_addr.s_addr = INADDR_ANY;
        addresses[i].sin_port = htons(server_port + i);
        if (bind(server_sockets[i], (struct sockaddr *)(addresses + i), sizeof(addresses[i])) < 0) {
            std::cerr << "Bind failed on " << i + 1 << " socket!\n";
            exit(0);
        }
    }
    std::cout << "Done!\n";

    // 3 sockets listening
    std::cout << "Listening...";
    for (int i = 0; i < 3; i++) {
        if (listen(server_sockets[i], 3) < 0) {
            std::cerr << "Failed on listening " << i + 1 << " socket.\n";
        }
    }
    std::cout << "Done!\n";

    // Connect with 3 client sockets
    std::cout << "Connecting...";
    for (int i = 0; i < 3; i++) {
        addrlen[i] = sizeof(addresses[i]);
        if ((client_sockets[i] = accept(server_sockets[i], (struct sockaddr *)(addresses + i), (socklen_t *)(addrlen + 1))) < 0) {
            std::cerr << "Failed accepting process " << i + 1 << "\n";
            printf("Error number: %d\n", errno);
            printf("The error message is %s\n", strerror(errno));
            printf("Local socket connection with the server failed.\n");
            exit(errno);
        }
    }
    std::cout << "Done!\n";

    return 0;
}

void* manage_clients(void* args) {
     // Manage clients' requests using this function
    // args: 1. client id  2. sockfd: the listening socket for the corresponding process
    argu_t* argu = (argu_t*) args;
    int cid = argu->cid;
    int cur_sockfd = argu->sockfd;
    struct timeval timestamp;
    timestamp_t timestamp_msg;

    // A while loop receiving from the corresponding client
    char buffer[sizeof(request_t)];
    int read_size, sizeleft;
    while (true) {
        sizeleft = sizeof(request_t);
        std::string strMessage;
        while (sizeleft != 0) {
            if ((read_size = recv(cur_sockfd, buffer, sizeof(buffer), 0)) < 0) {
                std::cerr << "Failed receving from process " << cid + 1 << "\n";
                exit(0);
            }
            strMessage.append(buffer);
            sizeleft -= read_size;
            bzero(buffer, sizeof(buffer));
        }
        request_t m;
        m.ParseFromString(strMessage);

        // type 1 for request, type 2 for quit
        if (m.type() == REQUEST_STOP_TYPE) {
            std::cout << "Client " << cid << " exits.\n";
            break;
        }

        // Send out the timestamp to client
        std::cout << "Waiting to send the message from server to client" << cid << "......"<<std::endl;
            
        gettimeofday(&timestamp, NULL);
        timestamp_msg.set_seconds(timestamp.tv_sec);
        timestamp_msg.set_nanos(timestamp.tv_usec);
        strMessage = timestamp_msg.SerializeAsString();
        
        // Add random delay
        uint32_t delay = random_uint32(COMM_DELAY_MAX);
        sleep(delay);

        int send_size = 0;
        if ((send_size = send(cur_sockfd, strMessage.c_str(), sizeof(timestamp_t), 0)) < 0) {
            std::cerr << "Failed\n";
            exit(0);
        }
        std::cout << "Done!\n";
    }

    close(cur_sockfd);
    return NULL;
}

int server::run_time_server() {
   
    // Create two extra threads to handle messages from client 2 and 3
    argu_t argus[3];
    for (int i = 1; i < 3; i++) {
        argus[i].cid = i + 1;
        argus[i].sockfd = client_sockets[i];
        pthread_create(tids + i - 1, NULL, manage_clients, (void*)(argus + i));
    }

    // Call function for main thread
    argus[0].cid = 1;
    argus[0].sockfd = client_sockets[0];
    manage_clients((void*)(argus));

    std::cout << "The time server to clients connection is up!\n";

    // pthread_join for other two threads
    for (int i = 0; i < 2; i++) {
        pthread_join(tids[i], NULL);
    }

    std::cout << "The time server to clients connection is down!\n";

    return 0;
}

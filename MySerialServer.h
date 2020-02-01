//
// Created by ofir on 13/01/2020.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <sstream>
#include "Server.h"
#include "Solver.h"
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "Matrix.h"

using namespace std;
using namespace server_side;

class MySerialServer : public Server {
public:
    void open(int port, ClientHandler* ch) {
        thread thread_obj(handleServer, port, ch);
        thread_obj.join();
    }

    static void handleServer(int port, ClientHandler* ch) {
        int socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd == -1) {
            cerr << "Could not create a socket" << endl;
            exit(1);
        }

        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (bind(socketfd, (struct sockaddr*) &address, sizeof(address)) == -1) {
            cerr << "Could not bind the socket to an IP" << endl;
            exit(1);
        }

        listen(socketfd, 10);

        //can accept up to 10 clients (one by one)
        for (int i = 1; i <= 10; ++i) {
            int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
            if (client_socket == -1) {
                cerr << "Error accepting client" << endl;
                exit(1);
            }
            cout << "connected to client number " << i << endl;
            ch->handleClient(client_socket);
        }

       close(socketfd);
    }


    static void readFromClient(int client_socket, ClientHandler* ch) {
        ch->handleClient(client_socket);
    }


    void stop() {
    }
};

#endif //EX4_MYSERIALSERVER_H

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

class MySerialServer : public Server {

public:
    //this string includes the "end"
    static bool isEnd(char buffer[]) {
        string buff = buffer;
        for (int i = 0; i < buff.length(); i++)  {
            if ((buff[i] == 'e') && (buff[i + 1] == 'n') && (buff[i + 2] == 'd')) {
                return true; //includes "end"
            }
        }
        return false; //doesn't include "end"
    }

    //returns the last buffer without the string "end"
    static string cutEnd(char buffer[]) {
        string buff = buffer;
        string ret = "";

        for (int i = 0; i < buff.length(); i++) {
            if ((buff[i] == 'e') && (buff[i + 1] == 'n') && (buff[i + 2] == 'd')) {
                return ret;
            } else {
                ret += buff[i];
            }
        }
        return ret;
    }


    void open(int port, ClientHandler* ch) {
        int socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd == -1) {
            cerr << "Could not create a socket" << endl;
            //return -1;
        }

        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (bind(socketfd, (struct sockaddr*) &address, sizeof(address)) == -1) {
            cerr << "Could not bind the socket to an IP" << endl;
            //return -2;
        }

        if (listen(socketfd, 10) == -1) { //SOMAXCON
            cerr << "Error during listening command" << endl;
            //return -3;
        }

        while (true) {
            //some loop -- while not stop
            int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
            if (client_socket == -1) {
                cerr << "Error accepting client" << endl;
                //return -4;
            }

            thread thread_obj(readFromClient, client_socket, ch);
            thread_obj.detach();
        }

    }


    static void readFromClient(int client_socket, ClientHandler* ch) {
        ch->handleClient(client_socket);
    }


    void stop() {

    }


    static vector<vector<int>> addToMat(string buffer, vector<vector<int>> mat) {
        vector<int> temp;
        string curr = "";
        int vecCount = 0;
        int len = buffer.length();

        for (int i = 0; i < len; i++) {
            if ((buffer[i] == ' ') || (buffer[i] == ',')) {
                if (curr != "") {
                    temp.push_back(stoi(curr));
                    curr = "";
                    vecCount++;
                }
            } else {
                curr += buffer[i];
            }
        }
        temp.push_back(stoi(curr));
        mat.push_back(temp);
        return mat;
    }

    //If it's the first time we read to a buffer, we create a vector and return it
    static vector<vector<int>> createVector(string buffer) {
        vector<vector<int>> mat;
        vector<int> temp;
        string curr = "";
        int vecCount = 0;
        int len = buffer.length();

        for (int i = 0; i < len; i++) {
            if ((buffer[i] == ' ') || (buffer[i] == ',')) {
                if (curr != "") {
                    temp.push_back(stoi(curr));
                    //mat[0][vecCount] = stoi(curr);
                    curr = "";
                    vecCount++;
                }
            } else {
                curr += buffer[i];
            }
        }
        //add the last "curr" to the temp vector
        temp.push_back(stoi(curr));
        //mat[0][vecCount] = stoi(curr);

        //push temp to mat
        mat.push_back(temp);

        return mat;
    }
};

#endif //EX4_MYSERIALSERVER_H

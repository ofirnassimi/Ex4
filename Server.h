//
// Created by ofir on 13/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include <iostream>
#include "ClientHandler.h"
using namespace std;

class Server {
public:
    virtual void open(int port, ClientHandler* ch) = 0;
    virtual void stop() = 0;
};

namespace server_side {
    Server* s;
}

#endif //EX4_SERVER_H

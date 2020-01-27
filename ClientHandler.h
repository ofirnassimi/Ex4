//
// Created by ofir on 13/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

#include <iostream>
#include <list>
#include "Searchable.h"

using namespace std;

class ClientHandler {
public:
    virtual string handleClient(int client_socket) = 0;
};

#endif //EX4_CLIENTHANDLER_H

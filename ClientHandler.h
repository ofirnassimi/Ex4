//
// Created by ofir on 13/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

#include <iostream>
#include <list>
#include "Searchable.h"
//#include "Solver.h"

using namespace std;

class ClientHandler {
public:
    //virtual string handleClient(list<string> buffers) = 0;
    //virtual string handleClient(Searchable<T>* s) = 0;
    virtual string handleClient(int client_socket) = 0;
};

#endif //EX4_CLIENTHANDLER_H

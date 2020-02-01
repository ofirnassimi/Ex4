#include <iostream>
#include "Server.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "StringReverser.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "ObjectAdapter.h"
#include "MyParallelServer.h"

int main(int argc, char* argv[]) {
    server_side::MyParallelServer s;
    Solver<Matrix, string>* sol = new ObjectAdapter();
    CacheManager<string, string>* cm = new FileCacheManager();
    ClientHandler* ch = new MyTestClientHandler(sol, cm);
    int port = stoi(argv[1]);
    s.open(port, ch);
}
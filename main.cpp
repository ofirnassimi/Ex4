#include <iostream>
#include "Server.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "StringReverser.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "ObjectAdapter.h"

int main() {
    Server* s = new MySerialServer();
    Solver<Matrix, string>* sol = new ObjectAdapter();
    //Solver<list<string>, string>* sol = new ObjectAdapter();
    CacheManager<string, string>* cm = new FileCacheManager();
    ClientHandler* ch = new MyTestClientHandler(sol, cm);
    s->open(5400, ch);
}
#include <iostream>
#include "Server.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "StringReverser.h"

int main() {
    Server* s = new MySerialServer();
    Solver<string, string>* sol = new StringReverser();
    ClientHandler* ch = new MyTestClientHandler(sol);
    s->open(5400, ch);
}
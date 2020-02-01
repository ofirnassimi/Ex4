//
// Created by ofir on 28/01/2020.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H

#include <bits/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stack>
#include <thread>
#include <unistd.h>
#include "Server.h"
#include "Sockets.h"

namespace server_side {
    class MyParallelServer : public Server {
        bool isFirst = true;

    public:
        void open(int port, ClientHandler *ch) {
            stack<thread> threads;
            posix_sockets::TCP_server server(port);
            server.listen(10);

            while (true) {
                try {
                    posix_sockets::TCP_client client = server.accept();
                    threads.push(thread([](ClientHandler *handler, int sock) { handler->handleClient(sock); }, ch,
                                        client.get_socket()));
                } catch (posix_sockets::timeout_exception &e) {
                    server.close();
                    break;
                } catch (exception &e) {
                    exit(1);
                }

                if (isFirst) {
                    server.setTimeOut(10);
                    isFirst = false;
                }
            }

            while (!threads.empty()) {
                threads.top().join();
                threads.pop();
            }
        }

        void stop() {}

        bool isOpen() {
            return false;
        }
    };
}

#endif //EX4_MYPARALLELSERVER_H

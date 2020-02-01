//
// Created by ofir on 30/01/2020.
//

#ifndef EX4_SOCKETS_H
#define EX4_SOCKETS_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <system_error>
#include <stdexcept>

using namespace std;

namespace posix_sockets {
    class timeout_exception : public runtime_error {
    public:
        explicit timeout_exception(const char *msg) : runtime_error(msg) {}
        explicit timeout_exception(const string& msg) : runtime_error(msg) {}
    };

    class illegal_state_exception : public logic_error {
    public:
        explicit illegal_state_exception(const string& msg) : logic_error(msg) {}
    };


    struct TCP_socket {
        int socketfd;

        TCP_socket() {
            socketfd = socket(AF_INET, SOCK_STREAM, 0);
            if (socketfd < 0) {
                throw system_error(error_code(errno, generic_category()), "Could not create a socket");
            }
        }

        TCP_socket(int sockfd) {
            this->socketfd = sockfd;
        }

        void close() {
            if (::close(socketfd) < 0) {
                throw system_error(error_code(errno, generic_category()), "Could not close socket");
            }
        }

        void setTimeOut(int sec, int usec = 0) {
            timeval timeout;
            timeout.tv_sec = sec;
            timeout.tv_usec = usec;

            // setting socket option for recieve timeout
            if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout)) == -1) {
                throw system_error(error_code(errno, generic_category()), "Failure on setsockopt");
            }
        }
    };


    class TCP_client {
        TCP_socket sock;
    public:
        int get_socket() const {
            return sock.socketfd;
        }
        explicit TCP_client(TCP_socket sock) : sock(sock) {}

        std::string read(int max_len) {
            char *buffer = new char[max_len + 1];
            int read_len = ::read(sock.socketfd, buffer, max_len);
            if (read_len < 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    throw timeout_exception("Timeout while reading");
                }
                throw system_error(error_code(errno, generic_category()), "Could not read");
            }

            buffer[read_len] = 0;
            string output = string(buffer);
            delete[] buffer;
            return output;
        }

        void setTimeOut(int sec, int usec = 0) {
            sock.setTimeOut(sec, usec);
        }

        void close() {
            sock.close();
        }
    };


    class TCP_server {
        TCP_socket sock;
    public:
        TCP_server(int port) {
            int n = 1;
            setsockopt(sock.socketfd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(int));
            sockaddr_in addr_in;
            addr_in.sin_family = AF_INET;
            addr_in.sin_port = htons(port);
            addr_in.sin_addr.s_addr = INADDR_ANY;

            if (bind(sock.socketfd, (sockaddr *) &addr_in, sizeof(addr_in)) == -1) {
                throw system_error(error_code(errno, generic_category()), "Could not bind the socket to an IP");
            }
        }

        void listen(int max_lis) {
            if (::listen(sock.socketfd, max_lis) == -1) {
                throw system_error(error_code(errno, generic_category()), "Error during listening command");
            }
        }

        void setTimeOut(int sec, int usec = 0) {
            sock.setTimeOut(sec, usec);
        }

        TCP_client accept() {
            sockaddr_in addr;
            socklen_t len = sizeof(addr);
            int client_socket = ::accept(sock.socketfd, (sockaddr*) &addr, &len);
            if (client_socket == -1) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    throw timeout_exception("Timeout while accepting");
                } else {
                    throw system_error(error_code(errno, generic_category()), "Error accepting client");
                }
            }

            TCP_socket client_sock(client_socket);

            client_sock.setTimeOut(0);
            return TCP_client(client_sock);
        }

        void close() {
            sock.close();
        }
    };
}

#endif //EX4_SOCKETS_H

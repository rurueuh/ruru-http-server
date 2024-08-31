/*
** EPITECH PROJECT, 2024
** codecrafters-http-server-cpp
** File description:
** Socket
*/

#pragma once

#include <bits/stdc++.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

class Socket {
    public:
        Socket(uint16_t port);
        Socket(sockaddr_in addr, uint _fd);
        ~Socket();

        void listen(void);
        Socket accept(void);

        uint get_fd(void) { return _server_fd; }
        sockaddr_in get_addr(void) { return _server_addr; }

        std::string getIP(void) {
            return inet_ntoa(_server_addr.sin_addr);
        }

        void send(std::string data);
        std::string recv(void);

    protected:
        uint16_t _port = 0;
        uint _server_fd = 0;
        sockaddr_in _server_addr = {};
    private:
};

/*
** EPITECH PROJECT, 2024
** codecrafters-http-server-cpp
** File description:
** Socket
*/

#include "Socket.hpp"

Socket::Socket(uint16_t port)
    : _port(port)
{
    _server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_fd < 0) {
        throw std::runtime_error("Failed to create server socket");
    }

    int reuse = 1;
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        throw std::runtime_error("setsockopt failed");
    }

    _server_addr.sin_family = AF_INET;
    _server_addr.sin_addr.s_addr = INADDR_ANY;
    _server_addr.sin_port = htons(port);

    if (bind(_server_fd, (struct sockaddr *) &_server_addr, sizeof(_server_addr)) != 0) {
        throw std::runtime_error("Failed to bind to port " + std::to_string(port));
    }
}

Socket::Socket(sockaddr_in addr, uint _fd)
{
    _server_addr = addr;
    _server_fd = _fd;
}

Socket::~Socket()
{
    close(_server_fd);
}

void Socket::listen(void)
{
    int connection_backlog = 5;
    if (::listen(_server_fd, connection_backlog) != 0) {
        throw std::runtime_error("Failed to listen on port " + std::to_string(_port));
    }
}

Socket Socket::accept(void)
{
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    int client_fd = ::accept(_server_fd, (struct sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
    if (client_fd < 0) {
        throw std::runtime_error("Failed to accept connection");
    }

    return Socket(client_addr, client_fd);
}

void Socket::send(std::string data)
{
    if (::send(_server_fd, data.c_str(), data.length(), 0) < 0) {
        throw std::runtime_error("Failed to send data");
    }
}

std::string Socket::recv(void)
{
    char buffer[1024] = {0};
    int valread = ::recv(_server_fd, buffer, 1024, 0);
    if (valread < 0) {
        throw std::runtime_error("Failed to receive data");
    }

    return std::string(buffer);
}

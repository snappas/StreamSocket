//
// Created by ryan on 9/4/16.
//

#include "Server.hxx"
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>

Server::Server(const std::string &listen_address, int listen_port) : address(listen_address), listen_fd(-1) {
    if (listen_port > UINT16_MAX) {
        port = UINT16_MAX - 1;
    } else {
        port = (uint16_t) listen_port;
    }
    bind_socket();
    listen_socket();
}

void Server::bind_socket() {
    sockaddr_in listen_sockaddr_in;
    std::memset(&listen_sockaddr_in, 0, sizeof(listen_sockaddr_in));
    listen_sockaddr_in.sin_family = AF_INET;
    inet_aton(address.c_str(), &listen_sockaddr_in.sin_addr);
    listen_sockaddr_in.sin_port = htons(port);

    listen_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (listen_fd < 0) {
        perror("could not create socket");
    }

    int t = 1;
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &t, sizeof(t))) {
        perror("could not set SO_REUSEADDR");
    }

    if (bind(listen_fd, (struct sockaddr *) &listen_sockaddr_in, sizeof(listen_sockaddr_in))) {
        perror("could not bind listen socket");
    }
}

void Server::listen_socket() {
    if (listen(listen_fd, 48)) {
        perror("could not listen on socket");
    }
}

int Server::get_descriptor() {
    return listen_fd;
}

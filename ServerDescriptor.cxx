//
// Created by ryan on 9/3/16.
//

#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include "ServerDescriptor.hxx"

int ServerDescriptor::accept_nonblocking() {
    sockaddr_in peer_addr;
    socklen_t peer_addr_size = sizeof(peer_addr);
    std::memset(&peer_addr, 0, peer_addr_size);
    /*
     * Accept new connections in non-blocking mode for use with edge-triggered epoll
     * it's ok if accept returns -1, we will use it to stop looking for new connections
     */
    int peer_fd = accept4(fd, (struct sockaddr *) &peer_addr, &peer_addr_size, SOCK_NONBLOCK);

    return peer_fd;
}

ServerDescriptor::~ServerDescriptor() {
    close(fd);

}

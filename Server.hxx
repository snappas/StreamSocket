//
// Created by ryan on 9/4/16.
//

#ifndef STREAMSOCKET_SERVER_HXX
#define STREAMSOCKET_SERVER_HXX

#include <string>
#include <stdint.h>

class Server {
public:
    Server(const std::string &listen_address, int listen_port);

    void bind_socket();

    void listen_socket();

    int get_descriptor();

private:
    int listen_fd;
    std::string address;
    uint16_t port;
};


#endif //STREAMSOCKET_SERVER_HXX

//
// Created by ryan on 9/3/16.
//

#ifndef STREAMSOCKET_EPOLL_IF_HXX
#define STREAMSOCKET_EPOLL_IF_HXX


#include "Descriptor.hxx"
#include "DataModel.hxx"

class Epoll_If {
public:
    Epoll_If(){init();};

    Epoll_If(DataModel *model);

    void init();
    void event_loop();
    void add_server_descriptor(int fd);
    void add_file_descriptor(int fd);
    void add_client_descriptor(int fd);


    int epollfd;

    void set_fd(int io, Descriptor* desc);

private:
    DataModel *model;
};


#endif //STREAMSOCKET_EPOLL_IF_HXX

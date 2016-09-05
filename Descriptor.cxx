//
// Created by ryan on 9/5/16.
//

#include <sys/epoll.h>
#include "Descriptor.hxx"
#include "ClientDescriptor.hxx"
#include "ServerDescriptor.hxx"
#include "FileDescriptor.hxx"

Descriptor *Descriptor::make_descriptor(int type, int fd, DataModel *model, epoll_event *event) {
    switch (type) {
        case Descriptor::SERVER: {
            event->events = EPOLLIN | EPOLLET;
            return new ServerDescriptor(fd);
        }
        case Descriptor::CLIENT: {
            event->events = EPOLLIN | EPOLLET | EPOLLONESHOT;
            return new ClientDescriptor(fd, model);
        }
        case Descriptor::FILE: {
            event->events = EPOLLIN | EPOLLET | EPOLLONESHOT;
            return new FileDescriptor(fd, model);
        }
        default:
            return NULL;
    }
}

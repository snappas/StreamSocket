//
// Created by ryan on 9/3/16.
//

#include <sys/epoll.h>
#include <unistd.h>
#include "ClientDescriptor.hxx"

int ClientDescriptor::do_io(unsigned int i) {
    if (i & EPOLLOUT) {
        return do_write();
    } else if (i & EPOLLIN) {
        return do_read();
    } else {
        return Descriptor::ERROR;
    }
}

int ClientDescriptor::do_write() {
    return 0;
}

int ClientDescriptor::do_read() {
    return 0;
}

ClientDescriptor::~ClientDescriptor() {
    close(fd);
}

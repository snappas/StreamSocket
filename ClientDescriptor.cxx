//
// Created by ryan on 9/3/16.
//

#include <sys/epoll.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <cerrno>
#include <iostream>
#include "ClientDescriptor.hxx"

ClientDescriptor::ClientDescriptor(int fd, DataModel *model) : Descriptor(Descriptor::CLIENT, fd), model(model) {
}

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
    const char *outgoing_message = write_buffer.c_str();
    size_t length = write_buffer.length();
    ssize_t bytes_sent = 0;

    while (length != 0 && (bytes_sent = write(fd, outgoing_message, length)) != -1) {
        outgoing_message += bytes_sent;
        length -= bytes_sent;
    }

    if (bytes_sent == -1) {
        if (errno == EAGAIN) {
            std::string remainder(outgoing_message, length);
            write_buffer = remainder;
            return Descriptor::WRITABLE;
        } else {
            return Descriptor::ERROR;
        }
    }
    write_buffer.clear();
    return Descriptor::READABLE;
}

int ClientDescriptor::do_read() {
    ssize_t bytes_received;
    char buf[4096];

    while ((bytes_received = read(fd, buf, sizeof buf)) > 0) {
        read_buffer.append(buf, (unsigned long) bytes_received);
        std::memset(buf, 0, 4096); //reset the buffer for the next read
    }

    if (bytes_received < 0) {
        if (errno != EAGAIN || errno != EWOULDBLOCK) {
            return Descriptor::ERROR;
        }
    }

    if (!read_buffer.empty()) {
        if (*read_buffer.rbegin() == '\n') { /* end of message delimiter will be \n */
            if (model->parse_request(&read_buffer) == DataModel::GOOD_REQUEST) {
                write_buffer = std::string(read_buffer);
                read_buffer.clear();
                return Descriptor::WRITABLE;
            } else {
                return Descriptor::READABLE;
            }
        } else {
            return Descriptor::READABLE;
        }
    }
    return Descriptor::ERROR;
}

ClientDescriptor::~ClientDescriptor() {
    close(fd);
}



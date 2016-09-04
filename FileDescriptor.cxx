//
// Created by ryan on 9/4/16.
//

#include <sys/epoll.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "FileDescriptor.hxx"

FileDescriptor::FileDescriptor(int fd, DataModel *model) : Descriptor(Descriptor::FILE, fd), model(model) {
}

int FileDescriptor::do_io(unsigned int i) {
    if (i & EPOLLOUT) {
        return do_write();
    } else if (i & EPOLLIN) {
        return do_read();
    } else {
        return Descriptor::ERROR;
    }
}

int FileDescriptor::do_write() {
    return 0;
}

int FileDescriptor::do_read() {
    if( (stream = fdopen(fd, "r")) == NULL){
        perror("fdopen");
        return Descriptor::ERROR;
    }else{
        char *buffer = NULL;
        size_t buffer_size;
        ssize_t bytes_read = getline(&buffer, &buffer_size, stream);
        if(bytes_read != -1){
            model->parse_data(std::string(buffer));
            std::cout << buffer << std::endl;
            return Descriptor::READABLE;
        }else{
            return Descriptor::ERROR;
        }
    }
}

FileDescriptor::~FileDescriptor() {
    pclose(stream);
}

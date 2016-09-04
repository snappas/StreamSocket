//
// Created by ryan on 9/4/16.
//

#ifndef STREAMSOCKET_FILEDESCRIPTOR_HXX
#define STREAMSOCKET_FILEDESCRIPTOR_HXX

#include <stdio.h>

#include "Descriptor.hxx"
#include "DataModel.hxx"

class FileDescriptor : public Descriptor {
public:
    FileDescriptor(int fd) : Descriptor(Descriptor::FILE, fd) {};

    FileDescriptor(int fd, DataModel *model);

    ~FileDescriptor();

    int do_io(unsigned int i);

    int do_write();

    int do_read();

private:
    _IO_FILE *stream;
    DataModel *model;
};


#endif //STREAMSOCKET_FILEDESCRIPTOR_HXX

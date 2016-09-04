//
// Created by ryan on 9/3/16.
//

#ifndef STREAMSOCKET_CLIENTDESCRIPTOR_HXX
#define STREAMSOCKET_CLIENTDESCRIPTOR_HXX


#include "Descriptor.hxx"
#include "DataModel.hxx"

class ClientDescriptor : public Descriptor {
public:
    ClientDescriptor(int fd): Descriptor(Descriptor::CLIENT, fd) {};

    ClientDescriptor(int fd, DataModel *model);
    ~ClientDescriptor();

    int do_io(unsigned int i);
    int do_write();
    int do_read();

private:
    DataModel *model;
    std::string read_buffer;
    std::string write_buffer;
};


#endif //STREAMSOCKET_CLIENTDESCRIPTOR_HXX

//
// Created by ryan on 9/3/16.
//

#ifndef STREAMSOCKET_SERVERDESCRIPTOR_HXX
#define STREAMSOCKET_SERVERDESCRIPTOR_HXX


#include "Descriptor.hxx"
#include "DataModel.hxx"

class ServerDescriptor : public Descriptor {
public:
    ServerDescriptor(int fd): Descriptor(Descriptor::SERVER, fd){};

    ~ServerDescriptor();
    int accept_nonblocking();

};


#endif //STREAMSOCKET_SERVERDESCRIPTOR_HXX

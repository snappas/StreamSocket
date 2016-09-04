//
// Created by ryan on 9/3/16.
//

#ifndef STREAMSOCKET_DESCRIPTOR_HXX
#define STREAMSOCKET_DESCRIPTOR_HXX


class Descriptor {

public:
    enum {
        SERVER = 1,
        CLIENT = 2,
        FILE = 3
    };
    enum {
        READABLE = 1,
        WRITABLE = 2,
        ERROR = 3
    };
    Descriptor(int type, int fd):type(type), fd(fd){};

    virtual ~Descriptor() {};

    int get_type() { return type; }

    int get_descriptor() { return fd; }
protected:
    int type;
    int fd;

};


#endif //STREAMSOCKET_DESCRIPTOR_HXX

#include <iostream>
#include "ExternalProcess.hxx"
#include "Epoll_If.hxx"

int main() {
    std::cout << "Hello, World!" << std::endl;
    ExternalProcess telnet("telnet 192.168.1.13 30000");
    Epoll_If epoll;
    epoll.add_file_descriptor(telnet.getFileDescriptor());
    while(1){
        epoll.event_loop();
    }

    return 0;
}